#pragma once

class Vector3
{
public:
    Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f)
        : value(XMVectorSet(x, y, z, 0))
    {}
    Vector3(Float3 value) : value(XMLoadFloat3(&value))
    {}
    Vector3(Vector4 value) : value(value)
    {}

    operator Vector4() { return value; }
    operator Float3()
    {
        Float3 result;
        XMStoreFloat3(&result, value);

        return result;
    }

    void SetX(const float& x)
    {
        value = XMVectorSetX(value, x);
    }
    void SetY(const float& y)
    {
        value = XMVectorSetY(value, y);
    }
    void SetZ(const float& z)
    {
        value = XMVectorSetZ(value, z);
    }

    float GetX() const { return XMVectorGetX(value); }
    float GetY() const { return XMVectorGetY(value); }
    float GetZ() const { return XMVectorGetZ(value); }

    __declspec(property(get = GetX, put = SetX)) float x;
    __declspec(property(get = GetY, put = SetY)) float y;
    __declspec(property(get = GetZ, put = SetZ)) float z;

    Vector3 operator+(const Vector3& v) { return value + v.value; }
    Vector3 operator-(const Vector3& v) { return value - v.value; }

    void operator +=(const Vector3& v) { value += v.value; }
    void operator -=(const Vector3& v) { value -= v.value; }

    Vector3 operator*(const float& s) const { return value * s; }
    Vector3 operator/(const float& s) const { return value / s; }

    friend void operator+=(Float3& v1, const Vector3& v2)
    {
        Vector4 temp = XMLoadFloat3(&v1) + v2.value;

        XMStoreFloat3(&v1, temp);
    }

    friend void operator-=(Float3& v1, const Vector3& v2)
    {
        Vector4 temp = XMLoadFloat3(&v1) - v2.value;

        XMStoreFloat3(&v1, temp);
    }

    Vector3 GetNormalized() const { return XMVector3Normalize(value); }
    void Normlize() { value = XMVector3Normalize(value); }

    float Length() const { return XMVectorGetX(XMVector3Length(value)); }

    Vector4* GetValue() { return &value; }

    static Vector3 Cross(Vector3& vec1, Vector3& vec2)
    {
        return XMVector3Cross(vec1, vec2);
    }
    static float Dot(Vector3& vec1, Vector3& vec2)
    {
        return XMVectorGetX(XMVector3Dot(vec1, vec2));
    }
public:
    static Vector3 Zero() { return Vector3(); }
    static Vector3 One() { return Vector3(1, 1, 1); }
    static Vector3 Right() { return Vector3(1, 0, 0); }
    static Vector3 Left() { return Vector3(-1, 0, 0); }
    static Vector3 Up() { return Vector3(0, 1, 0); }
    static Vector3 Down() { return Vector3(0, -1, 0); }
    static Vector3 Forward() { return Vector3(0, 0, 1); }
    static Vector3 Back() { return Vector3(0, 0, -1); }

private:
    Vector4 value;
};