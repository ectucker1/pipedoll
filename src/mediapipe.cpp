#include "mediapipe.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/project_settings.hpp>
#include <gmod_api.h>
#include <framework/formats/landmark.pb.h>

using namespace godot;

MediaPipe::MediaPipe()
{
    _igmod = CreateGMOD();
}

MediaPipe::~MediaPipe()
{
    stop();
}

void MediaPipe::start()
{
    _igmod->set_camera_props(0, 640, 480, 30);
    _igmod->set_camera(true);
    _igmod->set_overlay(true);

    auto obs = _igmod->create_observer("face_landmarks");
    obs->SetPresenceCallback([=](class IObserver* observer, bool present){
        this->_present = present;
    });
    obs->SetPacketCallback([=](class IObserver* observer){ 
        const mediapipe::NormalizedLandmarkList* data = (mediapipe::NormalizedLandmarkList*)(observer->GetData()); 
        this->_first_landmark = { data->landmark(0).x(), data->landmark(0).y(), data->landmark(0).z() };
    });

    String path = ProjectSettings::get_singleton()->globalize_path("res://mediapipe_graphs/holistic_tracking/holistic_tracking_cpu.pbtxt");
    CharString asciiPath = path.ascii();
    _igmod->start(asciiPath.get_data());
}

void MediaPipe::stop()
{
    _igmod->stop();
}

bool MediaPipe::is_present()
{
    return _present;
}

Vector3 MediaPipe::first_landmark()
{
    return _first_landmark;
}

void MediaPipe::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("start"), &MediaPipe::start);
    ClassDB::bind_method(D_METHOD("stop"), &MediaPipe::stop);
    ClassDB::bind_method(D_METHOD("is_present"), &MediaPipe::is_present);
    ClassDB::bind_method(D_METHOD("first_landmark"), &MediaPipe::first_landmark);
}
