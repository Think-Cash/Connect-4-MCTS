#include "gdexample.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void GDExample::_bind_methods() {

	ClassDB::bind_method(D_METHOD("get_speed"), &GDExample::get_speed);
	ClassDB::bind_method(D_METHOD("AIMove", "board"), &GDExample::AIMove);
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
		print_line("top space is " + String(top_space) + " slot is " + String::num_int64(slot));
	}
	while (int(top_space) != 0);//then cast it and hope for the best
		
	return slot;
}