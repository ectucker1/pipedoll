#include "register_types.h"

#include "pose_recording.h"
#include "mediapipe.h"
#include "pose_rig.h"
#include "pose_baker.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

using namespace godot;

void initialize_pipedoll_types(ModuleInitializationLevel p_level)
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
	ClassDB::register_class<PoseRecording>();
	ClassDB::register_class<PoseRig>();
	ClassDB::register_class<PoseBaker>();
	ClassDB::register_class<MediaPipe>();
}

void uninitialize_pipedoll_types(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}

extern "C"
{

	// Initialization.

	GDExtensionBool GDE_EXPORT pipedoll_library_init(const GDExtensionInterface *p_interface, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization)
	{
		GDExtensionBinding::InitObject init_obj(p_interface, p_library, r_initialization);

		init_obj.register_initializer(initialize_pipedoll_types);
		init_obj.register_terminator(uninitialize_pipedoll_types);
		init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

		return init_obj.init();
	}
}
