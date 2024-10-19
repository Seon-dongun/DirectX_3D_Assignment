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
	// Vector4 매개변수를 요구할 때는 Vector4 타입의 value로 리턴해줌

	void SetX(const float& x)
	{
		value = XMVectorSetX(value,x);
	}
	void SetY(const float& y)
	{
		value = XMVectorSetX(value, y);
	}
	void SetZ(const float& z)
	{
		value = XMVectorSetX(value, z);
	}

	float GetX() const { return XMVectorGetX(value); }	
	float GetY() const { return XMVectorGetY(value); }
	float GetZ() const { return XMVectorGetZ(value); }

	// 람다식을 활용한 문법이라고 하는데, 이렇게 하면 ~~.x 방식으로
	// 바로 Get, Set 함수를 사용할 수 있음
	__declspec(property(get = GetX, put = SetX)) float x;
	__declspec(property(get = GetY, put = SetY)) float y;
	__declspec(property(get = GetZ, put = SetZ)) float z;

	void operator +=(const Vector3& v) { value += v.value; }
	void operator -=(const Vector3& v) { value -= v.value; }


private:
	Vector4 value;
};