#ifndef MEDIAPIPE_CLASS_H
#define MEDIAPIPE_CLASS_H

#ifdef WIN32
#include <windows.h>
#endif

#include <godot_cpp/classes/ref.hpp>

using namespace godot;

class IGMOD;

class MediaPipe : public RefCounted
{
    GDCLASS(MediaPipe, RefCounted);


    IGMOD* _igmod = nullptr;

    bool _present = false;
    Vector3 _first_landmark = { 0, 0, 0 };

protected:
    static void _bind_methods();

public:
    MediaPipe();
    ~MediaPipe();

    void start();
    void stop();

    bool is_present();
    Vector3 first_landmark();
};

#endif // MEDIAPIPE_CLASS_H