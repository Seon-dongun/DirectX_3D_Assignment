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

    // HP ���� �ʱ� ũ�⸦ �����մϴ�.
    originalHpBarWidth = hpBar->GetLocalScale().x; // Quad�� �ʱ� �ʺ� �����մϴ�.
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

    // 36�� ����� ��Ʈ������ ������ RightHand�� �־���
    rightHand->SetWorld(bodyMesh->GetTransformByNode(36));

    UpdateWorld();
    bodyMesh->Update();
    sword->Update();

    Vector3 screenPos = CAM->WorldToScreen(localPosition);

    // HP ���� ���
    float hpRatio = stat.curHp / stat.maxHp;
    // HP ���� ũ�⸦ HP ������ ���� �����մϴ�.
    Vector3 hpBarScale = hpBar->GetLocalScale();
    hpBarScale.x = originalHpBarWidth * hpRatio; // ���� ũ�� ��� ������ŭ �ʺ� ����
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

            message = "���� ����..";
            title = "���� ����";

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

    if (curState == ATTACK) return; // ���� ������ ���� �ٸ� ���� �ȸ�����

    // ���� ��Ʈ�� �ϰ� ���� ������ üũ�ؼ� ��Ʈ�� �ϰ� ���� �ʴٸ� ���� ȿ�� ������ �� �ֵ��� ����
    bool isMoveZ = false;
    bool isMoveX = false;

    // �̵� �������� velocity�� ���ӵ���ŭ ����
    // �̵� ���⿡ ���� X, Z �࿡ ���� �̵� ���� üũ
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

    // �ӷ°� ����ȭ
    if (velocity.Length() > 1.0f)
        velocity.Normlize();

    // X�࿡ ���� �̵��� ���ٸ� 
    // ���� �ӷ��� x���� �ڿ������� 0�� �ǵ��� deceleration������ ����
    if (!isMoveX)
        velocity.x = MATH->Lerp(velocity.x,0.0f,deceleration*DELTA);

    // Z���� ��������
    if (!isMoveZ)
        velocity.z = MATH->Lerp(velocity.z, 0.0f, deceleration * DELTA);


    Vector3 delta = mousePos - Vector3(CENTER_X, CENTER_Y);
    SetCursorPos(clientCenterPos.x, clientCenterPos.y);

    Rotate(Vector3::Up() * delta.x * rotSpeed * DELTA);
    CAM->Rotate(Vector3::Left() * delta.y * rotSpeed * DELTA);
}

void Groot::Move()
{
    if (curState == ATTACK) return; // ���� ���¸� �̵��ȵǰ� ó��

    Matrix rotY = XMMatrixRotationY(localRotation.y);

    // ĳ���Ͱ� ȸ���ʿ� ����, velocity�� ���� ���⵵ ���� ȸ�����������μ�, 
    // ĳ���Ͱ� ȸ���Ǿ ������ �������� vecocity�� ������ �� ����
    Vector3 direction = XMVector3TransformNormal(velocity, rotY); 

    Translate(direction * moveSpeed * DELTA); // ȸ���� �ݿ��� �ùٸ� ������ �ӷ��� �ݿ��� �̵�
}

void Groot::SetAction() // velocity ���� ���� ���� ���� ����
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
    // ���� ���¶� �Ű������� ���� ���°� ������ ���� ���� �״�� ����
    if (curState == state)
        return;

    // ���°� �ٲ���ٸ� ���� ���¸� �ٲ��ְ�, �ش� ���¿� ���� �ִϸ��̼� Ŭ�� ���
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

    // ���� �ִϸ��̼� Ŭ������ �ִϸ��̼� ��� ���� 0.6�� �����ϸ� Groot ������Ʈ������
    // EndAttack �Լ��� ȣ���ϵ��� �Լ� �����͸� ���
    bodyMesh->GetClip(ATTACK)->SetEvent(bind(&Groot::EndAttack,this),0.6f);

    bodyMesh->GetClip(ATTACK)->SetEvent(bind(&Groot::ActiveSwordCollider, this), 0.2f);
    bodyMesh->GetClip(ATTACK)->SetEvent(bind(&Groot::InactiveSwordCollider, this), 0.7f);
}
