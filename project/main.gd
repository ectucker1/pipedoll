extends Node

@onready
var pipe = MediaPipe.new()

var recording: PoseRecording

func _ready():
	pipe.load()

func _input(event):
	if event.is_action_released("test_record_start"):
		pipe.start_record()
	elif event.is_action_released("test_record_stop"):
		recording = pipe.finish_record()

func _process(delta: float) -> void:
	print(pipe.is_recording())
