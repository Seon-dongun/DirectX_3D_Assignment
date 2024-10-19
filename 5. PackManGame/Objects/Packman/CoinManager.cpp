#include "Framework.h"
#include "CoinManager.h"

CoinManager::CoinManager(Packman* packman) : packman(packman)
{
	MakeCoins();
}

CoinManager::~CoinManager()
{
	for (Coin* coin : coins)
		delete coin;
}

void CoinManager::MakeCoins()
{
	for (int i = 0; i < MAX_COIN; i++)
	{
		coins[i] = new Coin(1.0f);
		float y = coins[i]->GetRadius();
		coins[i]->SetLocalPosition({ 110.0f,y,160.0f + (i + 1) * 10.0f});
	}
}

void CoinManager::Update()
{
	for (Coin* coin : coins)
	{
		if (coin->GetIsActive())
		{
			if (coin->IsSphereCollision(packman))
			{
				coin->SetIsActive(false);
				coinCount--;
			}

			coin->Update();			
		}
	}
}

void CoinManager::Render()
{
	for (Coin* coin : coins)
	{
		if (coin->GetIsActive())
			coin->Render();
	}
}

