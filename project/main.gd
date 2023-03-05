extends Node

@onready
var pipe = MediaPipe.new()

func _ready():
	pipe.start()

func _process(delta: float) -> void:
	if (pipe.is_present()):
		print(pipe.first_landmark())
