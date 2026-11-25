extends Node2D
@export var coin_scene : PackedScene
@export var player : Node2D
@export var AI : GDExample
@onready var timer := $Timer 
var spr_yellow_coin = preload('res://Sprites/YellowCoin.png')
var playerTurn := true
var newCoin
var board = []
# Stores how many coins are inserted to a given column
static var height: Array[int] = [0,0,0,0,0,0,0]
#yellow coin = 1 red = 2, empty = 0
func updateBoard(yellowCoin: bool, slotValue: float) -> void:
	var slot := -1
	if yellowCoin:
		slot = slotValue
	elif slotValue < -30:
		slot = 0
	elif slotValue < -20:
		slot = 1
	elif slotValue < -10:
		slot = 2
	elif slotValue < 5:
		slot = 3
	elif slotValue < 15:
		slot = 4
	elif slotValue < 30: 
		slot = 5
	else:
		slot = 6
	if height[slot] == 6:
		print("ERROR - Column full")
		return
	board[height[slot]][slot] = 1 if yellowCoin else 2
	height[slot] += 1
	print("---------------------")
	for i in range (5,-1,-1):
			print(board[i])
	playerTurn = !playerTurn
	if !playerTurn:
		updateBoard(true, AI.AIMove(board))
	else:
		spawnAICoin(slot)
func _unhandled_input(event) -> void:
	if event is InputEventMouseButton and event.button_index == MOUSE_BUTTON_LEFT and event.pressed and playerTurn and timer.is_stopped():
		newCoin = coin_scene.instantiate() as Node2D
		newCoin.global_position = player.get_current_slot() * 10
		add_child(newCoin)
		updateBoard(false, player.get_current_slot().x)
		timer.start()
func spawnAICoin(slot: int):
	newCoin = coin_scene.instantiate() as Node2D
	var coinPos = Vector2(0,-202)
	match (slot):
		0: coinPos.x = -365
		1: coinPos.x = -245
		2: coinPos.x = -125
		3: coinPos.x = -5
		4: coinPos.x = 115
		5: coinPos.x = 235
		6: coinPos.x = 355
	newCoin.global_position = coinPos 
	add_child(newCoin)
	var newCoinSprite: Sprite2D = newCoin.get_node("Coin/Sprite2D")
	newCoinSprite.texture = spr_yellow_coin
# Called when the node enters the scene tree for the first time.
func _ready():
	for i in range(6): 
		board.append([])
		for j in range(7): 
			board[i].append(0)


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta):
	pass
