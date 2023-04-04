@tool
extends Control


const start_meta = "StartMetamark"
const target_meta = "TargetMetamark"

@onready
var start_picker = $StartPicker

@onready
var target_picker = $TargetPicker

var bone: Bone2D = null

var init_update: bool = false


func _ready() -> void:
	start_picker.changed.connect(update_bone)
	target_picker.changed.connect(update_bone)
	update_meta_editors()

func set_bone(new_bone: Bone2D) -> void:
	bone = new_bone
	init_update = false

func update_meta_editors() -> void:
	if bone != null:
		if bone.has_meta(start_meta):
			start_picker.load_metamark(bone.get_meta(start_meta))
		if bone.has_meta(target_meta):
			target_picker.load_metamark(bone.get_meta(target_meta))
		init_update = true

func update_bone() -> void:
	if init_update and bone != null:
		bone.set_meta(start_meta, start_picker.get_metamark())
		bone.set_meta(target_meta, target_picker.get_metamark())
