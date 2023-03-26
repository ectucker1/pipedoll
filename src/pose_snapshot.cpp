#include "pose_snapshot.h"

using namespace godot;

size_t PoseSnapshot2D::float_size() const
{
    return 1 + 4 * 33;
}

void PoseSnapshot2D::append_to(PackedFloat32Array& data) const
{
    data.append(time);
    for (size_t i = 0; i < std::extent<decltype(landmarks)>::value; ++i)
    {
        landmarks[i].append_to(data);
    }
}

void PoseSnapshot2D::read_from(const PackedFloat32Array& data, size_t offset)
{
    time = data[offset];
    offset += 1;
    for (size_t i = 0; i < std::extent<decltype(landmarks)>::value; ++i)
    {
        landmarks[i].read_from(data, offset);
        offset += 4;
    }
}
