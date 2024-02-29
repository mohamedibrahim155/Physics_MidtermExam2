#include "Flag.h"
#include "../Time.h"

using namespace MathUtils;

FlagObject::FlagObject()
{
	name = "Flag";


    //std::string flagTexturePath = "Textures/FLAG2.png";
    std::string flagTexturePath = "Textures/Flag.png";
    Texture* flagTexture = new Texture(flagTexturePath);

    std::string flagTextureOpacityPath = "Textures/FlagOpacity.png";
    Texture* flagopacityTexture = new Texture(flagTextureOpacityPath);

   // SoftbodyObject* softBodyTest1 = new SoftbodyObject();
   // softBodyTest1->name = "Flag";


    //LoadModel("Models/Plane/FlagPlane10x10.fbx");
   // LoadModel("Models/Plane/Plane10x10.ply");
   // LoadModel("Models/Plane/IBU10x10.ply");
    LoadModel("Models/Plane/IBU_HighPoly10x10.ply");
  //  LoadModel("Models/Plane/Flag.ply");
    acceleration = glm::vec3(0, -10, 0.2f);
    meshes[0]->meshMaterial->material()->diffuseTexture = flagTexture;
    meshes[0]->meshMaterial->material()->alphaTexture = flagopacityTexture;
    meshes[0]->meshMaterial->material()->useMaskTexture = true;

    //softBodyTest1->LoadModel("Models/DefaultCube/DefaultCube.fbx");
 //  transform.SetPosition(glm::vec3(-1.30f, 5.00f, -4.60f));
   transform.SetPosition(glm::vec3(-2.0f, 5.10f, -4.60f));
   //  transform.SetPosition(glm::vec3(-0.10f, 4.50f, -4.60f));  //50x50
     //softBodyTest1->transform.SetPosition(glm::vec3(0, 1, 0));
     //softBodyTest1->transform.SetScale(glm::vec3(5));

   transform.SetRotation(glm::vec3(0, 180.00, 0));
    transform.SetScale(glm::vec3(40, 40, 1));
    GraphicsRender::GetInstance().AddModelAndShader(this, GraphicsRender::GetInstance().flagShader);
    showDebug = false;


 
   
    Initialize();

    /*meshes[0]->indices.erase(std::remove(meshes[0]->indices.begin(),meshes[0]->indices.end(),
        meshes[0]->indices[0]), meshes[0]->indices.end());

    meshes[0]->indices.erase(std::remove(meshes[0]->indices.begin(), meshes[0]->indices.end(),
        meshes[0]->indices[0]), meshes[0]->indices.end());


    meshes[0]->indices.erase(std::remove(meshes[0]->indices.begin(), meshes[0]->indices.end(),
        meshes[0]->indices[0]), meshes[0]->indices.end());

    meshes[0]->indices.erase(std::remove(meshes[0]->indices.begin(), meshes[0]->indices.end(),
        meshes[0]->indices[0]), meshes[0]->indices.end());

    meshes[0]->indices.erase(std::remove(meshes[0]->indices.begin(), meshes[0]->indices.end(),
        meshes[0]->indices[0]), meshes[0]->indices.end());

    meshes[0]->indices.erase(std::remove(meshes[0]->indices.begin(), meshes[0]->indices.end(),
        meshes[0]->indices[0]), meshes[0]->indices.end());

    meshes[0]->indices.erase(std::remove(meshes[0]->indices.begin(), meshes[0]->indices.end(),
        meshes[0]->indices[0]), meshes[0]->indices.end());

    meshes[0]->indices.erase(std::remove(meshes[0]->indices.begin(), meshes[0]->indices.end(),
        meshes[0]->indices[0]), meshes[0]->indices.end());

    meshes[0]->indices.erase(std::remove(meshes[0]->indices.begin(), meshes[0]->indices.end(),
        meshes[0]->indices[0]), meshes[0]->indices.end());

    meshes[0]->indices.erase(std::remove(meshes[0]->indices.begin(), meshes[0]->indices.end(),
        meshes[0]->indices[0]), meshes[0]->indices.end());

    meshes[0]->indices.erase(std::remove(meshes[0]->indices.begin(), meshes[0]->indices.end(),
        meshes[0]->indices[0]), meshes[0]->indices.end());

    meshes[0]->indices.erase(std::remove(meshes[0]->indices.begin(), meshes[0]->indices.end(),
        meshes[0]->indices[0]), meshes[0]->indices.end());

    meshes[0]->indices.erase(std::remove(meshes[0]->indices.begin(), meshes[0]->indices.end(),
        meshes[0]->indices[0]), meshes[0]->indices.end());*/


    ///*softBodyTest1->AddLockSphere(glm::vec3(0.100f, 5.500, -4.6f), 0.20f);
    //softBodyTest1->AddLockSphere(glm::vec3(0.100f, 5.12f,-4.6f), 0.20f);
    //softBodyTest1->AddLockSphere(glm::vec3(0.100f, 4.9f, -4.6f), 0.20f);
    //softBodyTest1->*/AddLockSphere(glm::vec3(0.100f, 4.6f, -4.6f), 0.20f);



    AddLockSphere(glm::vec3(0.100f, 5.7f, -4.6f), 0.25f);
    AddLockSphere(glm::vec3(0.100f, 5.12f, -4.6f), 0.25f);
    AddLockSphere(glm::vec3(0.100f, 4.9f, -4.6f), 0.25f);
    AddLockSphere(glm::vec3(0.100f, 4.5f, -4.6f), 0.25f);

    AddLockedPoints();

    InitalizeFlag();

    InputManager::GetInstance().AddObserver(this);

}

FlagObject::~FlagObject()
{
}

void FlagObject::DrawProperties()
{
    SoftbodyObject::DrawProperties();

    ImGui::Text("Acceleration");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(80);
    ImGui::DragFloat("###AccelerationX", &acceleration.x);
    ImGui::SameLine();
    ImGui::SetNextItemWidth(80);
    ImGui::DragFloat("###AccelerationY", &acceleration.y);
    ImGui::SameLine();
    ImGui::SetNextItemWidth(80);
    ImGui::DragFloat("###AccelerationZ", &acceleration.z);
}

void FlagObject::SceneDraw()
{
    SoftbodyObject::SceneDraw();
}

void FlagObject::Start()
{
   // acceleration = windOffAcceleration;
}

void FlagObject::Update(float deltaTime)
{
    
    SetShaderValues();
}

void FlagObject::Render()
{
	SoftbodyObject::Render();
}

void FlagObject::OnDestroy()
{
}

void FlagObject::AddLockedPoints()
{
    for (Point* pointsLocked : listOfPoints)
    {
        if (pointsLocked->locked)
        {
            listOfLockedPoints.push_back(pointsLocked);
        }
    }
}

void FlagObject::GetRandomSpherePointed()
{
    glm::mat4 modelTransformedMatrix = transform.GetModelMatrix();

    int randomIndex = Math::GetRandomIntNumber(0, listOfSticks.size() - 1);

    Stick* stick = listOfSticks[randomIndex];
   
   // Stick* stick4 = listOfSticks[randomIndex];

    glm::vec3 sphereCenter = stick->centre;

    float radius = 0.5f;

    std::vector<Stick*> listOfRandomSticks;
    for (Stick* mStick : listOfSticks)
    {
        if (glm::distance(mStick->centre, sphereCenter) < radius) 
        {
            //mStick->isActive = false;

            listOfRandomSticks.push_back(mStick);
        }
    }



#pragma region TEST_ERROR



    /*for (Stick*& disconnect : listOfRandomSticks)
    {
        disconnect->isActive = false;

        for (Stick* connectedStick : disconnect->pointA->connectedSticks)
        {
            if (connectedStick == disconnect)
            {
                continue;
            }
            else
            {
                connectedStick->isActive = false;
                AddRemoveIndicesNode(disconnect->pointA);
            }
        }


        for (Stick* connectedStick : disconnect->pointB->connectedSticks)
        {
            if (connectedStick == disconnect)
            {
                continue;
            }
            else
            {

                connectedStick->isActive = false;
                AddRemoveIndicesNode(disconnect->pointB);


            }
        }


    }*/
 

    //std::vector<unsigned int> ::iterator it;
    //unsigned int currentRemoveIndex = 0;
    //std::vector<unsigned int> alreadyRemovedIndex;

    //for (Point* point : listOfRemovePointsIndices)
    //{
    //    //unsigned int removeIndex = point->indices;

    //    //for (unsigned int index : alreadyRemovedIndex)
    //    //{
    //    //    if (index == removeIndex)
    //    //    {
    //    //        continue;
    //    //    }
    //    //}

    //    //if (removeIndex < meshes[0]->indices.size()) 
    //    //{
    //    //    
    //    //    meshes[0]->indices.erase(meshes[0]->indices.begin() + (removeIndex - currentRemoveIndex));

    //    //    alreadyRemovedIndex.push_back(removeIndex);

    //    //    currentRemoveIndex++;
    //    //}



    //   
    //
    //}
    //listOfRemovePointsIndices.clear();
#pragma endregion

    for (Stick* mStick : listOfRandomSticks)
    {
       
        listOfBulletPositions.push_back(mStick->pointA->position);

        return;
    }

   // GraphicsRender::GetInstance()
  
    isBullet = true;
    //SetShaderValues(glm::vec3());

}

void FlagObject::LockNodes(bool isLocked)
{
    for (Point* lockedPoint : listOfLockedPoints)
    {
        lockedPoint->locked = isLocked;
    }
}

void FlagObject::InitalizeFlag()
{
    glm::mat4 inverse = transform.GetModelInverseMatrix();

    for (std::shared_ptr<Mesh> mesh :  meshes)
    {
        listOfFlagPositions.reserve(mesh->vertices.size());

        for (Vertex& vertex : mesh->vertices)
        {
            glm::vec3 vertexPosition = inverse * glm::vec4(vertex.Position, 1);

            FlagVertex* temp = new FlagVertex(&vertex, vertexPosition);

            listOfFlagPositions.push_back(temp);
        }

        for (unsigned int& index : mesh->indices)
        {
            meshIndices.push_back(index);
        }

    }



}

void FlagObject::ReConstruct()
{
   
    isWindBlow = false;

    acceleration = isWindBlow ? windOnAcceleration : windOffAcceleration;

    listOfBulletPositions.clear();

    SetMeshVerticesPosition();
    
    CalculateCloth();


    AddLockSphere(glm::vec3(0.100f, 5.7f, -4.6f), 0.25f);
    AddLockSphere(glm::vec3(0.100f, 5.12f, -4.6f), 0.25f);
    AddLockSphere(glm::vec3(0.100f, 4.9f, -4.6f), 0.25f);
    AddLockSphere(glm::vec3(0.100f, 4.5f, -4.6f), 0.25f);

    AddLockedPoints();

    LockNodes(true);
}

void FlagObject::SetMeshVerticesPosition()
{
    glm::mat4 modelTransform = transform.GetModelMatrix();

    for (FlagVertex* flagvertex : listOfFlagPositions )
    {
        glm::vec3 position = modelTransform * glm::vec4(flagvertex->initialPosition, 1);

        flagvertex->vertex->Position = flagvertex->initialPosition;
    }

    //listOfFlagPositions.clear();

    for (std::shared_ptr<Mesh> mesh : meshes)
    {
        mesh->indices = meshIndices;
    }
}




void FlagObject::OnKeyPressed(const int& key)
{
    if (key == GLFW_KEY_2)
    {
        isWindBlow = !isWindBlow;

       // glm::vec3 acceleration = glm::vec3(-2, -1.0f, 0.7f);
        acceleration = isWindBlow ? windOnAcceleration : windOffAcceleration;
    }

    if (key == GLFW_KEY_3)
    {
        GetRandomSpherePointed();
    }

    if (key == GLFW_KEY_4)
    {
        LockNodes(false);
    }
    if (key == GLFW_KEY_5)
    {
        ReConstruct();
    }

    if (key == GLFW_KEY_RIGHT)
    {
        acceleration.x -= 0.5f;
    }
}

void FlagObject::OnKeyReleased(const int& key)
{
}

void FlagObject::OnKeyHold(const int& key)
{
}

void FlagObject::AddRemoveIndicesNode(Point* node)
{
    std::vector<Point*>::iterator it = std::find(listOfRemovePointsIndices.begin(),
        listOfRemovePointsIndices.end(), node);

    if (it == listOfRemovePointsIndices.end())
    {
        listOfRemovePointsIndices.push_back(node);
    }
      
  
}

void FlagObject::SetShaderValues()
{

    for (size_t i = 0; i < listOfBulletPositions.size(); i++)
    {
        GraphicsRender::GetInstance().flagShader->Bind();

        std::string uniform = "sphere[" + std::to_string(i) + "].sphereCentre";

        GraphicsRender::GetInstance().flagShader->setVec3(uniform, listOfBulletPositions[i]);
        GraphicsRender::GetInstance().flagShader->setFloat("radius", 0.1f);
    }
   
}
