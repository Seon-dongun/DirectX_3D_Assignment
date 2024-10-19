#pragma once
class PackManScene : public Scene
{
public:
	PackManScene();
	~PackManScene();


	void Update() override;
	void PreRender() override;
	void Render() override;
	void PostRender() override;
	void GUIRender() override;

	bool IsGameClear();

private:
	Maze* maze;
	Packman* packman;
	CoinManager* coinManager;
};