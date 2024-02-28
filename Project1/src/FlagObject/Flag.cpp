#include "Flag.h"

FlagObject::FlagObject()
{
	name = "Flag";


    std::string flagTexturePath = "Textures/FLAG2.png";
    Texture* flagTexture = new Texture(flagTexturePath);


   // SoftbodyObject* softBodyTest1 = new SoftbodyObject();
   // softBodyTest1->name = "Flag";


    LoadModel("Models/Plane/Plane10x10.ply");
    //softBodyTest1->LoadModel("Models/Plane/Flag.ply");
    acceleration = glm::vec3(-2, -1.0f, 0.7f);
    meshes[0]->meshMaterial->material()->diffuseTexture = flagTexture;
    meshes[0]->meshMaterial->material()->useMaskTexture = true;

    //softBodyTest1->LoadModel("Models/DefaultCube/DefaultCube.fbx");
   transform.SetPosition(glm::vec3(-1.30f, 5.00f, -4.60f));
    // softBodyTest1->transform.SetPosition(glm::vec3(-0.10f, 4.50f, -4.60f));  50x50
     //softBodyTest1->transform.SetPosition(glm::vec3(0, 1, 0));
     //softBodyTest1->transform.SetScale(glm::vec3(5));
    transform.SetScale(glm::vec3(10, 4, 10));
    GraphicsRender::GetInstance().AddModelAndShader(this, GraphicsRender::GetInstance().defaultShader);
    showDebug = false;
    Initialize();

    /*softBodyTest1->AddLockSphere(glm::vec3(0.100f, 5.500, -4.6f), 0.20f);
    softBodyTest1->AddLockSphere(glm::vec3(0.100f, 5.12f,-4.6f), 0.20f);
    softBodyTest1->AddLockSphere(glm::vec3(0.100f, 4.9f, -4.6f), 0.20f);
    softBodyTest1->AddLockSphere(glm::vec3(0.100f, 4.6f, -4.6f), 0.20f);*/



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
	//SoftbodyObject::upda
}

void FlagObject::Render()
{
	SoftbodyObject::Render();
}

void FlagObject::OnDestroy()
{
}
