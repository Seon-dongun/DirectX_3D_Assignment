#include "Framework.h"

GameMath::GameMath()
    : generator(randomDevice()), floatDistribution(0.0f, 1.0f),
    intDistribution(0)
{
}

int GameMath::Random(const int& min, const int& max)
{
    return intDistribution(generator) % (max - min) + min;
}

float GameMath::Random(const float& min, const float& max)
{
    return (max - min) * floatDistribution(generator) + min;
}
