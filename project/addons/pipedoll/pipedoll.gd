@tool
extends EditorPlugin


var dock: Control
var dock_button: Button
var landmark_editor: EditorInspectorPlugin


func _enter_tree() -> void:
	dock = preload("res://addons/pipedoll/editor/dock.tscn").instantiate()
	dock_button = add_control_to_bottom_panel(dock, "Motion Capture")
	add_tool_menu_item("Create Pose Rig", Callable(self, "create_pose_rig"))
	landmark_editor = preload("res://addons/pipedoll/editor/bone_inspector_editor.gd").new()
	add_inspector_plugin(landmark_editor)


func _exit_tree() -> void:
	if dock != null:
		remove_control_from_bottom_panel(dock)
		dock.queue_free()
	dock_button = null
	remove_tool_menu_item("Create Pose Rig")
	remove_inspector_plugin(landmark_editor)


func _get_plugin_name() -> String:
	return "PipeDoll"


func _get_plugin_icon():
	return get_editor_interface().get_base_control().get_theme_icon("Node", "EditorIcons")


func create_pose_rig() -> void:
	var selected = get_editor_interface().get_selection().get_selected_nodes()
	if selected.size() == 1:
		var rig = selected.front()
		for child in rig.get_children():
			rig.remove_child(child)
		
		add_pose2d_node(rig, 0, "nose")
		add_pose2d_node(rig, 1, "left_eye_inner")
		add_pose2d_node(rig, 2, "left_eye")
		add_pose2d_node(rig, 3, "left_eye_outer")
		add_pose2d_node(rig, 4, "right_eye_inner")
		add_pose2d_node(rig, 5, "right_eye")
		add_pose2d_node(rig, 6, "right_eye_outer")
		add_pose2d_node(rig, 7, "left_ear")
		add_pose2d_node(rig, 8, "right_ear")
		add_pose2d_node(rig, 9, "mouth_left")
		add_pose2d_node(rig, 10, "mouth_right")
		add_pose2d_node(rig, 11, "left_shoulder")
		add_pose2d_node(rig, 12, "right_shoulder")
		add_pose2d_node(rig, 13, "left_elbow")
		add_pose2d_node(rig, 14, "right_elbow")
		add_pose2d_node(rig, 15, "left_wrist")
		add_pose2d_node(rig, 16, "right_wrist")
		add_pose2d_node(rig, 17, "left_pinky")
		add_pose2d_node(rig, 18, "right_pinky")
		add_pose2d_node(rig, 19, "left_index")
		add_pose2d_node(rig, 20, "right_index")
		add_pose2d_node(rig, 21, "left_thumb")
		add_pose2d_node(rig, 22, "right_thumb")
		add_pose2d_node(rig, 23, "left_hip")
		add_pose2d_node(rig, 24, "right_hip")
		add_pose2d_node(rig, 25, "left_knee")
		add_pose2d_node(rig, 26, "right_knee")
		add_pose2d_node(rig, 27, "left_ankle")
		add_pose2d_node(rig, 28, "right_ankle")
		add_pose2d_node(rig, 29, "left_heel")
		add_pose2d_node(rig, 30, "right_heel")
		add_pose2d_node(rig, 31, "left_foot_index")
		add_pose2d_node(rig, 32, "right_foot_index")

func add_pose2d_node(root: Node, landmark: int, landmark_name: String) -> void:
	var bone = Bone2D.new()
	root.add_child(bone)
	bone.owner = get_tree().get_edited_scene_root()
	bone.name = landmark_name
	bone.set_meta("StartMetamark", str(landmark) + ",")
	if landmark != 0:
		bone.set_meta("TargetMetamark", "0,")
	else:
		bone.set_meta("TargetMetamark", "1,")
	bone.position = Vector2.ZERO
	bone.set_autocalculate_length_and_angle(false)
