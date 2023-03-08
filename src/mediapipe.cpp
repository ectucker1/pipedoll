#include "mediapipe.h"

#include "pose_recording.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/project_settings.hpp>
#include <godot_cpp/core/mutex_lock.hpp>

#include <gmod_api.h>
#include <framework/formats/landmark.pb.h>

using namespace godot;

MediaPipe::MediaPipe() : _recording(memnew(PoseRecording))
{
    _igmod = CreateGMOD();
}

MediaPipe::~MediaPipe()
{
    _igmod->stop();
}

void MediaPipe::load()
{
    _igmod->set_camera_props(0, 640, 480, 30);
    _igmod->set_camera(true);
    _igmod->set_overlay(true);

    auto obs = _igmod->create_observer("pose_landmarks");
    obs->SetPresenceCallback([=](class IObserver* observer, bool present){
        this->_is_present.store(present);
    });
    obs->SetPacketCallback([=](class IObserver* observer){ 
        const mediapipe::NormalizedLandmarkList* data = (mediapipe::NormalizedLandmarkList*)(observer->GetData()); 
        
        if (this->_is_recording.load())
        {
            MutexLock lock(_recording_lock);

            this->_recording->add_snapshot(
                data->landmark(0).x(),
                data->landmark(0).y(),
                data->landmark(0).z(),
                data->landmark(0).visibility()
            );
        }
    });

    String path = ProjectSettings::get_singleton()->globalize_path("res://mediapipe_graphs/pose_tracking/pose_tracking_cpu.pbtxt");
    CharString asciiPath = path.ascii();
    _igmod->start(asciiPath.get_data());
}

void MediaPipe::start_record()
{
    _is_recording.store(true);
}

Ref<PoseRecording> MediaPipe::finish_record()
{
    MutexLock lock(_recording_lock);

    _is_recording.store(false);

    Ref<PoseRecording> _temp = _recording;
    _recording = Ref<PoseRecording>(nullptr);
    return _temp;
}

bool MediaPipe::is_present()
{
    return _is_present.load();
}

bool MediaPipe::is_recording()
{
    return _is_recording.load();
}

void MediaPipe::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("load"), &MediaPipe::load);
    ClassDB::bind_method(D_METHOD("is_present"), &MediaPipe::is_present);
    ClassDB::bind_method(D_METHOD("is_recording"), &MediaPipe::is_recording);
    ClassDB::bind_method(D_METHOD("start_record"), &MediaPipe::start_record);
    ClassDB::bind_method(D_METHOD("finish_record"), &MediaPipe::finish_record);
}
