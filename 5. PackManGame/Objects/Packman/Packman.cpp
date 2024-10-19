#include "Framework.h"
#include "Packman.h"
#define ADD_CAM_TRANSFORM Vector3::Up()*6+GetBack()*20

Packman::Packman(float radius) : SphereCollider(radius)
{
	prevMousePos = mousePos;

	sphere = new Sphere(radius);
	sphere->GetMaterial()->SetShader(L"Light/Light.hlsl");
	sphere->GetMaterial()->SetDiffuseMap(L"Textures/Colors/Yellow.png");
	sphere->SetParent(this);

	ClientToScreen(hWnd, &clientCenterPos);
	ShowCursor(true);

	light = Environment::Get()->GetLight(0);
	light->type = 2;
	light->range = 130.0f;
	light->inner = 75.0f;
	light->outer = 18.5f;
	light->attentionIntensity = 0.1f;
}

Packman::~Packman()
{
	delete sphere;
}

void Packman::Update()
{
	Move();
	SetLight();

	UpdateWorld();
	sphere->UpdateWorld();
}

void Packman::SetLight()
{
	if (KEY->Down('V'))
		light->isActive = !(light->isActive);
	light->direction = GetForward();
	light->position = localPosition;
}

void Packman::Move()
{
	/*
	* 이동 시 자꾸 구가 벽을 통과하는 경우가 있었는데, 문제는 평면 상으로 이동시킨다고 y=0으로 설정한 것이 문제였다
	* y=0으로 설정해야 하는 것은 맞지만 이후에 y를 0으로 만든 다음 해당 벡터를 다시 정규화하는 것이 필요하다.
	* 왜냐하면 처음에 3차원의 정규화 된 벡터를 받더라도 y=0으로 만들면 해당 벡터는 xz 평면 상의 새로운 벡터가 되고, 
	* 이때 크기가 변하게 된다.
	* 따라서 정확한 방향 벡터를 얻기 위해서는 y=0으로 만든 과정 이후에 정규화를 다시 한 번 해주어야 했던 것.
	* 
	* 지금 보면 대각선으로 WA WD 키를 동시에 눌러서 가는 케이스에서는 다시 뚫리는 것을 보니, 대각선의 경우도
	* 아마 방향 벡터를 다시 구해야 할듯? 이 때는 대각선의 방향 벡터를 계산해서 정규화하고 반지름을 곱해주면 해결될듯
	*/
	if (KEY->Press('W'))
	{
		Vector3 forward = GetForward();
		forward.y = 0;
		Vector3 tmp = localPosition + forward.GetNormalized() * Radius();
		if (maze->GetHeight(tmp) < 5.0f)
		{
			Translate(forward * moveSpeed * DELTA);
		}
	}
	if (KEY->Press('S'))
	{
		Vector3 back = GetBack();
		back.y = 0;
		Vector3 tmp = localPosition +back.GetNormalized()*Radius();
		if (maze->GetHeight(tmp) < 5.0f)
		{
			Translate(back * moveSpeed * DELTA);
		}
	}
	if (KEY->Press('A'))
	{
		Vector3 left = GetLeft();
		left.y = 0;
		Vector3 tmp = localPosition  +left.GetNormalized()*Radius();
		if (maze->GetHeight(tmp) < 5.0f)
		{
			Translate(left * moveSpeed * DELTA);
		}			
	}
	if (KEY->Press('D'))
	{
		Vector3 right = GetRight();
		right.y = 0;
		Vector3 tmp = localPosition + right.GetNormalized()*Radius();
		if (maze->GetHeight(tmp) <5.0f)
		{
			Translate(right * moveSpeed * DELTA);
		}
	}

	if (KEY->Press(VK_SHIFT))
		moveSpeed = 60.0f;
	else
		moveSpeed = 30.0f;
	
	if (KEY->Down(VK_ESCAPE))
		isFree = !isFree;

	if (isFree) return;

	Vector3 delta = mousePos - Vector3(CENTER_X, CENTER_Y);

	SetCursorPos(clientCenterPos.x, clientCenterPos.y);

	Rotate(Vector3::Up() * delta.x * rotSpeed * DELTA);
	Rotate(Vector3::Left() * delta.y * rotSpeed * DELTA);

	localPosition.y = maze->GetHeight(localPosition) + Radius();

	CAM->SetLocalPosition(localPosition+ADD_CAM_TRANSFORM);
	CAM->SetLocalRotation(localRotation);
}

void Packman::Render()
{
	//Collider::Render();
	sphere->Render();
}
