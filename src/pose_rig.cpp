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

void PoseRig::load_rig(Node* node, Vector2 root_scale)
{
    _root_scale = root_scale;
    load_rig_recur(node, true);
}

void PoseRig::load_rig_recur(Node* node, bool root)
{
    Bone2D* bone = Object::cast_to<Bone2D>(node);
    if (bone != nullptr)
    {
        auto start_landmarks = get_landmarks(bone, start_meta);
        auto target_landmarks = get_landmarks(bone, target_meta);
        if (start_landmarks.size() > 0 && target_landmarks.size() > 0)
        {
            _bones.append(PoseBone(bone, start_landmarks, target_landmarks, root));
        }
        root = false;
    }
    for (size_t i = 0; i < node->get_child_count(); ++i)
    {
        load_rig_recur(node->get_child(i), root);
    }
}

static Vector2 calc_landmark_pos(const PoseRecording* recording, size_t snapshot, const godot::Vector<uint8_t>& landmarks)
{
    Vector2 pos;
    for (uint8_t landmark : landmarks)
    {
        pos += recording->get_position(snapshot, landmark);
    }
    pos /= landmarks.size();
    return pos;
}

void PoseRig::apply_from(const PoseRecording* recording, size_t snapshot) const
{
    for (const PoseBone& bone : _bones)
    {    
        bone.bone->set_autocalculate_length_and_angle(bone.bone->get_autocalculate_length_and_angle());
    }

    for (const PoseBone& bone : _bones)
    {
        Vector2 start = calc_landmark_pos(recording, snapshot, bone.start_landmarks);
        Vector2 target = calc_landmark_pos(recording, snapshot, bone.target_landmarks);

        Vector2 diff = target - start;
        double target_angle = atan2(diff.y, diff.x);

        bone.bone->set_global_rotation(target_angle - bone.bone->get_bone_angle());

        if (bone.root)
            bone.bone->set_global_position(target * _root_scale);
    }
}

void PoseRig::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("clear_rig"), &PoseRig::clear_rig);
    ClassDB::bind_method(D_METHOD("load_rig"), &PoseRig::load_rig);
}
