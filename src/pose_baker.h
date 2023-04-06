#ifndef POSE_BAKER_H
#define POSE_BAKER_H

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/templates/vector.hpp>

namespace godot {
    class AnimationPlayer;
}
class PoseRecording;
class PoseRig;

class PoseBaker : public godot::Resource
{
GDCLASS(PoseBaker, Resource);

protected:
    static void _bind_methods();

public:
    static void bake(
        PoseRecording* poseRecording,
        PoseRig* rig,
        godot::AnimationPlayer* animPlayer,
        godot::String name);
};

#endif // POSE_RECORDING_H
