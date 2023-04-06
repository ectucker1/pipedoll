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
    bool root;

    PoseBone() {};
    PoseBone(godot::Bone2D* bone, godot::Vector<uint8_t> start_landmarks, godot::Vector<uint8_t> target_landmarks, bool root) :
        bone(bone), start_landmarks(start_landmarks), target_landmarks(target_landmarks), root(root) {}
};

class PoseRig : public godot::Resource
{
GDCLASS(PoseRig, Resource);

private:
    godot::Vector<PoseBone> _bones;
    godot::Vector2 _root_scale;

protected:
    static void _bind_methods();

public:
    void clear_rig();
    void load_rig(godot::Node* node, godot::Vector2 root_scale);
    const godot::Vector<PoseBone>& get_bones() const { return _bones; };

    void apply_from(const PoseRecording* recording, size_t snapshot) const;

private:
    void load_rig_recur(godot::Node* node, bool root);
};

#endif // POSE_RIG_H
