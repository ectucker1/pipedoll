#ifndef POSE_RIG_H
#define POSE_RIG_H

#include "pose_recording.h"

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/templates/vector.hpp>

namespace godot
{
    class Bone2D;
};

struct PoseBone
{
    godot::Bone2D* bone;
    godot::Vector<uint8_t> start_landmarks;
    godot::Vector<uint8_t> target_landmarks;

    PoseBone() {};
    PoseBone(godot::Bone2D* bone, godot::Vector<uint8_t> start_landmarks, godot::Vector<uint8_t> target_landmarks) :
        bone(bone), start_landmarks(start_landmarks), target_landmarks(target_landmarks) {}
};

class PoseRig : public godot::Resource
{
GDCLASS(PoseRig, Resource);

private:
    godot::Vector<PoseBone> _bones;

protected:
    static void _bind_methods();

public:
    void clear_rig();
    void load_rig(godot::Node* root);
    const godot::Vector<PoseBone>& get_bones() const { return _bones; };

    void apply_from(const PoseRecording* recording, size_t snapshot) const;
};

#endif // POSE_RIG_H
