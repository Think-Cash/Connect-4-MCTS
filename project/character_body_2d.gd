extends CharacterBody2D
@export var collision: Area2D
@export var glow : Sprite2D

var playerTurn := true
# default point off screen, will fail if spawn is equal to this value, e.g, not a slot
var coinSpawnPoint = Vector2(-100,0)

func _input(event):
	if event is InputEventMouse:
		position = event.position
func _physics_process(delta: float) -> void:
	var overlaps = collision.get_overlapping_bodies()
	if overlaps.is_empty():
		glow.position = Vector2(-100,0)
		coinSpawnPoint = Vector2(-100,0)
	for body in overlaps: 
		#print(body.name)
		glow.position = body.position
		coinSpawnPoint = glow.position
	# print(glow.position)
func get_current_slot() -> Vector2:
	return coinSpawnPoint
# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.
	

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta: float) -> void:
	pass
