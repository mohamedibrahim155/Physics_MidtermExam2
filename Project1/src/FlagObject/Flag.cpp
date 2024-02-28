#include "Flag.h"
#include "../Time.h"
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
    LoadModel("Models/Plane/IBU10x10.ply");
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



    AddLockSphere(glm::vec3(0.100f, 5.500, -4.6f), 0.30f);
    AddLockSphere(glm::vec3(0.100f, 5.12f, -4.6f), 0.30f);
    AddLockSphere(glm::vec3(0.100f, 4.9f, -4.6f), 0.30f);
    AddLockSphere(glm::vec3(0.100f, 4.6f, -4.6f), 0.30f);


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
    OnAccelerationChange();
}

void FlagObject::Render()
{
	SoftbodyObject::Render();
}

void FlagObject::OnDestroy()
{
}

void FlagObject::OnAccelerationChange()
{
   
    timeStep += Time::GetInstance().deltaTime / time;

    lerpValue = timeStep;

    acceleration = LerpObject(acceleration, glm::vec3(-5, -1.0f, 0.7f), lerpValue);
}

glm::vec3 FlagObject::LerpObject(const glm::vec3& a, const glm::vec3& b, float t)
{
    t = glm::clamp(t, 0.0f, 1.0f);

    return a + t * (b - a);
}