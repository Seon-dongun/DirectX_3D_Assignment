#pragma once
class Boss : public BoxCollider
{
private:
	enum ActionState
	{
		IDLE,
		RUN_F, RUN_B, RUN_R, RUN_L,
		ATTACK
	};

	const float EPSILON = 0.1f;

public:
	Boss();
	~Boss();

	void Dead();
	void Update();
	void Render();
	void GUIRender();
	void PostRender();

	void SetPlayer(Groot* player) { this->player = player; }
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
	Groot* player;

	Transform* rightHand;

	ActionState curState;

	float moveSpeed = 5.0f;
	float rotSpeed = 2.0f;
	float accelation = 2.0f;
	float deceleration = 10.0f;

	Vector3 velocity;

	Quad* hpBar;
	float originalHpBarWidth;
	Stat stat;

	float accumTime = 0.0f;
	const float delayTime = 0.4f;
	bool isDead = false;
};