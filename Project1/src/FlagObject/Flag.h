#pragma once
#include "../Physics/SoftBody/SoftbodyObject.h"
class FlagObject : public SoftbodyObject
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

	void OnAccelerationChange();
	float timeStep = 0;
	float time = 3;
	float lerpValue = 0;

	glm::vec3 LerpObject(const glm::vec3& a, const glm::vec3& b, float t);



};

