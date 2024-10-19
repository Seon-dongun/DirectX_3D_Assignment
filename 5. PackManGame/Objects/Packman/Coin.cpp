#include "Framework.h"
#include "Coin.h"

Coin::Coin(float radius) : SphereCollider(radius)
{
	sphere = new Sphere();
	sphere->GetMaterial()->SetShader(L"Light/Light.hlsl");
	sphere->GetMaterial()->SetDiffuseMap(L"Textures/Colors/Yellow.png");
	sphere->SetParent(this);

	sphere->SetLocalScale({ 0.2f,1.0f,1.0f });
}

Coin::~Coin()
{
	delete sphere;
}

void Coin::Render()
{
	//Collider::Render();
	sphere->Render();
}


void Coin::Update()
{
	MoveRound();
}

void Coin::MoveRound()
{
	sphere->Rotate(Vector3::Up() * rotSpeed * DELTA);

	UpdateWorld();
	sphere->UpdateWorld();
}
