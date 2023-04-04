@tool
extends Control


const element_scene = preload("res://addons/pipedoll/editor/landmark_element.tscn")

@export
var prop_name := "Landmark"

@onready
var add_button := $RightLayout/AddButton

@onready
var landmark_list := $RightLayout/LandmarkList


signal changed()


func _ready() -> void:
	$Label.text = prop_name
	add_button.pressed.connect(_add_pressed)
	landmark_list.child_exiting_tree.connect(_list_child_removed)

func _add_pressed() -> void:
	var element = element_scene.instantiate()
	landmark_list.add_child(element)
	element.changed.connect(_child_changed)
	changed.emit()

func _child_changed() -> void:
	changed.emit()

func _list_child_removed(child: Node) -> void:
	_child_changed.call_deferred()

func get_metamark() -> String:
	var mark = ""
	for element in landmark_list.get_children():
		mark += str(element.get_landmark())
		mark += ","
	return mark

func load_metamark(meta: String) -> void:
	if get_metamark() == meta:
		return
	
	var marks = meta.split(",", false)
	for child in landmark_list.get_children():
		landmark_list.remove_child(child)
	for mark in marks:
		var element = element_scene.instantiate()
		landmark_list.add_child(element)
		element.set_landmark(int(mark))
		element.changed.connect(_child_changed)
