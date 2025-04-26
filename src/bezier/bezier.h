#ifndef MOUSE_SMOOTH_MOVEMENT_H_
#define MOUSE_SMOOTH_MOVEMENT_H_

#include <cmath>
#include <vector>
#include <Windows.h>

std::vector<POINT> calculate_bezier_curve(POINT start, POINT end, float control_x, float control_y, int num_points = 100) {
    std::vector<POINT> points;

    for (int i = 0; i <= num_points; i++) {
        float t = i / static_cast<float>(num_points);
        float u = 1.0f - t;

        float x = u * u * start.x + 2 * u * t * control_x + t * t * end.x;
        float y = u * u * start.y + 2 * u * t * control_y + t * t * end.y;

        points.push_back({ static_cast<LONG>(x), static_cast<LONG>(y) });
    }

    return points;
}

#endif // MOUSE_SMOOTH_MOVEMENT_H_
