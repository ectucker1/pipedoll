extends Bone2D


func _ready():
	set_autocalculate_length_and_angle(get_autocalculate_length_and_angle())
	
	var dir = Vector2(0.1, -1).normalized()
	var angle = atan2(dir.y, dir.x)
	
	print(angle)
	print(get_bone_angle())
	
	global_rotation = angle - get_bone_angle()
