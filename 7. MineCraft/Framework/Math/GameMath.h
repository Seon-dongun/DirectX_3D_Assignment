#pragma once

class GameMath : public Singleton<GameMath>
{
private:
    friend class Singleton;

    GameMath();
    ~GameMath() = default;

public:
    bool NearlyEqual(const float& s1, const float& s2)
    {
        return abs(s1 - s2) < FLT_EPSILON;
    }

    int Random(const int& min, const int& max);
    float Random(const float& min, const float& max);

private:
    random_device randomDevice;
    mt19937_64 generator;

    uniform_int_distribution<int> intDistribution;
    uniform_real_distribution<float> floatDistribution;
};