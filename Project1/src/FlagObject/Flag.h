#pragma once
#include "../Physics/SoftBody/SoftbodyObject.h"
#include "../InputManager/InputManager.h"
#include"../Math.h"

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

	float minX = -1.0f;
	float maxX = -5.0f;

	float maxZ;
	float minZ;


	glm::vec3 windOnAcceleration = glm::vec3(-2.0f, -1.0f, 0.7f);
	glm::vec3 windOffAcceleration = glm::vec3(0, -10.0f, 0);

	std::vector<Point*> lockedPointsList;

	// Inherited via iInputObserver
	void AddAllLockedNodes();

	void GetRandomSpherePointed();

	void DisconnectFlag();
	void OnKeyPressed(const int& key) override;

	void OnKeyReleased(const int& key) override;

	void OnKeyHold(const int& key) override;

};

