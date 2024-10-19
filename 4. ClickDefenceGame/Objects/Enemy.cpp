#include "Framework.h"
#include "Enemy.h"

Enemy::Enemy()
{
	sphere = new Sphere(1.0f);
	sphere->GetMaterial()->SetShader(L"Light/NormalMapping.hlsl");
}

Enemy::~Enemy()
{
	delete sphere;
}

void Enemy::MoveToTarget()
{
	Vector3 dir = (CAM->GetLocalPosition() - GetLocalPosition()).GetNormalized();
	localPosition += (dir * moveSpeed * DELTA);

	sphere->SetLocalPosition(localPosition);
	sphere->SetLocalRotation(localRotation);
	sphere->SetLocalScale(localScale);

	sphere->UpdateWorld();
	UpdateWorld();
}