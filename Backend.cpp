#include "Backend.h"
#include <cmath>
int Backend::Backend_func(int x_, int y_, int width, int height, int pix_to_cm) {
	long double x, y;
	x = double(x_ - width / 2) / pix_to_cm;
	y = double(height / 2 - y_) / pix_to_cm;
	// Линия 1
	bool line1 = (y < x - 1 + 0.05) && (y > x - 1 - 0.05);
	bool under_line1 = y < x - 1;
	// Линия 2
	bool line2 = (6 * y <= -x - 22 + 0.15) && (6 * y >= -x - 22 - 0.15);
	bool under_line2 = 6 * y < -x - 22;
	// Парабола 1 - вдоль оси x
	bool parabole1 = (x <= 1.6 * y * y - 1.5 + 0.1) && (x >= 1.6 * y * y - 1.5 - 0.1);
	bool under_parabole1 = x > 1.6 * y * y - 1.5;
	// Парабола 2 - вдоль оси y
	bool parabole2 = (y <= -(x * x) - (8 * x) - 14 + 0.1) && (y >= -(x * x) - (8 * x) - 14 - 0.1);
	bool under_parabole2 = y < -(x * x) - (8 * x) - 14;
	// Прямоугольник
	bool rect = (x == 3 && y >= -2 && y <= 1) || (x == 5 && y >= -2 && y <= 1) || (y == 1 && x >= 3 && x <= 5) || (y == -2 && x >= 3 && x <= 5);
	bool in_rect = x > 3 && x < 5 && y > -2 && y < 1;
	// Ромб
	bool rhombus = (0.04 + 0.65 * abs(x - 1) + abs(y + 1.5) >= 1) && (0.65 * abs(x - 1) + abs(y + 1.5) - 0.04 <= 1);
	bool in_rhombus = 0.65 * abs(x - 1) + abs(y + 1.5) < 1;
	// Круг
	bool circle = ((x + 1.5) * (x + 1.5) + (y - 3) * (y - 3) + 0.1 >= 6.25) && ((x + 1.5) * (x + 1.5) + (y - 3) * (y - 3) - 0.1 <= 6.25);
	bool in_circle = (x + 1.5) * (x + 1.5) + (y - 3) * (y - 3) < 6.25;

	if (line1 || line2 || parabole1 || parabole2 || rect || rhombus || circle) {
		return 2;
	}
	if (!under_line1 && !under_parabole1 && x > 0) {
		return 1;
	}
	if (in_circle) {
		return 1;
	}
	if (under_parabole2 && !under_line2) {
		return 1;
	}
	if (in_rhombus && under_parabole1) {
		return 1;
	}
	if (in_rect && under_parabole1) {
		return 1;
	}
	if (!under_parabole1 && under_line1 && !under_parabole2 && !in_rhombus && !in_rect && y <= 1 && x>= - 3) {
		return 1;
	}
	return 0;
}