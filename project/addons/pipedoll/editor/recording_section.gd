@tool
extends Control


@onready
var pipe = MediaPipe.new()

@onready
var arm_button: Button = find_child("Arm")

@onready
var start_button: Button = find_child("Start")

@onready
var pause_button: Button = find_child("Pause")

@onready
var stop_button: Button = find_child("Stop")

@onready
var output_line: LineEdit = find_child("OutputOption")


func _ready() -> void:
	arm_button.pressed.connect(_arm_pressed)
	start_button.pressed.connect(_start_pressed)
	pause_button.pressed.connect(_pause_pressed)
	stop_button.pressed.connect(_stop_pressed)

func _arm_pressed() -> void:
	pipe.load()
	arm_button.disabled = true
	start_button.disabled = false

func _start_pressed() -> void:
	pipe.start_record()
	start_button.disabled = true
	output_line.editable = false
	stop_button.disabled = false

func _pause_pressed() -> void:
	pass

func _stop_pressed() -> void:
	var recording = pipe.finish_record()
	stop_button.disabled = true
	start_button.disabled = false
	output_line.editable = true
	ResourceSaver.save(recording, "res://" + output_line.text, ResourceSaver.FLAG_BUNDLE_RESOURCES)
