#pragma once
#include "../../model.h"
#include "../PhysicsCollisionTypes.h"
#include"../PhysicsObject.h"
#include "Stick.h"



enum class BodyType
{
	CLOTH = 0,
	SPRING = 1
};

class SoftbodyObject : public Model
{
public:
	SoftbodyObject();
	~SoftbodyObject();

	bool showDebug = true;

	bool isSoftBodyActive = true;

	float gravity = 0.1f /*-9.81f*/;
	glm::vec3 acceleration = glm::vec3(0, -10.0f, 0);
	BodyType type = BodyType::CLOTH;

	std::vector<Triangle> listOfTriangles;
	std::vector<Point*> listOfPoints;
	std::vector<Stick*> listOfSticks;
	std::vector<Triangle> GetTriangleList();

	void Initialize();
	void CalculateCloth();
	void CalculateSpring();
	void SetupPoints(std::vector<Vertex>& vertices);
	void SetupSticks(std::shared_ptr<Mesh>& mesh, unsigned int& currentMeshIndex);


	virtual void DrawProperties()override;
	virtual void SceneDraw()override;

	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	virtual void OnDestroy() override;

	void UpdateVerlet(float deltaTime);
	void UpdateSticks(float deltaTime);
	void UpdatePoints(float deltaTime);

	void CollisionTest();
	void UpdateVertices();


	void UpdateNormals();

	void UpdateClothVertices();
	void UpdateSpringVertices();

	void CleanZeros(glm::vec3& value);
	void AddLockSphere(glm::vec3 centre, float radius);

	PhysicsObject* updateAABBTest = nullptr;
private:


	float renderRadius = 0.025f;
	float tightnessFactor = 1;
	float lockRadius;
	const double MAX_DELTATIME = 1.0 / 60.0;

	glm::vec3 downVector = glm::vec3(0, -1, 0);
	glm::vec3 lockSphereCenter;
	
	bool CheckSoftBodyAABBCollision(Point* point, const cAABB& aabb);
	bool CheckSoftBodySphereCollision(Point* point, const cSphere& sphere);
	void HandleSoftBodySphereCollision(Point*& point, const cSphere& sphere);
	//bool CheckSoftBodyAABBCollision(const cAABB& aabb);
	

	void HandleSoftBodyAABBCollision(Point& particle, const cAABB& aabb);

	bool IsPointLocked(Point* point, glm::vec3 centre, float radius);

};

