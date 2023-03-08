extends PanelContainer


func _enter_tree() -> void:
	add_theme_stylebox_override("panel", get_theme_stylebox("panel", "TabContainer"))
