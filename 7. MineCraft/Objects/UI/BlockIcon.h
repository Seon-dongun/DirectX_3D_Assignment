#pragma once
class BlockIcon : public Button
{
public:
	BlockIcon(wstring image,int id);
	~BlockIcon();

	int GetID() { return id; }
	void PostRender();
private:
	int id;
};