#pragma once
class RoomEscapeScene : public Scene
{
public:
	RoomEscapeScene();
	~RoomEscapeScene();

	void ItemStateUpdate();

	void Update() override;

	void PreRender() override;

	void Render() override;

	void PostRender() override;

	void GUIRender() override;

private:
	Quad* room;
	Model* door;
	Model* chest;
	Model* table;

	RoomEscapePlayer* player;
	LightBuffer::Light* light;

	bool isGetChestKey = false, isGetEscapeKey = false;
};