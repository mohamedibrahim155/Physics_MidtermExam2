#pragma once
#include "../../Vertex.h"
#include <vector>
#include "Stick.h"

struct Stick;

struct VertexData
{
	VertexData() {};

	Vertex* vertex = nullptr;
	glm::vec3 offset;
};

struct Point
{
	//public:
	Point() {};
	Point(glm::vec3 position, glm::vec3 oldPostiion, std::vector<VertexData*> _vertex) :
		position(position), previousPosition(oldPostiion), vertex(_vertex)
	{
	}

	glm::vec3 position = glm::vec3(0);
	glm::vec3 previousPosition = glm::vec3(0);
	glm::vec3 velocity = glm::vec3(0);
	glm::vec3 centre = glm::vec3(0);
	 std::vector<VertexData*> vertex;
	 std::vector<Stick*> connectedSticks;
	bool locked = false;
	bool isActive = true;
	unsigned int indices = 0;
	void AddStick(Stick* stick)
	{
		connectedSticks.push_back(stick);
	}
	void AddIndices(unsigned int index)
	{
		indices = index;
	}

};


