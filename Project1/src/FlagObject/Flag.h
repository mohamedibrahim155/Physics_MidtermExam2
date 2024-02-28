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
};

