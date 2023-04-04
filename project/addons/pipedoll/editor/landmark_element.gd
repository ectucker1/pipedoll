@tool
extends Control


@onready
var landmark_option = $LandmarkOption

@onready
var remove_button = $RemoveButton


signal changed()


func _ready() -> void:
	remove_button.pressed.connect(_remove_pressed)
	landmark_option.item_selected.connect(_item_selected)

func _remove_pressed() -> void:
	get_parent().remove_child.call_deferred(self)

func get_landmark() -> int:
	return landmark_option.get_selected_id()

func set_landmark(landmark: int) -> void:
	landmark_option.select(landmark)

func _item_selected(idx: int) -> void:
	changed.emit()
