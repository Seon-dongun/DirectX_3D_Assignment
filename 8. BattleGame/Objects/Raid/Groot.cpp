#include "Framework.h"

Groot::Groot()
{
    stat.maxHp = 100;
    stat.curHp = 100;
    stat.atk = 30;

	bodyMesh = new ModelAnimator("Groot");
    bodyMesh->Load();
    bodyMesh->SetParent(this);
   
    ReadClips();

    rightHand = new Transform();

    sword = new Sword();
    sword->SetParent(rightHand);
    sword->Load();

    Load();
    ClientToScreen(hWnd, &clientCenterPos);

    hpBar = new Quad(L"Textures/Colors/Red.png");
    hpBar->SetTag("HPBar");
    hpBar->Load();  

    // HP 바의 초기 크기를 저장합니다.
    originalHpBarWidth = hpBar->GetLocalScale().x; // Quad의 초기 너비를 저장합니다.
}

Groot::~Groot()
{
    delete bodyMesh;
    delete sword;
    delete rightHand;
    delete hpBar;
}

void Groot::Update()
{
    if (isDead)
    {
        Dead();
        return;
    }

    Attack();
    Control();
    Move();
    SetAction();

    // 36번 노드의 매트릭스를 추출해 RightHand에 넣어줌
    rightHand->SetWorld(bodyMesh->GetTransformByNode(36));

    UpdateWorld();
    bodyMesh->Update();
    sword->Update();

    Vector3 screenPos = CAM->WorldToScreen(localPosition);

    // HP 비율 계산
    float hpRatio = stat.curHp / stat.maxHp;
    // HP 바의 크기를 HP 비율에 따라 조절합니다.
    Vector3 hpBarScale = hpBar->GetLocalScale();
    hpBarScale.x = originalHpBarWidth * hpRatio; // 원래 크기 대비 비율만큼 너비를 조정
    hpBar->SetLocalScale(hpBarScale);


    screenPos.y += 200;
    hpBar->SetLocalPosition(screenPos);
    hpBar->UpdateWorld();

    if (stat.curHp <= 0)
        isDead = true;
}

void Groot::Render()
{
    if (!isActive) return;

    if (isDead)
    {
        isActive = false;
        bodyMesh->SetActive(false);
        sword->SetActive(false);
    }

    Collider::Render();
    bodyMesh->Render();
    sword->Render();
}

void Groot::GUIRender()
{
    bodyMesh->GUIRender();
    Transform::GUIRender();
    sword->GUIRender();
    sword->GetCollider()->GUIRender();
    hpBar->GUIRender();
}

void Groot::PostRender()
{
    hpBar->Render();
}

void Groot::Dead()
{
    if (accumTime >= 0.0f)
    {
        accumTime += DELTA;
        if (accumTime >= delayTime)
        {
            const char* message;
            const char* title;

            message = "게임 오버..";
            title = "게임 오버";

            MessageBoxA(NULL, message, title, MB_OK);

            PostQuitMessage(0);
        }
    }
}

void Groot::Attack()
{
    if (KEY->Down(VK_LBUTTON))
    {
        SetState(ATTACK);
    }

    if (sword->GetCollider()->IsActive() && sword->GetCollider()->IsBoxCollision(boss))
    {
        sword->GetCollider()->SetActive(false);
        Stat bossStat = boss->GetStat();
 
        bossStat.curHp -= stat.atk;
        boss->SetStat(bossStat);      
    }
}

void Groot::EndAttack()
{
    SetState(IDLE);
}

void Groot::Control()
{
    if (KEY->Down(VK_ESCAPE))
        isFree = !isFree;

    if (isFree) return;

    if (curState == ATTACK) return; // 공격 상태일 때는 다른 조작 안먹히게

    // 지금 컨트롤 하고 있지 않은지 체크해서 컨트롤 하고 있지 않다면 감속 효과 적용할 수 있도록 구현
    bool isMoveZ = false;
    bool isMoveX = false;

    // 이동 방향으로 velocity를 가속도만큼 가속
    // 이동 방향에 따라 X, Z 축에 대한 이동 여부 체크
    if (KEY->Press('W'))
    {
        velocity.z += accelation * DELTA; 
        isMoveZ = true;
    }
    if (KEY->Press('S'))
    {
        velocity.z -= accelation * DELTA; 
        isMoveZ = true;
    }
    if (KEY->Press('D'))
    {
        velocity.x += accelation * DELTA;
        isMoveX = true;
    }
    if (KEY->Press('A'))
    {
        velocity.x -= accelation * DELTA; 
        isMoveX = true;
    }

    // 속력값 정규화
    if (velocity.Length() > 1.0f)
        velocity.Normlize();

    // X축에 대한 이동이 없다면 
    // 현재 속력의 x값이 자연스럽게 0이 되도록 deceleration값으로 보간
    if (!isMoveX)
        velocity.x = MATH->Lerp(velocity.x,0.0f,deceleration*DELTA);

    // Z값도 마찬가지
    if (!isMoveZ)
        velocity.z = MATH->Lerp(velocity.z, 0.0f, deceleration * DELTA);


    Vector3 delta = mousePos - Vector3(CENTER_X, CENTER_Y);
    SetCursorPos(clientCenterPos.x, clientCenterPos.y);

    Rotate(Vector3::Up() * delta.x * rotSpeed * DELTA);
    CAM->Rotate(Vector3::Left() * delta.y * rotSpeed * DELTA);
}

void Groot::Move()
{
    if (curState == ATTACK) return; // 공격 상태면 이동안되게 처리

    Matrix rotY = XMMatrixRotationY(localRotation.y);

    // 캐릭터가 회전됨에 따라, velocity에 대한 방향도 같이 회전시켜줌으로서, 
    // 캐릭터가 회전되어도 동일한 방향으로 vecocity를 적용할 수 있음
    Vector3 direction = XMVector3TransformNormal(velocity, rotY); 

    Translate(direction * moveSpeed * DELTA); // 회전이 반영된 올바른 방향의 속력을 반영해 이동
}

void Groot::SetAction() // velocity 값에 따라 현재 상태 설정
{
    if (curState == ATTACK) return; // 공격 중일 때는 다른 것 못하게 return

    // z가 양수인 경우는 앞으로 가고 있는 것
    if (velocity.z > EPSILON)
        SetState(RUN_F);
    // z가 음수인 경우는 뒤로 가는 것
    else if (velocity.z < -EPSILON)
        SetState(RUN_B);
    // x가 양수인 경우는 오른쪽으로 가는 것
    else if (velocity.x > EPSILON)
        SetState(RUN_R);
    // x가 음수인 경우는 왼쪽로 가는 것
    else if (velocity.x < -EPSILON)
        SetState(RUN_L);
    else // x,z 둘 다 0이면 이동하지 않는 것
        SetState(IDLE);
}

void Groot::ActiveSwordCollider()
{
    sword->GetCollider()->SetActive(true);
}

void Groot::InactiveSwordCollider()
{
    sword->GetCollider()->SetActive(false);
}

void Groot::SetState(ActionState state)
{
    // 현재 상태랑 매개변수로 받은 상태가 같으면 현재 상태 그대로 유지
    if (curState == state)
        return;

    // 상태가 바뀌었다면 현재 상태를 바꿔주고, 해당 상태에 대한 애니메이션 클립 재생
    curState = state;
    bodyMesh->PlayClip(state);
}

void Groot::ReadClips()
{
    bodyMesh->ReadClip("Idle");
    bodyMesh->ReadClip("RunF");
    bodyMesh->ReadClip("RunB");
    bodyMesh->ReadClip("RunR");
    bodyMesh->ReadClip("RunL");
    bodyMesh->ReadClip("Attack");
    bodyMesh->CreateTexture();

    // 공격 애니메이션 클립에서 애니메이션 재생 비율 0.6에 도달하면 Groot 오브젝트에서의
    // EndAttack 함수를 호출하도록 함수 포인터를 등록
    bodyMesh->GetClip(ATTACK)->SetEvent(bind(&Groot::EndAttack,this),0.6f);

    bodyMesh->GetClip(ATTACK)->SetEvent(bind(&Groot::ActiveSwordCollider, this), 0.2f);
    bodyMesh->GetClip(ATTACK)->SetEvent(bind(&Groot::InactiveSwordCollider, this), 0.7f);
}
