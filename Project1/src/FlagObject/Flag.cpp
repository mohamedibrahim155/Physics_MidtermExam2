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
    acceleration = glm::vec3(-2, -1.0f, 0.7f);
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
    GraphicsRender::GetInstance().AddModelAndShader(this, GraphicsRender::GetInstance().alphaCutOutShader);
    showDebug = false;
    Initialize();

    ///*softBodyTest1->AddLockSphere(glm::vec3(0.100f, 5.500, -4.6f), 0.20f);
    //softBodyTest1->AddLockSphere(glm::vec3(0.100f, 5.12f,-4.6f), 0.20f);
    //softBodyTest1->AddLockSphere(glm::vec3(0.100f, 4.9f, -4.6f), 0.20f);
    //softBodyTest1->*/AddLockSphere(glm::vec3(0.100f, 4.6f, -4.6f), 0.20f);



    AddLockSphere(glm::vec3(0.100f, 5.7f, -4.6f), 0.30f);
    AddLockSphere(glm::vec3(0.100f, 5.12f, -4.6f), 0.30f);
    AddLockSphere(glm::vec3(0.100f, 4.9f, -4.6f), 0.30f);
    AddLockSphere(glm::vec3(0.100f, 4.5f, -4.6f), 0.30f);

    AddAllLockedNodes();

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
}

void FlagObject::Update(float deltaTime)
{
   
}

void FlagObject::Render()
{
	SoftbodyObject::Render();
}

void FlagObject::OnDestroy()
{
}

void FlagObject::AddAllLockedNodes()
{
    for (Point* pointsLocked : listOfPoints)
    {
        if (pointsLocked->locked)
        {
            lockedPointsList.push_back(pointsLocked);
        }
    }
}

void FlagObject::GetRandomSpherePointed()
{
    int randomIndex = Math::GetRandomIntNumber(0, listOfSticks.size() - 1);

    Stick* stick = listOfSticks[randomIndex];
   
   // Stick* stick4 = listOfSticks[randomIndex];

    glm::vec3 sphereCenter = stick->centre;

    float radius = 0.5f;

    std::vector<Stick*> localList;
    for (Stick* mStick : listOfSticks)
    {
        if (glm::distance(mStick->centre, sphereCenter) < radius) 
        {
            localList.push_back(mStick);

        }
    }

    for (Stick* mStick : localList)
    {
       // mStick->pointA->locked = true;
      //  mStick->pointB->locked = true;

        mStick->isActive = false;

    }
 

   

}

void FlagObject::DisconnectFlag()
{
    for (Point* lockedPoint : listOfPoints)
    {
        lockedPoint->locked = false;
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
        DisconnectFlag();
    }
}

void FlagObject::OnKeyReleased(const int& key)
{
}

void FlagObject::OnKeyHold(const int& key)
{
}
