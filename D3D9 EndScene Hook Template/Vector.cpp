#pragma once
#include "stdafx.h"
#include <math.h>
#include <cfloat>
#include "Vector.hpp"

Vector3::Vector3(void)
{
    Init(0.f, 0.f, 0.f);
}

Vector3::Vector3(float x, float y, float z)
{
    Init(x, y, z);
}

Vector3::Vector3(const Vector3& vec)
{
    Init(vec);
}

Vector3 Vector3::operator +(const Vector3& other)
{
    return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3 Vector3::operator +(const float& other)
{
    return Vector3(x + other, y + other, z + other);
}

Vector3 Vector3::operator +=(const Vector3& other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

Vector3 Vector3::operator +=(const float& other)
{
    x += other;
    y += other;
    z += other;
    return *this;
}

Vector3 Vector3::operator -(const Vector3& other)
{
    return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3 Vector3::operator -(const float& other)
{
    return Vector3(x - other, y - other, z - other);
}

Vector3 Vector3::operator -=(const Vector3& other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

Vector3 Vector3::operator -=(const float& other)
{
    x -= other;
    y -= other;
    z -= other;
    return *this;
}

Vector3 Vector3::operator *(const Vector3& other)
{
    return Vector3(x * other.x, y * other.y, z * other.z);
}

Vector3 Vector3::operator *(const float& other)
{
    return Vector3(x * other, y * other, z * other);
}

Vector3 Vector3::operator *=(const Vector3& other)
{
    x *= other.x;
    y *= other.y;
    z *= other.z;
    return *this;
}

Vector3 Vector3::operator *=(const float& other)
{
    x *= other;
    y *= other;
    z *= other;
    return *this;
}

Vector3 Vector3::operator /(const Vector3& other)
{
    return Vector3(x / other.x, y / other.y, z / other.z);
}

Vector3 Vector3::operator /(const float& other)
{
    return Vector3(x / other, y / other, z / other);
}

Vector3 Vector3::operator /=(const Vector3& other)
{
    x /= other.x;
    y /= other.y;
    z /= other.z;
    return *this;
}

Vector3 Vector3::operator /=(const float& other)
{
    x /= other;
    y /= other;
    z /= other;
    return *this;
}

Vector3& Vector3::operator =(const Vector3& other)
{
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
}

Vector3 Vector3::operator =(const float& other)
{
    x = other;
    y = other;
    z = other;
    return *this;
}

const bool Vector3::operator ==(const Vector3& other) const
{
    return (x == other.x && y == other.y && z == other.z);
}

const bool Vector3::operator ==(const float& other) const
{
    return (x == other && y == other && z == other);
}

const bool Vector3::operator !=(const Vector3& other) const
{
    return (x != other.x && y != other.y && z != other.z);
}

const bool Vector3::operator !=(const float& other) const
{
    return (x != other && y != other && z != other);
}

const bool Vector3::operator <(const Vector3& other) const
{
    return (x < other.x && y < other.y && z < other.z);
}

const bool Vector3::operator <(const float& other) const
{
    return (x < other && y < other && z < other);
}

const bool Vector3::operator <=(const Vector3& other) const
{
    return (x <= other.x && y <= other.y && z <= other.z);
}

const bool Vector3::operator <=(const float& other) const
{
    return (x <= other && y <= other && z <= other);
}

const bool Vector3::operator >(const Vector3& other) const
{
    return (x > other.x&& y > other.y&& z > other.z);
}

const bool Vector3::operator >(const float& other) const
{
    return (x > other&& y > other&& z > other);
}

const bool Vector3::operator >=(const Vector3& other) const
{
    return (x >= other.x && y >= other.y && z >= other.z);
}

const bool Vector3::operator >=(const float& other) const
{
    return (x >= other && y >= other && z >= other);
}

float& Vector3::operator [](int iIndex)
{
    switch (iIndex)
    {
    case 1:
        return y;

    case 2:
        return z;

    default:
        return x;
    }
}

const float& Vector3::operator [](int iIndex) const
{
    switch (iIndex)
    {
    case 1:
        return y;

    case 2:
        return z;

    default:
        return x;
    }
}

const bool Vector3::empty(void) const
{
    return (x == 0.f && y == 0.f && z == 0.f);
}

const float Vector3::DotProduct(const Vector3& other) const
{
    return (x * other.x + y * other.y + z * other.z);
}

const float Vector3::DotProduct(const float* other) const
{
    return (x * other[0] + y * other[1] + z * other[2]);
}

const Vector3 Vector3::CrossProduct(const Vector3& other)
{
    auto n_x = y * other.z - z * other.y;
    auto n_y = z * other.x - x * other.z;
    auto n_z = x * other.y - y * other.x;
    return Vector3(n_x, n_y, n_z);
}

float Vector3::GetLengthXYZ(void)
{
    return float(sqrtf(x * x + y * y + z * z));
}

float Vector3::GetLengthXY(void)
{
    return float(sqrtf(x * x + y * y));
}

float Vector3::GetLength3D(void)
{
    return GetLengthXYZ();
}

float Vector3::GetLength2D(void)
{
    return GetLengthXY();
}

void Vector3::Init(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

void Vector3::Init(Vector3& vec)
{
    x = vec.x;
    y = vec.y;
    z = vec.z;
}

void Vector3::Init(const Vector3& vec)
{
    x = vec.x;
    y = vec.y;
    z = vec.z;
}

void Vector3::Normalize(void)
{
    float flLen = GetLengthXYZ();
    *this *= 1.f / flLen;
}

void Vector3::NormalizeInPlace(void)
{
    float iradius = 1.f / (this->GetLength3D() + FLT_EPSILON);
    *this *= iradius;
}
