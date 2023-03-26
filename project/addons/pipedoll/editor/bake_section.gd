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
var height_spinbox: SpinBox = find_child("HeightOption")


func _ready() -> void:
	bake_button.pressed.connect(_bake_pressed)
	
func _bake_pressed() -> void:
	var recording = load("res://" + input_line.text)
	if recording == null or not recording is PoseRecording:
		print("Recording not valid")
		return
	
	var rig = get_tree().get_edited_scene_root().get_node(rig_line.text)
	if rig == null:
		print("Rig not found")
		return
	if rig.get_child_count() < 33:
		print("Rig too small")
		return
	
	print(rig.get_child_count())
	
	var anim: AnimationPlayer = get_tree().get_edited_scene_root().get_node(anim_line.text)
	if anim == null or not anim is AnimationPlayer:
		print("Animation Player not found")
		return
	
	var i = 1
	var anim_name = "Recording " + str(i)
	while i > 0:
		anim_name = "Recording " + str(i)
		i += 1
		if not anim.has_animation(anim_name):
			i = 0
	
	var height = height_spinbox.value
	
	PoseBaker.bake(recording, rig, anim, anim_name, height)
	
