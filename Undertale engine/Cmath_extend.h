#pragma once
#include <cmath>
#include <raylib.h>
#include <iostream>

class Cmath_extend {
public:

	float GetDistance(Vector2& vec1, Vector2& vec2) {
		return sqrt((vec1.x - vec2.x) * (vec1.x - vec2.x) + (vec1.y - vec2.y) * (vec1.y - vec2.y));
	}
	Vector2 GetVectorMove(Vector2 vec1, Vector2 vec2) {
		float Distance = this->GetDistance(vec1, vec2);
		float dx = (vec1.x - vec2.x) / Distance;
		float dy = (vec1.y - vec2.y) / Distance;
		return { dx, dy };
	}
	Vector2 MultiplyVector(Vector2& vec1, Vector2& vec2) {
		return { vec1.x *= vec2.x,
		vec1.y *= vec2.y };
	}
	Vector2 GetRotation(float angle) {
		float angleRadian = angle * 3.14159 / 180;
		float c = cos(angleRadian);
		float s = sin(angleRadian);
		return {
			c, s
		};

	}
	float GetGrad(Vector2& vec1, Vector2& vec2) {
		// Тригонометрия с треугольником ABC, где нужно нвйти угол точки vec1. 
		float BC = vec2.x - vec1.x;
		float BA = GetDistance(vec1, vec2);
		try {
			if (BA == 0) {
				throw std::runtime_error("Div on 0");
			}
		}
		catch (const std::exception& e) {
			std::cout << "Error: " << e.what() << std::endl;
		}
		float grad = std::atan((float)BC / (float)BA) * 180 / 3.14159;
		return grad;
	}
	
};

extern Cmath_extend math;