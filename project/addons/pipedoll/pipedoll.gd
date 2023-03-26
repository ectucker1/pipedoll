@tool
extends EditorPlugin


var dock: Control
var dock_button: Button


func _enter_tree() -> void:
	dock = preload("res://addons/pipedoll/editor/dock.tscn").instantiate()
	dock_button = add_control_to_bottom_panel(dock, "Motion Capture")
	add_tool_menu_item("Create Pose Rig", Callable(self, "create_pose_rig"))


func _exit_tree() -> void:
	if dock != null:
		remove_control_from_bottom_panel(dock)
		dock.queue_free()
	dock_button = null
	remove_tool_menu_item("Create Pose Rig")


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
		
		add_pose2d_node(rig, "nose")
		add_pose2d_node(rig, "left_eye_inner")
		add_pose2d_node(rig, "left_eye")
		add_pose2d_node(rig, "left_eye_outer")
		add_pose2d_node(rig, "right_eye_inner")
		add_pose2d_node(rig, "right_eye")
		add_pose2d_node(rig, "right_eye_outer")
		add_pose2d_node(rig, "left_ear")
		add_pose2d_node(rig, "right_ear")
		add_pose2d_node(rig, "mouth_left")
		add_pose2d_node(rig, "mouth_right")
		add_pose2d_node(rig, "left_shoulder")
		add_pose2d_node(rig, "right_shoulder")
		add_pose2d_node(rig, "left_elbow")
		add_pose2d_node(rig, "right_elbow")
		add_pose2d_node(rig, "left_wrist")
		add_pose2d_node(rig, "right_wrist")
		add_pose2d_node(rig, "left_pinky")
		add_pose2d_node(rig, "right_pinky")
		add_pose2d_node(rig, "left_index")
		add_pose2d_node(rig, "right_index")
		add_pose2d_node(rig, "left_thumb")
		add_pose2d_node(rig, "right_thumb")
		add_pose2d_node(rig, "left_hip")
		add_pose2d_node(rig, "right_hip")
		add_pose2d_node(rig, "left_knee")
		add_pose2d_node(rig, "right_knee")
		add_pose2d_node(rig, "left_ankle")
		add_pose2d_node(rig, "right_ankle")
		add_pose2d_node(rig, "left_heel")
		add_pose2d_node(rig, "right_heel")
		add_pose2d_node(rig, "left_foot_index")
		add_pose2d_node(rig, "right_foot_index")

func add_pose2d_node(root: Node, landmark: String) -> void:
	var node = Marker2D.new()
	root.add_child(node)
	node.owner = get_tree().get_edited_scene_root()
	node.name = landmark
	node.position = Vector2.ZERO
