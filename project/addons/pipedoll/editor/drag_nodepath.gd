@tool
extends LineEdit


func _can_drop_data(at_position, data) -> bool:
	return data["type"] == "nodes" and data["nodes"].size() == 1

func _drop_data(at_position, data) -> void:
	text = get_tree().get_edited_scene_root().get_path_to(get_node(data["nodes"][0]))
