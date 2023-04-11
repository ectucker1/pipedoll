@tool
extends LineEdit


func _can_drop_data(at_position, data) -> bool:
	return data["type"] == "files" and data["files"].size() == 1

func _drop_data(at_position, data) -> void:
	text = data["files"][0]
