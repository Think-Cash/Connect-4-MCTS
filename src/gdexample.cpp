#include "gdexample.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void GDExample::_bind_methods() {

	ClassDB::bind_method(D_METHOD("get_speed"), &GDExample::get_speed);
	ClassDB::bind_method(D_METHOD("AIMove", "board"), &GDExample::AIMove);
	ClassDB::bind_method(D_METHOD("WinCheck", "board", "slot"), &GDExample::WinCheck);
	ClassDB::bind_method(D_METHOD("set_speed", "p_speed"), &GDExample::set_speed);

	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "speed", PROPERTY_HINT_RANGE, "0,1000,0.01"), "set_speed", "get_speed");
}

GDExample::GDExample() {
	// Initialize any variables here.
	time_passed = 0.0;
}

GDExample::~GDExample() {
	// Add your cleanup here.
}

void GDExample::_process(double delta) {
	time_passed += speed * delta;

	Vector2 new_position = Vector2(position.x, position.y + time_passed);

	set_position(new_position);
}

void GDExample::set_speed(const double p_speed) {
	speed = p_speed;
}

double GDExample::get_speed() const {
	return speed;
}

int GDExample::AIMove(Array board) {
	int slot = 0;
	std::random_device rand;
	std::mt19937 mt(rand());
	std::uniform_int_distribution<int> dist(0, 6);
	Array top_row;//to use a 2d array from godot in c++ you have to first break it down
	Variant top_space;//then grab it as a variant, which is a mystery box that could contain any type
	do {
		slot = dist(mt);
		top_row = board[5];
		top_space = top_row[slot];
		//print_line("top space is " + String(top_space) + " slot is " + String::num_int64(slot));
	}
	while (int(top_space) != 0);//then cast it and hope for the best
		
	return slot;
}

bool GDExample::WinCheck(Array board, int slot) {//check if a winning move was made
	//Find where the piece landed
	int player;// 1 for AI 2 for Player
	int2 piecePosition = {-1,-1};//row, column
	Array current_row;
	Variant current_space;

	for (int i = 5; i >= 0; i--) {
		current_row = board[i];
		current_space = current_row[slot];
		if (int(current_space) != 0) {
			player = int(current_space);
			piecePosition = {i, slot};
			print_line("piece position is " + String::num_int64(piecePosition.x) + ", " + String::num_int64(piecePosition.y));
			break;
		}
		else  if (i == 0){
			print_line("ERROR no free space found in GD::Example::WinCheck for slot " + String::num_int64(slot));
			return false;
		}
	}
	//Check if horizontal win
	Variant check_slot;
	int left_matches = 0;
	int right_matches = 0;
	for (int i = 1; i < 4; i++) {
		if (slot + i > 5) {
			break;
		}
		check_slot = current_row[slot + i];
		if (int(check_slot) != player) {
			right_matches = i - 1;//there isn't 4 pieces to the right but we'll add them in case there are more to the left. -1 because the for loop starts at 1
			break;
		}
		else if (i == 3) {
			return true;//if it counts 3 ahead and determines all 4 in a row are this player's colour, it's a win
		}
	}
	for (int i = 1; i < 4; i++) {
		if (slot - i < 0) {
			break;
		}
		check_slot = current_row[slot - i];
		if (int(check_slot) != player) {
			left_matches = i - 1;
			break;
		}
		else if (i == 3) {
			return true;
		}
	}
	if (left_matches + right_matches >= 4) {
		print_line("Middle piece in a horizontal line");
		return true;
	}
	
	//Check for vertical wins
	int verticalCount = 0;
	for (int i = 5; i >= 0; i--) {
		current_row = board[i];
		check_slot = current_row[slot];
		if (int(check_slot) != player) {
			verticalCount = 0;
		}
		else {
			verticalCount++;
		}
		if (verticalCount == 4) {
			print_line("Vertical line");
			return true;
		}
	}

	//Check for diagonal wins part 1 (bottom left to top right)
	int up_slope_count = 0;
	//North East 
	for (int i = 1; i < 6; i++) {//longest diagonal straight in connect 4 is 6 spaces so 5 discluding the player slot
		if (piecePosition.x + i > 5 || slot + i > 6) {
			up_slope_count = i - 1;
			break;
		}
		current_row = board[piecePosition.x + i];
		check_slot = current_row[slot + i];
		if (int(check_slot) != player) {
			up_slope_count = i - 1;
			break;	
		}
		else if (i == 3) {
			return true;
		}
	}
	//South West
	for (int i = 1; i < 6; i++) {//longest diagonal straight in connect 4 is 6 spaces so 5 discluding the player slot
		if (piecePosition.x - i < 0 || slot - i < 0) {
			up_slope_count = i - 1;
			break;
		}
		current_row = board[piecePosition.x - i];
		check_slot = current_row[slot - i];
		if (int(check_slot) != player) {
			up_slope_count += i - 1;
			break;	
		}
		else if (i == 3) {
			return true;
		}
	}
	if (up_slope_count >= 4) {
		print_line("Upwards slope diagonal win");
		return true;
	}

	//Part 2 top left to bottom right
	int down_slope_count = 0;
	//North West (200)
	for (int i = 1; i < 6; i++) {//longest diagonal straight in connect 4 is 6 spaces so 5 discluding the player slot
		if (piecePosition.x + i > 5 || slot - i < 0) {
			down_slope_count = i - 1;
			break;
		}
		current_row = board[piecePosition.x + i];
		check_slot = current_row[slot - i];
		if (int(check_slot) != player) {
			down_slope_count = i - 1;
			break;	
		}
		else if (i == 3) {
			return true;
		}
	}
	//South East
	for (int i = 1; i < 6; i++) {//longest diagonal straight in connect 4 is 6 spaces so 5 discluding the player slot
		if (piecePosition.x - i < 0 || slot + i > 6) {
			down_slope_count = i - 1;
			break;
		}
		current_row = board[piecePosition.x - i];
		check_slot = current_row[slot + i];
		if (int(check_slot) != player) {
			down_slope_count += i - 1;
			break;	
		}
		else if (i == 3) {
			return true;
		}
	}
	if (down_slope_count >= 4) {
		print_line("Downwards slope diagonal win");
		return true;
	}
	print_line("No win detected, Play continues");
	return false;//if you get this far there's no more hope for the win
}