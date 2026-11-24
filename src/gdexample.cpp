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

int GDExample::AIMove(const Array &board) {
	int slot = 0;
	slot = dist(mt);
	return slot;
}