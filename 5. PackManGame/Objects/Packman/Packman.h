#pragma once
class Packman : public SphereCollider
{
public:
	Packman(float radius);
	~Packman();

	void Update();
	void SetLight();
	void Move();
	void SetMaze(class Maze* maze) { this->maze = maze; }

	void Render();
private:
	float moveSpeed = 30.0f;
	float rotSpeed = 0.5f;

	Vector3 prevMousePos;

	POINT clientCenterPos = { WIN_WIDTH >> 1,WIN_HEIGHT >> 1 };

	class Maze* maze;
	Sphere* sphere;

	LightBuffer::Light* light;

	bool isFree = false;
};