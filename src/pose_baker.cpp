#include "pose_baker.h"

#include <godot_cpp/classes/animation_player.hpp>
#include <godot_cpp/classes/animation_library.hpp>
#include <godot_cpp/classes/animation.hpp>

#include "pose_recording.h"

using namespace godot;

void PoseBaker::bake(
    PoseRecording* poseRecording,
    Node* rig,
    AnimationPlayer* animPlayer,
    String name,
    real_t height)
{
    Ref<AnimationLibrary> recordings;
    if (animPlayer->has_animation_library("Recordings"))
    {
        recordings = animPlayer->get_animation_library("Recordings");
        WARN_PRINT_ED("Got library");
    }
    else
    {
        recordings = Ref<AnimationLibrary>(memnew(AnimationLibrary));
        animPlayer->add_animation_library("Recordings", recordings);
        recordings = animPlayer->get_animation_library("Recordings");
        WARN_PRINT_ED("Created library");
    }
    WARN_PRINT_ED("Created library");

    Ref<Animation> anim = memnew(Animation);
    WARN_PRINT_ED("Created anim");

    recordings->add_animation(name, anim);
    WARN_PRINT_ED("Added animation");

    // Create the tracks
    int32_t tracks[33];
    for (size_t i = 0; i < 33; ++i)
    {
        tracks[i] = anim->add_track(Animation::TrackType::TYPE_VALUE);
        WARN_PRINT_ED("Add track");
        anim->track_set_path(tracks[i], NodePath(godot::String(rig->get_child(i)->get_path()) + ":position"));
        WARN_PRINT_ED("Set track paths");
    }
    WARN_PRINT_ED("Created tracks");

    for (size_t i = 0; i < poseRecording->count_snapshots(); ++i)
    {
        real_t time = poseRecording->get_time(i);
        if (time < 0)
            continue;
        for (size_t j  = 0; j < 33; ++j)
        {
            anim->track_insert_key(tracks[j], time, poseRecording->get_position(i, j) * height);
        }
    }
    anim->set_length(poseRecording->get_time(poseRecording->count_snapshots() - 1));
    WARN_PRINT_ED("Processed snapshots");
}

void PoseBaker::_bind_methods()
{
    ClassDB::bind_static_method("PoseBaker", D_METHOD("bake"), PoseBaker::bake);
}
