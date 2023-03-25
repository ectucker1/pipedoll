#ifndef POSE_SNAPSHOT_H
#define POSE_SNAPSHOT_H

#include "pose_landmark.h"
#include "float32_serialize.h"

struct PoseSnapshot2D : public Float32Serialize, public Float32Deserialize
{
    float time;
    PoseLandmark2D landmarks[33];

public:
    PoseSnapshot2D() {};
    PoseSnapshot2D(real_t timestep, const PoseLandmark2D (& marks)[33]) : time(time)
    {
        for (size_t i = 0; i < std::extent<decltype(landmarks)>::value; ++i)
        {
            landmarks[i] = marks[i];
        }
    }

public:
    virtual size_t float_size() const override;
    virtual void append_to(godot::PackedFloat32Array& data) const override;
    virtual void read_from(const godot::PackedFloat32Array& data, size_t offset) override;
};

#endif // POSE_SNAPSHOT_H