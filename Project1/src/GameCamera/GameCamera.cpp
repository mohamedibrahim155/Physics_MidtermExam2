#include "GameCamera.h"
#include "../Time.h"
GameCamera::GameCamera()
{
}

GameCamera::~GameCamera()
{
}

void GameCamera::Start()
{
	startPosition = transform.position;
	startRotation = transform.rotation;
}

void GameCamera::Update(float deltaTime)
{
	if (isReached) return;

	float distance = glm::distance(transform.position, endposition);

	timeStep += Time::GetInstance().deltaTime / time;


	if (time == 0)
	{
		lerpValue = 1;
		timeStep = 1;
	}
	else
	{
		lerpValue = timeStep;
	}

	if (distance > 0.01f)
	{
		transform.SetRotation(LerpObject(transform.rotation, endRotation, lerpValue));

		transform.SetPosition(LerpObject(transform.position, endposition, lerpValue));
	}
	else
	{
		isReached = true;
	}
}

void GameCamera::OnDestroy()
{
}

void GameCamera::DrawProperties()
{
	Camera::DrawProperties();
}

void GameCamera::SceneDraw()
{
	Camera::SceneDraw();
}

void GameCamera::Render()
{

}

glm::vec3 GameCamera::LerpObject(const glm::vec3& a, const glm::vec3& b, float t)
{
	t = glm::clamp(t, 0.0f, 1.0f);

	return a + t * (b - a);
}
