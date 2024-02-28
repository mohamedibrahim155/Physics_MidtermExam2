#pragma once
#include "Point.h"

struct Stick
{
	Stick() {};
	Stick(Point* _pointA, Point* _pointB) : pointA(_pointA), pointB(_pointB)
	{
		restLength = glm::distance(_pointA->position, _pointB->position);

		centre = (_pointA->position + _pointB->position) * 0.5f;
	};

	Point* pointA = nullptr;
	Point* pointB = nullptr;
	glm::vec3 centre;
	float restLength = 0;
	bool isActive = true;
	bool isLocked = false;
};