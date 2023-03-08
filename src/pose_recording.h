#ifndef POSE_RECORDING_H
#define POSE_RECORDING_H

#include "pose_landmark.h"

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/templates/vector.hpp>

using namespace godot;

class PoseRecording : public Resource
{
GDCLASS(PoseRecording, Resource);

private:
    Vector<PoseLandmark2D> _snapshots;

protected:
    static void _bind_methods();

public:
    PackedFloat32Array get_data() const;
    void set_data(const PackedFloat32Array& data);

    void add_snapshot(float x, float y, float depth, float visibility);
};

#endif // POSE_RECORDING_H
