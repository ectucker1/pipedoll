@tool
extends Control


@onready
var bake_button: Button = find_child("Bake")

@onready
var input_line: LineEdit = find_child("InputOption")

@onready
var rig_line: LineEdit = find_child("RigOption")

@onready
var anim_line: LineEdit = find_child("AnimPlayerOption")

@onready
var scale_x_spinbox: SpinBox = find_child("ScaleXOption")

@onready
var scale_y_spinbox: SpinBox = find_child("ScaleYOption")

@onready
var rot_tolerance_spinbox: SpinBox = find_child("RotCompTolOption")

@onready
var lin_tolerance_spinbox: SpinBox = find_child("LinCompTolOption")


func _ready() -> void:
	bake_button.pressed.connect(_bake_pressed)
	
func _bake_pressed() -> void:
	var recording = load(input_line.text)
	if recording == null or not recording is PoseRecording:
		print("Recording not valid")
		return
	
	var rig_node = get_tree().get_edited_scene_root().get_node(rig_line.text)
	if rig_node == null:
		print("Rig not found")
		return
	
	var rig = PoseRig.new()
	rig.load_rig(rig_node, Vector2(scale_x_spinbox.value, scale_y_spinbox.value))
	
	var anim: AnimationPlayer = get_tree().get_edited_scene_root().get_node(anim_line.text)
	if anim == null or not anim is AnimationPlayer:
		print("Animation Player not found")
		return
	
	var anim_library = anim.get_animation_library("Recordings")
	var i = 1
	var anim_name = "Recording " + str(i)
	while i > 0:
		anim_name = "Recording " + str(i)
		i += 1
		if anim_library == null or not anim_library.has_animation(anim_name):
			i = 0
	
	PoseBaker.bake(recording, rig, anim, anim_name,
		rot_tolerance_spinbox.value,
		lin_tolerance_spinbox.value)
	
