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

    // HP ���� �ʱ� ũ�⸦ �����մϴ�.
    originalHpBarWidth = hpBar->GetLocalScale().x; // Quad�� �ʱ� �ʺ� �����մϴ�.
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

            message = "���� Ŭ����!";
            title = "���� Ŭ����";

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

    // 36�� ����� ��Ʈ������ ������ RightHand�� �־���
    rightHand->SetWorld(bodyMesh->GetTransformByNode(36));

    UpdateWorld();
    bodyMesh->Update();
    sword->Update();


    Vector3 bossScreenPos = CAM->WorldToScreen(localPosition + Vector3::Up()*5);

    float distance = (localPosition - player->GetLocalPosition()).Length(); // ���� ī�޶� ������ �Ÿ� ���
    
    if (distance < 35.0f)
        hpBar->SetActive(true);
    else
        hpBar->SetActive(false);

    float distanceScaleFactor = 1.0f / distance; // �Ÿ��� �־������� �۾������� ���� ����

    // HP ���� ���
    float hpRatio = stat.curHp / stat.maxHp;
    // HP ���� ũ�⸦ HP ������ ���� �����մϴ�.
    Vector3 hpBarScale = hpBar->GetLocalScale();
    hpBarScale.x = originalHpBarWidth * hpRatio; // ���� ũ�� ��� ������ŭ �ʺ� ����

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


    direction.GetNormalized(); // ���� ���ͷ� ����ȭ

    // ������ �ٶ� Y�� ȸ�� ������ ���
    float angle = atan2(direction.x, direction.z);
    SetLocalRotation(Vector3(0.0f, angle, 0.0f)); // Y�� ȸ���� ����

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
    if (curState == ATTACK) return; // ���� ���� ���� �ٸ� �� ���ϰ� return

    // z�� ����� ���� ������ ���� �ִ� ��
    if (velocity.z > EPSILON)
        SetState(RUN_F);
    // z�� ������ ���� �ڷ� ���� ��
    else if (velocity.z < -EPSILON)
        SetState(RUN_B);
    // x�� ����� ���� ���������� ���� ��
    else if (velocity.x > EPSILON)
        SetState(RUN_R);
    // x�� ������ ���� ���ʷ� ���� ��
    else if (velocity.x < -EPSILON)
        SetState(RUN_L);
    else // x,z �� �� 0�̸� �̵����� �ʴ� ��
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
    // ���� ���¶� �Ű������� ���� ���°� ������ ���� ���� �״�� ����
    if (curState == state)
        return;

    // ���°� �ٲ���ٸ� ���� ���¸� �ٲ��ְ�, �ش� ���¿� ���� �ִϸ��̼� Ŭ�� ���
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

    // ���� �ִϸ��̼� Ŭ������ �ִϸ��̼� ��� ���� 0.6�� �����ϸ� Groot ������Ʈ������
    // EndAttack �Լ��� ȣ���ϵ��� �Լ� �����͸� ���
    bodyMesh->GetClip(ATTACK)->SetEvent(bind(&Boss::EndAttack, this), 0.6f);

    bodyMesh->GetClip(ATTACK)->SetEvent(bind(&Boss::ActiveSwordCollider, this), 0.2f);
    bodyMesh->GetClip(ATTACK)->SetEvent(bind(&Boss::InactiveSwordCollider, this), 0.7f);
}
