#pragma once
class RoomEscapePlayer : public SphereCollider
{
public:
	RoomEscapePlayer(float radius);
	~RoomEscapePlayer();

	void Update();
	void Move();

	void Render();

	void PostRender();

	Quad* GetItemUI() { return itemUI; }
private:
	float moveSpeed = 1;
	float rotSpeed = 0.5f;

	Vector3 prevMousePos;

	POINT clientCenterPos = { WIN_WIDTH >> 1,WIN_HEIGHT >> 1 };

	Sphere* sphere;

	LightBuffer::Light* light;

	bool isFree = false;

	Quad* itemUI;
};