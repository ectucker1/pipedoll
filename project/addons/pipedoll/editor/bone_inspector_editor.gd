@tool
extends EditorInspectorPlugin


const landmark_editor_scene = preload("res://addons/pipedoll/editor/bone_landmark_editor.tscn")


func _can_handle(object: Object) -> bool:
	return object is Bone2D

func _parse_category(object: Object, category: String) -> void:
	if "Bone" in category:
		var editor = landmark_editor_scene.instantiate()
		add_custom_control(editor)
		editor.set_bone(object)
