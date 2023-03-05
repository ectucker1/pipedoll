@tool
extends EditorPlugin


var dock: Control
var dock_button: Button


func _enter_tree() -> void:
	dock = preload("res://addons/pipedoll/editor/dock.tscn").instantiate()
	dock_button = add_control_to_bottom_panel(dock, "Motion Capture")


func _exit_tree() -> void:
	if dock != null:
		remove_control_from_bottom_panel(dock)
		dock.queue_free()
	dock_button = null


func _get_plugin_name() -> String:
	return "PipeDoll"


func _get_plugin_icon():
	return get_editor_interface().get_base_control().get_theme_icon("Node", "EditorIcons")
