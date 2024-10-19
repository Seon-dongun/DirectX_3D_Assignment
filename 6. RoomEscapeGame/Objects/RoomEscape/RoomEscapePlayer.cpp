#include "Framework.h"
#include "RoomEscapePlayer.h"
#define ADD_CAM_TRANSFORM Vector3::Up()+GetBack()*5

RoomEscapePlayer::RoomEscapePlayer(float radius) : SphereCollider(radius)
{
	prevMousePos = mousePos;

	sphere = new Sphere(radius);
	sphere->GetMaterial()->SetShader(L"Light/Light.hlsl");
	sphere->GetMaterial()->SetDiffuseMap(L"Textures/Colors/Yellow.png");
	sphere->SetParent(this);

	itemUI = new Quad(L"Textures/UI/ItemUI.png");
	itemUI->SetLocalPosition({218,WIN_HEIGHT-40,0 });
	itemUI->UpdateWorld();

	ClientToScreen(hWnd, &clientCenterPos);
	ShowCursor(true);
}

RoomEscapePlayer::~RoomEscapePlayer()
{
	delete sphere;
	delete itemUI;
}

void RoomEscapePlayer::Update()
{
	Move();

	UpdateWorld();
	sphere->UpdateWorld();
}

void RoomEscapePlayer::Move()
{
	if (KEY->Press('W'))
	{
		Vector3 forward = GetForward();
		forward.y = 0;
		Translate(forward.GetNormalized() * moveSpeed * DELTA);
	}
	if (KEY->Press('S'))
	{
		Vector3 back = GetBack();
		back.y = 0;

		Translate(back.GetNormalized() * moveSpeed * DELTA);
	}
	if (KEY->Press('A'))
	{
		Vector3 left = GetLeft();
		left.y = 0;

		Translate(left.GetNormalized() * moveSpeed * DELTA);

	}
	if (KEY->Press('D'))
	{
		Vector3 right = GetRight();
		right.y = 0;

		Translate(right.GetNormalized() * moveSpeed * DELTA);

	}

	if (KEY->Press(VK_SHIFT))
		moveSpeed = 2;
	else
		moveSpeed = 1;

	if (KEY->Down(VK_ESCAPE))
		isFree = !isFree;

	if (isFree) return;

	Vector3 delta = mousePos - Vector3(CENTER_X, CENTER_Y);

	SetCursorPos(clientCenterPos.x, clientCenterPos.y);

	Rotate(Vector3::Up() * delta.x * rotSpeed * DELTA);
	Rotate(Vector3::Left() * delta.y * rotSpeed * DELTA);

	localPosition.y = Radius();

	CAM->SetLocalPosition(localPosition + ADD_CAM_TRANSFORM);
	CAM->SetLocalRotation(localRotation);
}

void RoomEscapePlayer::Render()
{
	sphere->Render();
}

void RoomEscapePlayer::PostRender()
{
	itemUI->Render();
}
