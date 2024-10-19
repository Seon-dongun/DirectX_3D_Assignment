#pragma once
class Coin : public SphereCollider
{
public:
	Coin(float radius);
	~Coin();

	void Render();

	void Update();
	
	void MoveRound();

	bool GetIsActive() { return isActive; }
	void SetIsActive(bool isActive) { this->isActive = isActive; }

private:
	Sphere* sphere;
	bool isActive = true;
	float rotSpeed = 1.0f;
};