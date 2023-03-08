#ifndef POSE_LANDMARK_H
#define POSE_LANDMARK_H

#include <godot_cpp/variant/vector2.hpp>

using namespace godot;

struct PoseLandmark2D
{
    Vector2 position;
    real_t depth;
    real_t visibility;

    PoseLandmark2D() {}
    PoseLandmark2D(real_t x, real_t y, real_t depth, real_t visbility) :
        position(Vector2(x, y)), depth(depth), visibility(visibility) {}
};

#endif // POSE_LANDMARK_H
