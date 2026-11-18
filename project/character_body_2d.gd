extends CharacterBody2D
@export var collision: Area2D
@export var glow : Sprite2D
func _input(event):
	if event is InputEventMouse:
		position = event.position
func _physics_process(delta: float) -> void:
	var overlaps = collision.get_overlapping_bodies()
	if overlaps.is_empty():
		glow.position = Vector2(-100,0)
	for body in overlaps: 
		print(body.name)
		glow.position = body.position
	print(glow.position)
# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.
	

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta: float) -> void:
	pass
