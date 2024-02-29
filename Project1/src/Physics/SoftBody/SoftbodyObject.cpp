#include "SoftbodyObject.h"
#include "../PhysicsEngine.h"
SoftbodyObject::SoftbodyObject()
{
	name = "Softbody";
}

SoftbodyObject::~SoftbodyObject()
{
	listOfTriangles.clear();
}

std::vector<Triangle> SoftbodyObject::GetTriangleList()
{
    return listOfTriangles;
}

void SoftbodyObject::Initialize()
{
	
	switch (type)
	{
	case BodyType::CLOTH:
		CalculateCloth();
		break;
	case BodyType::SPRING:
		CalculateSpring();
		break;
	default:
		break;
	}
	

	PhysicsEngine::GetInstance().AddSoftBodyObject(this);

}



void SoftbodyObject::CalculateCloth()
{


	listOfPoints.clear();
	listOfSticks.clear();


	unsigned int meshIndex = 0;
	for (std::shared_ptr<Mesh> mesh : meshes)
	{
		

		for (size_t index = 0; index < mesh->vertices.size(); index++)
		{
			glm::vec4 vertexMatrix = glm::vec4(mesh->vertices[index].Position.x,
				mesh->vertices[index].Position.y,
				mesh->vertices[index].Position.z, 1.0f);

			vertexMatrix = transform.GetModelMatrix() * vertexMatrix;


			mesh->vertices[index].Position.x = vertexMatrix.x;
			mesh->vertices[index].Position.y = vertexMatrix.y;
			mesh->vertices[index].Position.z = vertexMatrix.z;


		}


		SetupPoints(mesh->vertices);

		SetupSticks(mesh, meshIndex);  // need to check with  meshcount>1 


		meshIndex++;

	}
}

void SoftbodyObject::CalculateSpring()
{
	listOfPoints.clear();
	listOfSticks.clear();

	glm::mat4 modelMat  = transform.GetModelMatrix();

	for (std::shared_ptr<Mesh> mesh : meshes)
	{

		
		glm::vec3 totalPositions = glm::vec3(0);

		Point* point = new Point();


		for (size_t index = 0; index < mesh->vertices.size(); index++)
		{

			totalPositions += mesh->vertices[index].Position;

			VertexData* temp = new VertexData();


			temp->vertex = &mesh->vertices[index];

			point->vertex.push_back(temp);
		}

		point->centre = totalPositions / (float)point->vertex.size();


		for (size_t i = 0; i < point->vertex.size(); i++)
		{
			point->vertex[i]->offset = point->vertex[i]->vertex->Position - point->centre;
		}


	

		for (size_t index = 0; index < mesh->vertices.size(); index++)
		{

			glm::vec3 transformedPosition = modelMat * glm::vec4(mesh->vertices[index].Position, 1);

			mesh->vertices[index].Position = transformedPosition;


		}



		point->position = modelMat * glm::vec4(point->centre, 1);

		point->previousPosition = point->position;

		listOfPoints.push_back(point);
	}

	for (int i = 0; i < meshes.size() - 1; i++)
	{

		Point* pointA = listOfPoints[i];
		Point* pointB = listOfPoints[i + 1];

		Stick* stick = new Stick(pointA, pointB);

		listOfSticks.push_back(stick);

	}



	//listOfPoints.reserve(vertices.size());

	//for (Vertex& vertex : vertices)
	//{
	//	Point* temp = new Point(vertex.Position, vertex.Position, { &vertex });
	//	listOfPoints.push_back(temp);
	//}
}

void SoftbodyObject::SetupPoints(std::vector<Vertex>& vertices)
{
	listOfPoints.reserve(vertices.size());

	for (Vertex& vertex : vertices)
	{
		VertexData* vertexData = new VertexData();

		vertexData->vertex = &vertex;

		Point* temp = new Point(vertex.Position, vertex.Position, { vertexData });
		listOfPoints.push_back(temp);
	}


}

void SoftbodyObject::SetupSticks(std::shared_ptr<Mesh>& mesh, unsigned int& currentMeshIndex)
{
	for (size_t i = 0; i < mesh->indices.size(); i += 3)
	{


		Point* point1 = listOfPoints[mesh->indices[currentMeshIndex +i]];  
		Point* point2 = listOfPoints[mesh->indices[currentMeshIndex+ i + 1]];
		Point* point3 = listOfPoints[mesh->indices[currentMeshIndex+ i + 2]];

		//point1->AddIndices(mesh->indices[currentMeshIndex + i]);
		//point2->AddIndices(mesh->indices[currentMeshIndex + i+1]);
		//point3->AddIndices(mesh->indices[currentMeshIndex + i+2]);

		point1->AddIndices(currentMeshIndex + i);
		point2->AddIndices(currentMeshIndex + i + 1);
		point3->AddIndices(currentMeshIndex + i + 2);

		Stick* edge1 = new Stick(point1, point2);

		point1->AddStick(edge1);
		point2->AddStick(edge1);

		listOfSticks.push_back(edge1);

		Stick* edge2 = new Stick(point2, point3);

		point2->AddStick(edge2);
		point3->AddStick(edge2);

		listOfSticks.push_back(edge2);

		Stick* edge3 = new Stick(point3, point1);

		point3->AddStick(edge3);
		point1->AddStick(edge3);

		listOfSticks.push_back(edge3);

	}
}



void SoftbodyObject::DrawProperties()
{
    Model::DrawProperties();

	if (!ImGui::TreeNodeEx("Softbody properties", ImGuiTreeNodeFlags_DefaultOpen))
	{
		return;
	}

	ImGui::Text("Show Debug");
	ImGui::SameLine();
	ImGui::Checkbox("##ShowDebug" , &showDebug);
	
	ImGui::Text("tightnessFactor");
	ImGui::SameLine();
	ImGui::SetNextItemWidth(150);
	ImGui::InputFloat("##tightnessFactor", &tightnessFactor,0,0.1,"%.2f");

	ImGui::Text("LockRadius");
	ImGui::SameLine();
	ImGui::SetNextItemWidth(150);
	ImGui::InputFloat("##lockRadius", &lockRadius, 0, 0.1, "%.2f");

	

	ImGui::SetNextItemWidth(80);
	ImGui::Text("LockCentre");
	ImGui::SameLine();
	ImGui::Text("X");
	ImGui::SameLine();
	ImGui::SetNextItemWidth(80);
	ImGui::DragFloat("##X" ,&lockSphereCenter.x);
	ImGui::SameLine();
	ImGui::Text("Y");
	ImGui::SameLine();
	ImGui::SetNextItemWidth(80);
	ImGui::DragFloat("###Y", &lockSphereCenter.y);
	ImGui::SameLine();
	ImGui::Text("Z");
	ImGui::SameLine();
	ImGui::SetNextItemWidth(80);
	ImGui::DragFloat("###Z", &lockSphereCenter.z);


	ImGui::NewLine();
	ImGui::TreePop();

	if (!ImGui::TreeNodeEx("List of points ", ImGuiTreeNodeFlags_OpenOnArrow))
	{
		return;
	}
	for (int i = 0; i < listOfPoints.size(); ++i)
	{
		Point*& point = listOfPoints[i];

		
		ImGui::Text("locked");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(80);
		ImGui::Checkbox(("##locked" + std::to_string(i)).c_str(), &point->locked);




		ImGui::SetNextItemWidth(80);
		ImGui::Text("points");
		ImGui::SameLine();
		ImGui::Text("X");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(80);
		ImGui::DragFloat(("##X" + std::to_string(i)).c_str(), &point->position.x);
		ImGui::SameLine();
		ImGui::Text("Y");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(80);
		ImGui::DragFloat(("###Y" + std::to_string(i)).c_str(), &point->position.y);
		ImGui::SameLine();
		ImGui::Text("Z");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(80);
		ImGui::DragFloat(("###Z" + std::to_string(i)).c_str(), &point->position.z);

		ImGui::NewLine();
	}
	ImGui::TreePop();

}

void SoftbodyObject::SceneDraw()
{
    Model::SceneDraw();
}

void SoftbodyObject::Start()
{
}

void SoftbodyObject::Update(float deltaTime)
{ 
	//UpdateVerlet(deltaTime);  // disable as of now
}

void SoftbodyObject::Render()
{
	if (!showDebug) return;


	for (Point* point : listOfPoints)
	{
		GraphicsRender::GetInstance().DrawSphere(point->position, renderRadius, glm::vec4(0, 1, 1, 1), true);
	}

	for (Stick* stick : listOfSticks)
	{
		//GraphicsRender::GetInstance().DrawLine(stick->pointA->position, stick->pointB->position, glm::vec4(1, 1, 0, 1));
	}
	
	GraphicsRender::GetInstance().DrawSphere(lockSphereCenter, lockRadius, glm::vec4(1, 0, 1, 1), true);
}

void SoftbodyObject::OnDestroy()
{
}

void SoftbodyObject::UpdateVerlet(float deltaTime)
{
	
	UpdatePoints(deltaTime);
	CollisionTest();
	UpdateSticks(deltaTime);
	UpdateVertices();
}

void SoftbodyObject::UpdateSticks(float deltaTime)
{
	const unsigned int MAX_ITERATION = 10;

	for (size_t i = 0; i < MAX_ITERATION; i++)
	{
		for (Stick* stick : listOfSticks)
		{
			if (stick->isActive)
			{

				Point* pointA = stick->pointA;
				Point* pointB = stick->pointB;
				//// FEENEY's
				glm::vec3 delta = pointB->position - pointA->position;
				float deltaLength = glm::length(delta);

				if (deltaLength != 0)
				{
					float diff = (deltaLength - stick->restLength) / deltaLength;

					if (diff > 0.1f)
					{
						stick->isActive = false;
					}
				
					if (!pointA->locked) pointA->position += delta * 0.5f * diff * tightnessFactor;
					
					if (!pointB->locked) pointB->position -= delta * 0.5f * diff * tightnessFactor;
				

					CleanZeros(pointA->position);
					CleanZeros(pointB->position);
				}


				//SEBASTIAN's
				/*glm::vec3 centre = (pointA->position + pointB->position) * 0.5f;

				glm::vec3 direction = glm::normalize(pointA->position - pointB->position);

				if (glm::length(direction)!=0)
				{
					if (!pointA->locked)
					{
						stick->pointA->position = centre + direction * (stick->restLength * 0.5f);
					}

					if (!pointB->locked)
					{
						stick->pointB->position = centre - direction * (stick->restLength *0.5f );
					}

				}*/


			}
		
		}
	}

}

void SoftbodyObject::UpdatePoints(float deltaTime)
{
	if (deltaTime > MAX_DELTATIME)
	{
		deltaTime = MAX_DELTATIME;
	}

	for (Point* point : listOfPoints)
	{
		if (!point->locked)
		{
			glm::vec3 currentPosition = point->position;
			glm::vec3 prevPosition = point->previousPosition;

			glm::vec3 direction = currentPosition - prevPosition;

			
			
				//point->position += (direction) + (glm::vec3(0, -gravity, 0) * (float)(deltaTime * deltaTime));

			if (point->isActive)
			{
				point->position += (direction)+acceleration * (float)(deltaTime * deltaTime) * 0.98f;

				point->previousPosition = currentPosition;


				/*if (CheckSoftBodyAABBCollision(point,updateAABBTest->UpdateAABB()))
				{
					std::cout << "CollisionDetected" << std::endl;
					handleSoftBodyAABBCollision(*point, updateAABBTest->UpdateAABB());
				}
				else*/
				/*{
					point->position += (point->position - point->previousPosition);

					point->position += downVector * gravity * (deltaTime * deltaTime);

				}


				point->previousPosition = currentPosition;*/

				CleanZeros(point->position);
				CleanZeros(point->previousPosition);
			}
				
		}

	}

}



void SoftbodyObject::CollisionTest()
{
	//for (Point* point : listOfPoints)
	//{
	//	if (point->position.y < -5.0f)
	//	{
	//		point->position.y = -5.0f;
	//	}
	//}

	for (Point* point : listOfPoints)
	{
		/*if (CheckSoftBodyAABBCollision(point, updateAABBTest->UpdateAABB()))
		{
			handleSoftBodyAABBCollision(*point,updateAABBTest->UpdateAABB());
			std::cout << "Collision Detected" << std::endl;
		}*/
		/*cSphere sphere = updateAABBTest->UpdateSphere();
		if (CheckSoftBodySphereCollision(point, sphere))
		{
			HandleSoftBodySphereCollision(point, sphere);
		}*/
	}

	

	//for (Point* point : listOfPoints)
	//{
	//	glm::vec3 sphereCentre = glm::vec3(0.0f, -2, 0);
	//	float sphereRadius = 1;

	//	float distanceToSphere = glm::distance(point->position,
	//		sphereCentre);
	//	if (distanceToSphere < sphereRadius)
	//	{
	//		// it's 'inside' the sphere
	//		// Shift or slide the point along the ray from the centre of the sphere
	//		glm::vec3 particleToCentreRay = point->position - sphereCentre;
	//		// Normalize to get the direction
	//		particleToCentreRay = glm::normalize(particleToCentreRay);


	//		if (glm::length(particleToCentreRay)!=0)
	//		{
	//			point->position = (particleToCentreRay * sphereRadius) + sphereCentre;
	//		}
	//		
	//	

	//	}
	//}

//	return;

}

void SoftbodyObject::CleanZeros(glm::vec3& value)
{
	// 1.192092896e�07F 
	const float minFloat = 1.192092896e-07f;
	if ((value.x < minFloat) && (value.x > -minFloat))
	{
		value.x = 0.0f;
	}
	if ((value.y < minFloat) && (value.y > -minFloat))
	{
		value.y = 0.0f;
	}
	if ((value.z < minFloat) && (value.z > -minFloat))
	{
		value.z = 0.0f;
	}
}

void SoftbodyObject::AddLockSphere(glm::vec3 centre, float radius)
{
	lockSphereCenter = centre;
	lockRadius = radius;

	for (Point* point : listOfPoints)
	{
		if (point->locked)
		{
			continue;
		}
		point->locked = IsPointLocked(point, centre, radius);
	}
}

void SoftbodyObject::UpdateVertices()
{
	
	switch (type)
	{
	case BodyType::CLOTH:
		UpdateClothVertices();
		break;
	case BodyType::SPRING:
		UpdateSpringVertices();
		break;
	default:
		break;
	}
	

	UpdateNormals();

	for (std::shared_ptr<Mesh> mesh: meshes)
	{
		mesh->UpdateVertices();
	}
}

void SoftbodyObject::UpdateNormals()
{
	for (std::shared_ptr<Mesh> mesh : meshes)
	{

		for (size_t i = 0; i < mesh->vertices.size(); i++)
		{
			mesh->vertices[i].Normal = glm::vec3(0);
		}
	}

	for (std::shared_ptr<Mesh> mesh : meshes)
	{
		for (size_t i = 0; i < mesh->indices.size(); i += 3)
		{
			unsigned int vertAIndex = mesh->indices[i + 0];
			unsigned int vertBIndex = mesh->indices[i + 1];
			unsigned int vertCIndex = mesh->indices[i + 2];


			Vertex& vertexA = mesh->vertices[vertAIndex];
			Vertex& vertexB = mesh->vertices[vertBIndex];
			Vertex& vertexC = mesh->vertices[vertCIndex];

			glm::vec3 vertA = vertexA.Position;
			glm::vec3 vertB = vertexB.Position;
			glm::vec3 vertC = vertexC.Position;

			glm::vec3 triangleEdgeAtoB = vertB - vertA;
			glm::vec3 triangleEdgeAtoC = vertC - vertA;


			glm::vec3 normal = glm::normalize(glm::cross(triangleEdgeAtoB, triangleEdgeAtoC));

			//normal = glm::normalize(normal);

			CleanZeros(normal);

			//if (glm::length(normal)!=0)
			{
				vertexA.Normal.x += normal.x;
				vertexA.Normal.y += normal.y;
				vertexA.Normal.z += normal.z;

				vertexB.Normal.x += normal.x;
				vertexB.Normal.y += normal.y;
				vertexB.Normal.z += normal.z;

				vertexC.Normal.x += normal.x;
				vertexC.Normal.y += normal.y;
				vertexC.Normal.z += normal.z;
			}

			

		}
		
	}


	for (std::shared_ptr<Mesh> mesh : meshes)
	{

		/*for (size_t i = 0; i < mesh->vertices.size(); i++)
		{
			glm::vec3 normal = glm::vec3(mesh->vertices[i].Normal.x,
				mesh->vertices[i].Normal.y,
				mesh->vertices[i].Normal.z);

			normal = glm::normalize(normal);

			if (glm::length(normal) != 0)
			{
				mesh->vertices[i].Normal.x = normal.x;
				mesh->vertices[i].Normal.y = normal.y;
				mesh->vertices[i].Normal.z = normal.z;
			}
			

		}*/
	}
	

}

void SoftbodyObject::UpdateClothVertices()
{
	glm::mat4 modelInversematrix = transform.GetModelInverseMatrix();

	for (Point* point : listOfPoints)
	{
		glm::vec4 vertexMatrix = glm::vec4(point->position, 1.0f);


		vertexMatrix = modelInversematrix * vertexMatrix;

		point->vertex[0]->vertex->Position = glm::vec3(vertexMatrix.x, vertexMatrix.y, vertexMatrix.z);
	}
}

void SoftbodyObject::UpdateSpringVertices()
{
	glm::mat4 modelInversematrix = transform.GetModelInverseMatrix();

	for (Point* point : listOfPoints)
	{
		for (size_t i = 0; i < point->vertex.size(); i++)
		{

			glm::vec3 transformPosition = modelInversematrix * glm::vec4((point->position), 1);

			transformPosition += point->vertex[i]->offset;

			point->vertex[i]->vertex->Position = glm::vec3(transformPosition.x, transformPosition.y, transformPosition.z);
		}
	}
}


bool SoftbodyObject::CheckSoftBodyAABBCollision(Point* particle, const cAABB& aabb)
{

	return (
		particle->position.x >= aabb.minV.x && particle->position.x <= aabb.maxV.x &&
		particle->position.y >= aabb.minV.y && particle->position.y <= aabb.maxV.y &&
		particle->position.z >= aabb.minV.z && particle->position.z <= aabb.maxV.z
		);
	
}

bool SoftbodyObject::CheckSoftBodySphereCollision(Point* point, const cSphere& sphere)
{

	float distance = glm::distance(point->position,	sphere.center);

	return distance < sphere.radius;
}

void SoftbodyObject::HandleSoftBodySphereCollision(Point*& point, const cSphere& sphere)
{
	//float distance = glm::distance(point->position, sphere.center);

	//if (distance < sphere.radius)
	{
		glm::vec3 particleToCentreRay = point->position - sphere.center;
		// Normalize to get the direction
		particleToCentreRay = glm::normalize(particleToCentreRay);


		if (glm::length(particleToCentreRay) != 0)
		{
			point->position = (particleToCentreRay * sphere.radius) + sphere.center;
		}
	}
	

	//return;
}

void SoftbodyObject::HandleSoftBodyAABBCollision(Point& point,const cAABB& aabb)
{
	//
		/*if (point.position.x < aabb.minV.x)
		{
			point.position.x = aabb.minV.x;
		}
		else if (point.position.x > aabb.maxV.x) 
		{
			point.position.x = aabb.maxV.x;
		}

		if (point.position.y < aabb.minV.y) 
		{
			point.position.y = aabb.minV.y;
		}
		else if (point.position.y > aabb.maxV.y) 
		{
			point.position.y = aabb.maxV.y;
		}

		if (point.position.z < aabb.minV.z) 
		{
			point.position.z = aabb.minV.z;
		}
		else if (point.position.z > aabb.maxV.z) 
		{
			point.position.z = aabb.maxV.z;
		}*/

	point.position.x = glm::clamp(point.position.x, aabb.minV.x, aabb.maxV.x);
	point.position.y = glm::clamp(point.position.y, aabb.minV.y, aabb.maxV.y);
	point.position.z = glm::clamp(point.position.z, aabb.minV.z, aabb.maxV.z);

	//point.position.y = glm::clamp(point.position.y, aabb.minV.y, aabb.maxV.y);
		// 
		// point.position = glm::vec
		
}

bool SoftbodyObject::IsPointLocked(Point* point, glm::vec3 centre, float radius)
{
	float distance = glm::distance(point->position, centre);
	return distance < radius;
}
