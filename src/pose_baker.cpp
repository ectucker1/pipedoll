#include "pose_baker.h"

#include <godot_cpp/classes/animation_player.hpp>
#include <godot_cpp/classes/animation_library.hpp>
#include <godot_cpp/classes/animation.hpp>
#include <godot_cpp/classes/bone2d.hpp>

#include "pose_recording.h"
#include "pose_rig.h"

using namespace godot;

void PoseBaker::bake(
    PoseRecording* poseRecording,
    PoseRig* rig,
    AnimationPlayer* animPlayer,
    String name)
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

    for (size_t i = 0; i < poseRecording->count_snapshots(); ++i)
    {
        real_t time = poseRecording->get_time(i);
        if (time < 0)
            continue;
        rig->apply_from(poseRecording, i);
        for (size_t j = 0; j < rot_tracks.size(); ++j)
        {
            anim->track_insert_key(rot_tracks[j], time, rig->get_bones()[j].bone->get_rotation());
        }
        for (size_t j = 0; j < pos_tracks.size(); ++j)
        {
            if (rig->get_bones()[j].root)
            {
                anim->track_insert_key(pos_tracks[j], time, rig->get_bones()[j].bone->get_position());
            }
        }
    }
    anim->set_length(poseRecording->get_time(poseRecording->count_snapshots() - 1));
}

void PoseBaker::_bind_methods()
{
    ClassDB::bind_static_method("PoseBaker", D_METHOD("bake"), PoseBaker::bake);
}
