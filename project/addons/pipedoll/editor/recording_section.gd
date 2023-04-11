@tool
extends Control


@onready
var pipe = MediaPipe.new()

@onready
var arm_button: Button = find_child("Arm")

@onready
var disarm_button: Button = find_child("Disarm")

@onready
var start_button: Button = find_child("Start")

@onready
var stop_button: Button = find_child("Stop")

@onready
var output_line: LineEdit = find_child("OutputOption")


func _ready() -> void:
	arm_button.pressed.connect(_arm_pressed)
	disarm_button.pressed.connect(_disarm_pressed)
	start_button.pressed.connect(_start_pressed)
	stop_button.pressed.connect(_stop_pressed)
	pipe.loaded.connect(_loaded)

func _arm_pressed() -> void:
	pipe.load()
	arm_button.disabled = true
	stop_button.disabled = true

func _loaded() -> void:
	disarm_button.disabled = false
	start_button.disabled = false

func _disarm_pressed() -> void:
	pipe.unload()
	arm_button.disabled = false
	disarm_button.disabled = true
	start_button.disabled = true
	stop_button.disabled = true
	output_line.editable = true

func _start_pressed() -> void:
	pipe.start_record()
	start_button.disabled = true
	output_line.editable = false
	stop_button.disabled = false

func _stop_pressed() -> void:
	var recording = pipe.finish_record()
	stop_button.disabled = true
	start_button.disabled = false
	output_line.editable = true
	ResourceSaver.save(recording, "res://" + output_line.text, ResourceSaver.FLAG_BUNDLE_RESOURCES)
