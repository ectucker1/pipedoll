#include "pose_recording.h"

PackedFloat32Array PoseRecording::get_data() const
{
    PackedFloat32Array data = PackedFloat32Array();
    data.resize(_snapshots.size());
    for (size_t i = 0; i < _snapshots.size(); ++i)
    {
        const PoseLandmark2D& landmark = _snapshots[i];
        data.set(i * 4 + 0, landmark.position.x);
        data.set(i * 4 + 1, landmark.position.y);
        data.set(i * 4 + 2, landmark.depth);
        data.set(i * 4 + 3, landmark.visibility);
    }
    return data;
}

void PoseRecording::set_data(const PackedFloat32Array& data)
{
    _snapshots.clear();

    size_t count = data.size() / 4;
    _snapshots.resize(count);
    for (size_t i = 0; i < count; ++i)
    {
        PoseLandmark2D landmark;
        landmark.position.x = data[i * 4 + 0];
        landmark.position.y = data[i * 4 + 1];
        landmark.depth = data[i * 4 + 2];
        landmark.visibility = data[i * 4 + 3];
        _snapshots.set(i, landmark);
    }
}

void PoseRecording::add_snapshot(float x, float y, float depth, float visibility)
{
    _snapshots.push_back(PoseLandmark2D(x, y, depth, visibility));
}

void PoseRecording::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("get_data"), &PoseRecording::get_data);
    ClassDB::bind_method(D_METHOD("set_data"), &PoseRecording::set_data);
    ADD_PROPERTY(PropertyInfo(Variant::PACKED_FLOAT32_ARRAY, "data"), "set_data", "get_data");
}
