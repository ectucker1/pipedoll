
#include "pose_landmark.h"

using namespace godot;

size_t PoseLandmark2D::float_size() const
{
    return 4;
}

void PoseLandmark2D::append_to(PackedFloat32Array& data) const
{
    data.append(position.x);
    data.append(position.y);
    data.append(depth);
    data.append(visibility);
}

void PoseLandmark2D::read_from(const PackedFloat32Array& data, size_t offset)
{
    position = Vector2(data[offset + 0], data[offset + 1]);
    depth = data[offset + 2];
    visibility = data[offset + 3];
}
