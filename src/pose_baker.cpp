#include "pose_baker.h"

#include <godot_cpp/classes/animation_player.hpp>
#include <godot_cpp/classes/animation_library.hpp>
#include <godot_cpp/classes/animation.hpp>
#include <godot_cpp/classes/bone2d.hpp>

#include "pose_recording.h"
#include "pose_rig.h"
#include "anim_compressor.h"

using namespace godot;

void PoseBaker::bake(
    PoseRecording* poseRecording,
    PoseRig* rig,
    AnimationPlayer* animPlayer,
    String name,
    double max_rot_error,
    double max_pos_error)
{
    Ref<AnimationLibrary> recordings;
    if (animPlayer->has_animation_library("Recordings"))
    {
        recordings = animPlayer->get_animation_library("Recordings");
    }
    else
    {
        recordings = Ref<AnimationLibrary>(memnew(AnimationLibrary));
        animPlayer->add_animation_library("Recordings", recordings);
        recordings = animPlayer->get_animation_library("Recordings");
    }

    Ref<Animation> anim = memnew(Animation);

    recordings->add_animation(name, anim);

    // Create the tracks
    godot::Vector<int32_t> rot_tracks;
    godot::Vector<int32_t> pos_tracks;
    for (const PoseBone& bone : rig->get_bones())
    {
        int32_t rot_track = anim->add_track(Animation::TrackType::TYPE_VALUE);
        anim->track_set_path(rot_track, NodePath(godot::String(bone.bone->get_path()) + ":rotation"));
        rot_tracks.push_back(rot_track);

        int32_t pos_track = 0;
        if (bone.root)
        {
            pos_track = anim->add_track(Animation::TrackType::TYPE_VALUE);
            anim->track_set_path(pos_track, NodePath(godot::String(bone.bone->get_path()) + ":position"));
        }
        pos_tracks.push_back(pos_track);
    }

    // Add frames to compressor
    AnimCompressor compressor;
    for (size_t i = 0; i < poseRecording->count_snapshots(); ++i)
    {
        real_t time = poseRecording->get_time(i);
        if (time < 0)
        {
            continue;
        }
        rig->apply_from(poseRecording, i);
        for (size_t j = 0; j < rot_tracks.size(); ++j)
        {
            compressor.add_rot_sample(rot_tracks[j], time, rig->get_bones()[j].bone->get_rotation());
        }
        for (size_t j = 0; j < pos_tracks.size(); ++j)
        {
            if (rig->get_bones()[j].root)
            {
                compressor.add_pos_sample(pos_tracks[j], time, rig->get_bones()[j].bone->get_position());
            }
        }
    }

    // Run compression
    compressor.compress(Math_TAU / 200, 1);

    // Add values to actual animation player tracks
    for (const auto& track : compressor.pos_tracks)
    {
        for (const auto& frame : track.value)
        {
            anim->track_insert_key(track.key, frame.time, frame.pos);
        }
    }
    for (const auto& track : compressor.rot_tracks)
    {
        for (const auto& frame : track.value)
        {
            anim->track_insert_key(track.key, frame.time, frame.rot);
        }
    }
    anim->set_length(poseRecording->get_time(poseRecording->count_snapshots() - 1));
}

void PoseBaker::_bind_methods()
{
    ClassDB::bind_static_method("PoseBaker", D_METHOD("bake"), PoseBaker::bake);
}
