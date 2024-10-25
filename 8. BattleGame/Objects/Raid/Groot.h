#pragma once
struct Stat
{
	float maxHp, curHp;
	int atk;
};

class Groot : public BoxCollider
{
private:
	enum ActionState
	{
		IDLE,
		RUN_F,RUN_B,RUN_R,RUN_L,
		ATTACK
	};

	const float EPSILON = 0.1f;

public:
	Groot();
	~Groot();

	void Update();
	void Render();
	void GUIRender();
	void PostRender();
	void SetEnemy(class Boss* boss) { this->boss = boss; }
	void Dead();
	Stat GetStat() { return stat; }
	void SetStat(Stat stat) { this->stat = stat; }
private:
	void Attack();
	void EndAttack();

	void Control();
	void Move();
	void SetAction();

	void ActiveSwordCollider();
	void InactiveSwordCollider();

	void SetState(ActionState state);

	void ReadClips();
private:
	ModelAnimator* bodyMesh;
	Sword* sword;
	class Boss* boss;

	Transform* rightHand;

	ActionState curState;

	float moveSpeed = 10.0f;
	float rotSpeed = 2.0f;
	float accelation = 2.0f;
	float deceleration = 10.0f;

	POINT clientCenterPos = { WIN_WIDTH >> 1, WIN_HEIGHT >> 1 };
	bool isFree = true;

	Vector3 velocity;

	Vector3 prevMousePos;

	Quad* hpBar;
	float originalHpBarWidth;
	Stat stat;

	float accumTime = 0.0f;
	const float delayTime = 0.4f;
	bool isDead = false;
};