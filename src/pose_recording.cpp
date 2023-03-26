#include "pose_recording.h"

using namespace godot;

PackedFloat32Array PoseRecording::get_data() const
{
    PackedFloat32Array data = PackedFloat32Array();
    for (size_t i = 0; i < _snapshots.size(); ++i)
    {
        _snapshots[i].append_to(data);
    }
    return data;
}

void PoseRecording::set_data(const PackedFloat32Array& data)
{
    size_t count = data.size() / (1 + (33 * 4));
    _snapshots.clear();
    for (size_t i = 0; i < count; ++i)
    {
        PoseSnapshot2D snapshot;
        snapshot.read_from(data, i * (1 + (33 * 4)));
        _snapshots.append(std::move(snapshot));
    }
}

void PoseRecording::add_snapshot(real_t timestep, const PoseLandmark2D (& landmarks)[33])
{
    _snapshots.push_back(PoseSnapshot2D(timestep, landmarks));
}

size_t PoseRecording::count_snapshots() const
{
    return _snapshots.size();
}

real_t PoseRecording::get_time(size_t snapshot) const
{
    return _snapshots[snapshot].time;
}

Vector2 PoseRecording::get_position(size_t snapshot, size_t landmark) const
{
    return _snapshots[snapshot].landmarks[landmark].position;
}

real_t PoseRecording::get_depth(size_t snapshot, size_t landmark) const
{
    return _snapshots[snapshot].landmarks[landmark].depth;
}

real_t PoseRecording::get_visibility(size_t snapshot, size_t landmark) const
{
    return _snapshots[snapshot].landmarks[landmark].visibility;
}

void PoseRecording::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("get_data"), &PoseRecording::get_data);
    ClassDB::bind_method(D_METHOD("set_data"), &PoseRecording::set_data);
    ADD_PROPERTY(PropertyInfo(Variant::PACKED_FLOAT32_ARRAY, "data"), "set_data", "get_data");
    ClassDB::bind_method(D_METHOD("count_snapshots"), &PoseRecording::count_snapshots);
    ClassDB::bind_method(D_METHOD("get_position"), &PoseRecording::get_position);
    ClassDB::bind_method(D_METHOD("get_depth"), &PoseRecording::get_depth);
    ClassDB::bind_method(D_METHOD("get_visibility"), &PoseRecording::get_visibility);
}
