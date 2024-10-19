#pragma once
class Enemy : public SphereCollider
{
public:
	Enemy();
	~Enemy();

	void MoveToTarget();

	bool GetIsActive() { return isActive; }
	void SetIsActive(bool isActive) { this->isActive = isActive;
	}
	Sphere* GetSphere() { return sphere; }

private:
	float moveSpeed = 10.0f;
	bool isActive = true;

	Sphere* sphere;
};