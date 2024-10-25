#include "Framework.h"

Boss::Boss()
{
    stat.maxHp = 100;
    stat.curHp = 100;
    stat.atk = 10;

    bodyMesh = new ModelAnimator("Groot");
    bodyMesh->Load();
    bodyMesh->SetParent(this);
    ReadClips();
    Load();

    localPosition = { 5.0f,localPosition.y,65.0f };

    rightHand = new Transform();

    sword = new Sword();
    sword->SetParent(rightHand);
    sword->Load();

    hpBar = new Quad(L"Textures/Colors/Red.png");
    hpBar->SetTag("HPBar");
    hpBar->Load();

    // HP 바의 초기 크기를 저장합니다.
    originalHpBarWidth = hpBar->GetLocalScale().x; // Quad의 초기 너비를 저장합니다.
}

Boss::~Boss()
{
    delete bodyMesh;
    delete sword;
    delete rightHand;
}

void Boss::Dead()
{
    if (accumTime >= 0.0f)
    {
        accumTime += DELTA;
        if (accumTime >= delayTime)
        {
            const char* message;
            const char* title;

            message = "게임 클리어!";
            title = "게임 클리어";

            MessageBoxA(NULL, message, title, MB_OK);

            PostQuitMessage(0);
        }
    }
}

void Boss::Update()
{
    if (isDead)
    {
        Dead();
        return;
    }

    if (!isActive)   
        return;

    Control();

    // 36번 노드의 매트릭스를 추출해 RightHand에 넣어줌
    rightHand->SetWorld(bodyMesh->GetTransformByNode(36));

    UpdateWorld();
    bodyMesh->Update();
    sword->Update();


    Vector3 bossScreenPos = CAM->WorldToScreen(localPosition + Vector3::Up()*5);

    float distance = (localPosition - player->GetLocalPosition()).Length(); // 적과 카메라 사이의 거리 계산
    
    if (distance < 35.0f)
        hpBar->SetActive(true);
    else
        hpBar->SetActive(false);

    float distanceScaleFactor = 1.0f / distance; // 거리가 멀어질수록 작아지도록 역수 적용

    // HP 비율 계산
    float hpRatio = stat.curHp / stat.maxHp;
    // HP 바의 크기를 HP 비율에 따라 조절합니다.
    Vector3 hpBarScale = hpBar->GetLocalScale();
    hpBarScale.x = originalHpBarWidth * hpRatio; // 원래 크기 대비 비율만큼 너비를 조정

    hpBar->SetLocalScale(hpBarScale);

    hpBar->SetLocalPosition(bossScreenPos);
    hpBar->UpdateWorld();

    if (stat.curHp <= 0)
        isDead = true;
}

void Boss::Render()
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

void Boss::GUIRender()
{
    if (!isActive) return;

    bodyMesh->GUIRender();
    Transform::GUIRender();
    sword->GUIRender();
    sword->GetCollider()->GUIRender();
    hpBar->GUIRender();
}

void Boss::PostRender()
{
    hpBar->Render();
}

void Boss::Attack()
{
    SetState(ATTACK);

    if (sword->GetCollider()->IsActive() && sword->GetCollider()->IsBoxCollision(player))
    {
        sword->GetCollider()->SetActive(false);
        Stat playerStat = player->GetStat();

        playerStat.curHp -= stat.atk;
        player->SetStat(playerStat);
        
    }
}
void Boss::Move()
{
    if (curState == ATTACK) 
        return; 

    SetState(RUN_F);

    Vector3 direction = (player->GetLocalPosition() - localPosition).GetNormalized();

    direction.y = 0.0f; 


    direction.GetNormalized(); // 단위 벡터로 정규화

    // 보스가 바라볼 Y축 회전 각도를 계산
    float angle = atan2(direction.x, direction.z);
    SetLocalRotation(Vector3(0.0f, angle, 0.0f)); // Y축 회전을 설정

    Translate(direction * moveSpeed * DELTA); 
}

void Boss::EndAttack()
{
    SetState(IDLE);
}

void Boss::Control()
{
    float distance = (player->GetLocalPosition() - localPosition).Length();

    if (distance < 4.0f)
        Attack();
    else
        Move();
}

void Boss::SetAction()
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

void Boss::ActiveSwordCollider()
{
    sword->GetCollider()->SetActive(true);
}

void Boss::InactiveSwordCollider()
{
    sword->GetCollider()->SetActive(false);
}

void Boss::SetState(ActionState state)
{
    // 현재 상태랑 매개변수로 받은 상태가 같으면 현재 상태 그대로 유지
    if (curState == state)
        return;

    // 상태가 바뀌었다면 현재 상태를 바꿔주고, 해당 상태에 대한 애니메이션 클립 재생
    curState = state;
    bodyMesh->PlayClip(state);
}

void Boss::ReadClips()
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
    bodyMesh->GetClip(ATTACK)->SetEvent(bind(&Boss::EndAttack, this), 0.6f);

    bodyMesh->GetClip(ATTACK)->SetEvent(bind(&Boss::ActiveSwordCollider, this), 0.2f);
    bodyMesh->GetClip(ATTACK)->SetEvent(bind(&Boss::InactiveSwordCollider, this), 0.7f);
}
