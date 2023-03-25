#ifndef POSE_LANDMARK_H
#define POSE_LANDMARK_H

#include <godot_cpp/variant/vector2.hpp>
#include "float32_serialize.h"

struct PoseLandmark2D : public Float32Serialize, public Float32Deserialize
{
    godot::Vector2 position;
    real_t depth;
    real_t visibility;

public:
    PoseLandmark2D() {}
    PoseLandmark2D(real_t x, real_t y, real_t depth, real_t visbility) :
        position(godot::Vector2(x, y)), depth(depth), visibility(visibility) {}
    
public:
    virtual size_t float_size() const override;
    virtual void append_to(godot::PackedFloat32Array& data) const override;
    virtual void read_from(const godot::PackedFloat32Array& data, size_t offset) override;
};

#endif // POSE_LANDMARK_H
