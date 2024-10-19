#pragma once
class CoinManager
{
public:
	CoinManager(Packman* packman);
	~CoinManager();

	void MakeCoins();

	void Update();
	void Render();

	int GetCoinCount() { return coinCount; }

private:
	Coin* coins[MAX_COIN];
	Packman* packman;
	int coinCount = MAX_COIN;
};