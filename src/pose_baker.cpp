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
    String name,
    real_t height)
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
    godot::Vector<int32_t> tracks;
    for (const PoseBone& bone : rig->get_bones())
    {
        int32_t track = anim->add_track(Animation::TrackType::TYPE_VALUE);
        tracks.push_back(track);
        anim->track_set_path(track, NodePath(godot::String(bone.bone->get_path()) + ":rotation"));
    }

    for (size_t i = 0; i < poseRecording->count_snapshots(); ++i)
    {
        real_t time = poseRecording->get_time(i);
        if (time < 0)
            continue;
        rig->apply_from(poseRecording, i);
        for (size_t j = 0; j < tracks.size(); ++j)
        {
            anim->track_insert_key(tracks[j], time, rig->get_bones()[j].bone->get_rotation());
        }
    }
    anim->set_length(poseRecording->get_time(poseRecording->count_snapshots() - 1));
}

void PoseBaker::_bind_methods()
{
    ClassDB::bind_static_method("PoseBaker", D_METHOD("bake"), PoseBaker::bake);
}
