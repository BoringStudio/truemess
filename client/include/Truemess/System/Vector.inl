/////////////////////////////////////////////////////////////////////////////////////////
// Vector2
/////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
Vector2<T>::Vector2() :
    x(0),
    y(0)
{
    
}

template<typename T>
Vector2<T>::Vector2(T x, T y) :
    x(x),
    y(y)
{

}

template<typename T>
template<typename From>
Vector2<T>::Vector2(const Vector2<From>& vector) :
	x(static_cast<T>(vector.x)),
	y(static_cast<T>(vector.y))
{

}

template<typename T>
Vector2<T> Vector2<T>::operator+(const Vector2<T>& left, const T& right)
{
	return Vector2<T>(left.x + right, left.y + right);
}

template<typename T>
Vector2<T> Vector2<T>::operator-(const Vector2<T>& left, const T& right)
{
	return Vector2<T>(left.x - right, left.y - right);
}

template<typename T>
Vector2<T> Vector2<T>::operator*(const Vector2<T>& left, const T& right)
{
	return Vector2<T>(left.x * right, left.y * right);
}

template<typename T>
Vector2<T> Vector2<T>::operator/(const Vector2<T>& left, const T& right)
{
	return Vector2<T>(left.x / right, left.y / right);
}

template<typename T>
Vector2<T> Vector2<T>::operator+(const Vector2<T>& left)
{
	return left;
}

template<typename T>
Vector2<T> Vector2<T>::operator-(const Vector2<T>& left)
{
	return Vector2<T>(-left.x, -left.y);
}

template<typename T>
Vector2<T>& Vector2<T>::operator+=(Vector2<T>& left, const T& right)
{
	this->x += right;
	this->y += right;
	return this;
}

template<typename T>
Vector2<T>& Vector2<T>::operator-=(Vector2<T>& left, const T& right)
{
	this->x -= right;
	this->y -= right;
	return this;
}

template<typename T>
Vector2<T>& Vector2<T>::operator*=(Vector2<T>& left, const T& right)
{
	this->x *= right;
	this->y *= right;
	return this;
}

template<typename T>
Vector2<T>& Vector2<T>::operator/=(Vector2<T>& left, const T& right)
{
	this->x /= right;
	this->y /= right;
	return this;
}

template<typename T>
bool Vector2<T>::operator==(const Vector2<T>& left, const Vector2<T>& right)
{
	return (left.x == right.x) && (left.y == right.y);
}

/////////////////////////////////////////////////////////////////////////////////////////
// Vector3
/////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
Vector3<T>::Vector3() :
	x(0),
	y(0),
    z(0)
{

}

template<typename T>
Vector3<T>::Vector3(T x, T y, T z) :
	x(x),
	y(y),
    z(z)
{

}

template<typename T>
template<typename From>
Vector3<T>::Vector3(const Vector3<From>& vector) :
	x(static_cast<T>(vector.x)),
	y(static_cast<T>(vector.y)),
	z(static_cast<T>(vector.z))
{

}

template<typename T>
Vector3<T> Vector3<T>::operator+(const Vector3<T>& left, const T& right)
{
	return Vector3<T>(left.x + right, left.y + right, left.z + right);
}

template<typename T>
Vector3<T> Vector3<T>::operator-(const Vector3<T>& left, const T& right)
{
	return Vector3<T>(left.x - right, left.y - right, left.z - right);
}

template<typename T>
Vector3<T> Vector3<T>::operator*(const Vector3<T>& left, const T& right)
{
	return Vector3<T>(left.x * right, left.y * right, left.z * right);
}

template<typename T>
Vector3<T> Vector3<T>::operator/(const Vector3<T>& left, const T& right)
{
	return Vector3<T>(left.x / right, left.y / right, left.z / right);
}

template<typename T>
Vector3<T> Vector3<T>::operator+(const Vector3<T>& left)
{
	return left;
}

template<typename T>
Vector3<T> Vector3<T>::operator-(const Vector3<T>& left)
{
	return Vector3<T>(-left.x, -left.y, -left.z);
}

template<typename T>
Vector3<T>& Vector3<T>::operator+=(Vector3<T>& left, const T& right)
{
	this->x += right;
	this->y += right;
	this->z += right;
	return this;
}

template<typename T>
Vector3<T>& Vector3<T>::operator-=(Vector3<T>& left, const T& right)
{
	this->x -= right;
	this->y -= right;
	this->z -= right;
	return this;
}

template<typename T>
Vector3<T>& Vector3<T>::operator*=(Vector3<T>& left, const T& right)
{
	this->x *= right;
	this->y *= right;
	this->z *= right;
	return this;
}

template<typename T>
Vector3<T>& Vector3<T>::operator/=(Vector3<T>& left, const T& right)
{
	this->x /= right;
	this->y /= right;
	this->z /= right;
	return this;
}

template<typename T>
bool Vector3<T>::operator==(const Vector3<T>& left, const Vector3<T>& right)
{
	return (left.x == right.x) && (left.y == right.y) && (left.z == right.z);
}