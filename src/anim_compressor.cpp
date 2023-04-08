#include "anim_compressor.h"

#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void AnimCompressor::add_pos_sample(int32_t track, double time, Vector2 pos)
{
    auto frames = pos_tracks.find(track);
    if (frames == pos_tracks.end())
        frames = pos_tracks.insert(track, {});
    
    frames->value.push_back(PosKeyframe(time, pos));
}

void AnimCompressor::add_rot_sample(int32_t track, double time, double rot)
{
    auto frames = rot_tracks.find(track);
    if (frames == rot_tracks.end())
        frames = rot_tracks.insert(track, {});
    
    frames->value.push_back(RotKeyframe(time, rot));
}

static int pick_check_frame(int length, int iteration)
{
    if (length <= 2)
    {
        return -1;
    }

    // Half
    if (iteration == 0)
    {
        return length / 2;
    }
    // Quarters
    else if (iteration <= 3)
    {
        return (length / 4) * iteration;
    }
    // Eigths
    else if (iteration <= 10)
    {
        return (length / 8) * (iteration - 3);
    }
    // Straight iteration
    else if (iteration <= length + 10)
    {
        return iteration - 10;
    }
    else
    {
      return -1;
    }
}

static void compress_rot_track(Vector<RotKeyframe>& frames, double max_error)
{
    int i = 0;
    int check = 0;
    while (check != -1)
    {
        check = pick_check_frame(frames.size(), i);
        i += 1;
        if (check - 1 > 0 && check + 1 < frames.size())
        {
            const RotKeyframe& before = frames[check - 1];
            const RotKeyframe& sample = frames[check];
            const RotKeyframe& after = frames[check + 1];
            double interpolated = UtilityFunctions::lerp_angle(before.rot, after.rot, (sample.time - before.time) / (after.time - before.time));
            if (abs(interpolated - sample.rot) < max_error)
            {
                frames.remove_at(check);
                i = 0;
            }
        }
    }
}

static void compress_pos_track(Vector<PosKeyframe>& frames, double max_error)
{
    int i = 0;
    int check = 0;
    while (check != -1)
    {
        check = pick_check_frame(frames.size(), i);
        i += 1;
        if (check - 1 > 0 && check + 1 < frames.size())
        {
            const PosKeyframe& before = frames[check - 1];
            const PosKeyframe& sample = frames[check];
            const PosKeyframe& after = frames[check + 1];
            Vector2 interpolated = before.pos.lerp(after.pos, (sample.time - before.time) / (after.time - before.time));
            if (abs(interpolated.x - sample.pos.x) < max_error && abs(interpolated.y - sample.pos.y) < max_error)
            {
                frames.remove_at(check);
                i = 0;
            }
        }
    }
}

void AnimCompressor::compress(double max_rot_error, double max_pos_error)
{
    for (auto& pair : rot_tracks)
    {
        compress_rot_track(pair.value, max_rot_error);
    }
    for (auto& pair : pos_tracks)
    {
        compress_pos_track(pair.value, max_pos_error);
    }
}
