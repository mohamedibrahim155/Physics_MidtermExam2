#pragma once
#include "../Physics/SoftBody/SoftbodyObject.h"
#include "../InputManager/InputManager.h"
#include"../Math.h"


struct FlagVertex
{
	FlagVertex() {};
	FlagVertex(Vertex* vertex, glm::vec3 initialPosition) : vertex(vertex),
		initialPosition(initialPosition) {};

	Vertex* vertex;
	glm::vec3 initialPosition;

	unsigned int index;
};

class FlagObject : public SoftbodyObject, public iInputObserver
{
public: 
	FlagObject();
	~FlagObject();


	 void DrawProperties()override;
	 void SceneDraw()override;

	 void Start() override;
	 void Update(float deltaTime) override;
	 void Render() override;
	 void OnDestroy() override;

private: 
	
	bool isWindBlow = false;
	bool isBullet = false;
	float minX = -1.0f;
	float maxX = -5.0f;

	float maxZ;
	float minZ;


	glm::vec3 windOnAcceleration = glm::vec3(-2.0f, -1.0f, 0.7f);
	glm::vec3 windOffAcceleration = glm::vec3(0, -10.0f, 0);

	std::vector<Point*> listOfLockedPoints;

	std::vector<FlagVertex*> listOfFlagPositions;

	std::vector<Point*> listOfRemovePointsIndices;
	std::vector<glm::vec3> listOfBulletPositions;
	std::vector<unsigned int> meshIndices;

	void AddLockedPoints();

	void GetRandomSpherePointed();

	void LockNodes(bool isLocked);
	void InitalizeFlag();
	void ReConstruct();
	void SetMeshVerticesPosition();

	// Inherited via iInputObserver
	void OnKeyPressed(const int& key) override;

	void OnKeyReleased(const int& key) override;

	void OnKeyHold(const int& key) override;

	void AddRemoveIndicesNode(Point* node);

	void SetShaderValues();


};

