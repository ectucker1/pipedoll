#include "pose_rig.h"

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/bone2d.hpp>

using namespace godot;

const char* start_meta = "StartMetamark";
const char* target_meta = "TargetMetamark";

void PoseRig::clear_rig()
{
    _bones.clear();
}

static Vector<uint8_t> get_landmarks(const Node* node, const StringName& meta)
{
    Vector<uint8_t> landmarks;
    auto marks = node->get_meta(meta).stringify().split(",", false);
    for (const auto& mark : marks)
    {
        int64_t index = mark.to_int();
        if (index > 0 && index < 33)
            landmarks.append(index);
    }
    return landmarks;
} 

void PoseRig::load_rig(Node* root)
{
    Bone2D* bone = Object::cast_to<Bone2D>(root);
    if (bone != nullptr)
    {
        auto start_landmarks = get_landmarks(bone, start_meta);
        auto target_landmarks = get_landmarks(bone, target_meta);
        if (start_landmarks.size() > 0 && target_landmarks.size() > 0)
        {
            _bones.append(PoseBone(bone, start_landmarks, target_landmarks));
        }
    }
    for (size_t i = 0; i < root->get_child_count(); ++i)
    {
        load_rig(root->get_child(i));
    }
}

double calc_global_angle(const PoseRecording* recording, size_t snapshot, const godot::Vector<uint8_t>& start_landmarks, const godot::Vector<uint8_t>& target_landmarks)
{
    Vector2 start;
    for (uint8_t landmark : start_landmarks)
    {
        start += recording->get_position(snapshot, landmark);
    }
    start /= start_landmarks.size();

    Vector2 target;
    for (uint8_t landmark : target_landmarks)
    {
        target += recording->get_position(snapshot, landmark);
    }
    target /= target_landmarks.size();

    Vector2 diff = target - start;
    return atan2(diff.y, diff.x);
}

void PoseRig::apply_from(const PoseRecording* recording, size_t snapshot) const
{
    for (const PoseBone& bone : _bones)
    {    
        bone.bone->set_autocalculate_length_and_angle(bone.bone->get_autocalculate_length_and_angle());
    }

    for (const PoseBone& bone : _bones)
    {
        double target_angle = calc_global_angle(recording, snapshot, bone.start_landmarks, bone.target_landmarks);
        bone.bone->set_global_rotation(target_angle - bone.bone->get_bone_angle());
    }
}

void PoseRig::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("clear_rig"), &PoseRig::clear_rig);
    ClassDB::bind_method(D_METHOD("load_rig"), &PoseRig::load_rig);
}
