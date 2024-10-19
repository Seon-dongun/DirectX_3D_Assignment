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
	* �̵� �� �ڲ� ���� ���� ����ϴ� ��찡 �־��µ�, ������ ��� ������ �̵���Ų�ٰ� y=0���� ������ ���� ��������
	* y=0���� �����ؾ� �ϴ� ���� ������ ���Ŀ� y�� 0���� ���� ���� �ش� ���͸� �ٽ� ����ȭ�ϴ� ���� �ʿ��ϴ�.
	* �ֳ��ϸ� ó���� 3������ ����ȭ �� ���͸� �޴��� y=0���� ����� �ش� ���ʹ� xz ��� ���� ���ο� ���Ͱ� �ǰ�, 
	* �̶� ũ�Ⱑ ���ϰ� �ȴ�.
	* ���� ��Ȯ�� ���� ���͸� ��� ���ؼ��� y=0���� ���� ���� ���Ŀ� ����ȭ�� �ٽ� �� �� ���־�� �ߴ� ��.
	* 
	* ���� ���� �밢������ WA WD Ű�� ���ÿ� ������ ���� ���̽������� �ٽ� �ո��� ���� ����, �밢���� ��쵵
	* �Ƹ� ���� ���͸� �ٽ� ���ؾ� �ҵ�? �� ���� �밢���� ���� ���͸� ����ؼ� ����ȭ�ϰ� �������� �����ָ� �ذ�ɵ�
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
