#ifndef MEDIAPIPE_CLASS_H
#define MEDIAPIPE_CLASS_H

#include <atomic>

#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/mutex.hpp>

using namespace godot;

class IGMOD;
class PoseRecording;

class MediaPipe : public RefCounted
{
    GDCLASS(MediaPipe, RefCounted);

private:
    IGMOD* _igmod = nullptr;

    std::atomic_bool _is_loaded;

    std::atomic_bool _is_present;

    std::atomic_bool _is_recording;

    Mutex _recording_lock;

    Ref<PoseRecording> _recording;

protected:
    static void _bind_methods();

public:
    MediaPipe();
    ~MediaPipe();

    void load();
    void unload();

    void start_record();
    Ref<PoseRecording> finish_record();

    bool is_present();
    bool is_recording();
};

#endif // MEDIAPIPE_CLASS_H