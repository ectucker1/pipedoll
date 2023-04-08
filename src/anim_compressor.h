#ifndef ANIM_COMPRESSOR_H
#define ANIM_COMPRESSOR_H

#include <godot_cpp/variant/vector2.hpp>
#include <godot_cpp/templates/hash_map.hpp>
#include <godot_cpp/templates/vector.hpp>

class PoseRig;

struct PosKeyframe
{
    godot::Vector2 pos;
    double time;

    PosKeyframe(double time, godot::Vector2 pos) : time(time), pos(pos) {}
    PosKeyframe() {}
};

struct RotKeyframe
{
    double rot;
    double time;

    RotKeyframe(double time, double rot) : time(time), rot(rot) {}
    RotKeyframe() {}
};

class AnimCompressor
{
public:
    godot::HashMap<int32_t, godot::Vector<PosKeyframe>> pos_tracks;
    godot::HashMap<int32_t, godot::Vector<RotKeyframe>> rot_tracks;

public:
    void add_pos_sample(int32_t track, double time, godot::Vector2 pos);
    void add_rot_sample(int32_t track, double time, double rot);

    void compress(double max_rot_error, double max_pos_error);
};

#endif // ANIM_COMPRESSOR_H
