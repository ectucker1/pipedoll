#ifndef POSE_RECORDING_H
#define POSE_RECORDING_H

#include "pose_snapshot.h"

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/templates/vector.hpp>

class PoseRecording : public godot::Resource
{
GDCLASS(PoseRecording, Resource);

private:
    godot::Vector<PoseSnapshot2D> _snapshots;

protected:
    static void _bind_methods();

public:
    godot::PackedFloat32Array get_data() const;
    void set_data(const godot::PackedFloat32Array& data);

    void add_snapshot(real_t timestep, const PoseLandmark2D (& landmarks)[33]);
    
    size_t count_snapshots() const;
    real_t get_time(size_t snapshot) const;
    godot::Vector2 get_position(size_t snapshot, size_t landmark) const;
    real_t get_depth(size_t snapshot, size_t landmark) const;
    real_t get_visibility(size_t snapshot, size_t landmark) const;
};

#endif // POSE_RECORDING_H
