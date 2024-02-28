#pragma once
#include "../CameraManager.h"
class GameCamera : public Camera
{
public:
	GameCamera();
    ~GameCamera();

   void Start() override;

   void Update(float deltaTime) override;

   void OnDestroy() override;

    // Inherited via object
      void DrawProperties() override;
     void SceneDraw() override;
     void Render() override;

private:

    float time = 10;
    float lerpValue;
    float timeStep = 0;


    bool isReached = false;

    glm::vec3 startPosition = glm::vec3(0);
    glm::vec3 startRotation = glm::vec3(0);

    glm::vec3 endposition = glm::vec3(-1.37f, 0.85f, -15.01f);
    glm::vec3 endRotation = glm::vec3(17.50f, 180.0f, 0);

    glm::vec3 LerpObject(const glm::vec3& a, const glm::vec3& b, float t);


};

