#pragma once
#define ENEMY_COUNT 5

class DefenceGameScene : public Scene
{
public:
	DefenceGameScene();
	~DefenceGameScene();

	void Update() override;
	void PreRender() override;
	void Render() override;
	void PostRender() override;
	void GUIRender() override;

private:
	bool IsGameOver();
	bool IsGameClear();

private:
	vector<Enemy*> enemys;
};