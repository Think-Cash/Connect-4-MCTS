#pragma once
#include <godot_cpp/classes/sprite2d.hpp>
#include <random>

namespace godot {

	class GDExample : public Sprite2D {
		GDCLASS(GDExample, Sprite2D)
	
	private:
		double time_passed;
		double speed;
		Vector2 position = Vector2(500.f, 0.f);
		
	protected:
		static void _bind_methods();

	public:
		GDExample();
		~GDExample();

		void _process(double delta) override;
		void set_speed(const double p_speed);
		int AIMove(const Array &board);
		double get_speed() const;
	};

} // namespace godot