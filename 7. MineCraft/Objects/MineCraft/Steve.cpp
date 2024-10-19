#include "Framework.h"

Steve::Steve()
{
    localPosition = { 0, 0, 0 };

    prevMousePos = mousePos;
    ClientToScreen(hWnd, &clientCenterPos);

    ui = new MineCraftUI();
}

Steve::~Steve()
{
    delete ui;
}

void Steve::Update()
{
    ui->Update();

    Move();
    Jump();
    Control();

    UpdateWorld();
}

void Steve::PostRender()
{
    ui->PostRender();
}

void Steve::GUIRender()
{
    ui->GUIRender();
}

void Steve::Move()
{
    if (KEY->Press('W'))
    {
        Vector3 forward = GetForward();
        forward.y = 0;
        Translate(forward.GetNormalized() * moveSpeed * DELTA);
    }else if (KEY->Press('S'))
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
    else if (KEY->Press('D'))
    {
        Vector3 right = GetRight();
        right.y = 0;
        Translate(right.GetNormalized() * moveSpeed * DELTA);
    }

    if (KEY->Down(VK_ESCAPE))
        isFree = !isFree;

    if (isFree) return;

    Vector3 delta = mousePos - Vector3(CENTER_X, CENTER_Y);
    SetCursorPos(clientCenterPos.x, clientCenterPos.y);

    Rotate(Vector3::Up() * delta.x * rotSpeed * DELTA);
    Rotate(Vector3::Left() * delta.y * rotSpeed * DELTA);

    //localPosition.y = BlockManager::Get()->GetHeight(localPosition) + Radius();

    CAM->SetLocalPosition(localPosition);
    CAM->SetLocalRotation(localRotation);
}

void Steve::Jump()
{
    if (KEY->Down(VK_SPACE))
        velocity = JUMP_POWER;

    velocity -= GRAVITY * DELTA;

    Translate(Vector3::Up() * velocity * DELTA);

    float height = BlockManager::Get()->GetHeight(localPosition);

    if (height > localPosition.y - Radius())
    {
        velocity = 0.0f;
        localPosition.y = height + Radius();
    }
}

void Steve::Control()
{
    if (KEY->Down(VK_LBUTTON))
        ui->Mining();

    if (KEY->Down(VK_RBUTTON))
        ui->Build();
}
