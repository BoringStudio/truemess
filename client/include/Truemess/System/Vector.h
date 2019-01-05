#pragma once

/////////////////////////////////////////////////////////////////////////////////////////
// Vector2
/////////////////////////////////////////////////////////////////////////////////////////
namespace tms {
template <typename T>
class Vector2
{
public:
	Vector2();
	Vector2(T x, T y);

    template<typename From>
	explicit Vector2(const Vector2<From>& vector);

	T x;
	T y;
};

template <typename T>
Vector2<T> operator+(const Vector2<T>& left, const T& right);
template <typename T>
Vector2<T> operator-(const Vector2<T>& left, const T& right);
template <typename T>
Vector2<T> operator*(const Vector2<T>& left, const T& right);
template <typename T>
Vector2<T> operator/(const Vector2<T>& left, const T& right);

template <typename T>
Vector2<T> operator+(const Vector2<T>& left);
template <typename T>
Vector2<T> operator-(const Vector2<T>& left);

template <typename T>
Vector2<T>& operator+=(Vector2<T>& left, const T& right);
template <typename T>
Vector2<T>& operator-=(Vector2<T>& left, const T& right);
template <typename T>
Vector2<T>& operator*=(Vector2<T>& left, const T& right);
template <typename T>
Vector2<T>& operator/=(Vector2<T>& left, const T& right);

template <typename T>
bool operator==(const Vector2<T>& left, const Vector2<T>& right);

/////////////////////////////////////////////////////////////////////////////////////////
// Vector3
/////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
class Vector3
{
public:
	Vector3();
	Vector3(T x, T y, T z);

	template<typename From>
	explicit Vector3(const Vector3<From>& vector);

	T x;
	T y;
	T z;
};

template <typename T>
Vector3<T> operator+(const Vector3<T>& left, const T& right);
template <typename T>
Vector3<T> operator-(const Vector3<T>& left, const T& right);
template <typename T>
Vector3<T> operator*(const Vector3<T>& left, const T& right);
template <typename T>
Vector3<T> operator/(const Vector3<T>& left, const T& right);

template <typename T>
Vector3<T> operator+(const Vector3<T>& left);
template <typename T>
Vector3<T> operator-(const Vector3<T>& left);

template <typename T>
Vector3<T>& operator+=(Vector3<T>& left, const T& right);
template <typename T>
Vector3<T>& operator-=(Vector3<T>& left, const T& right);
template <typename T>
Vector3<T>& operator*=(Vector3<T>& left, const T& right);
template <typename T>
Vector3<T>& operator/=(Vector3<T>& left, const T& right);

template <typename T>
bool operator==(const Vector3<T>& left, const Vector3<T>& right);

typedef Vector2<unsigned int> Vector2u;
typedef Vector2<float> Vector2f;
typedef Vector2<int> Vector2i;

typedef Vector3<unsigned int> Vector3u;
typedef Vector3<float> Vector3f;
typedef Vector3<int> Vector3i;

#include <Truemess/System/Vector.inl>
}