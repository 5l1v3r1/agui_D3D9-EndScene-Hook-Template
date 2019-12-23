#pragma once
#include "stdafx.h"
#include "Vector.hpp"
#include <math.h>
#include <cfloat>

Vector::Vector(void)
{
    Init(0.f, 0.f, 0.f);
}

Vector::Vector(float x, float y, float z)
{
    Init(x, y, z);
}

Vector::Vector(const Vector& vec)
{
    Init(vec);
}

Vector Vector::operator +(const Vector& other)
{
    return Vector(x + other.x, y + other.y, z + other.z);
}

Vector Vector::operator +(const float& other)
{
    return Vector(x + other, y + other, z + other);
}

Vector Vector::operator +=(const Vector& other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

Vector Vector::operator +=(const float& other)
{
    x += other;
    y += other;
    z += other;
    return *this;
}

Vector Vector::operator -(const Vector& other)
{
    return Vector(x - other.x, y - other.y, z - other.z);
}

Vector Vector::operator -(const float& other)
{
    return Vector(x - other, y - other, z - other);
}

Vector Vector::operator -=(const Vector& other)
{
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

Vector Vector::operator -=(const float& other)
{
    x -= other;
    y -= other;
    z -= other;
    return *this;
}

Vector Vector::operator *(const Vector& other)
{
    return Vector(x * other.x, y * other.y, z * other.z);
}

Vector Vector::operator *(const float& other)
{
    return Vector(x * other, y * other, z * other);
}

Vector Vector::operator *=(const Vector& other)
{
    x *= other.x;
    y *= other.y;
    z *= other.z;
    return *this;
}

Vector Vector::operator *=(const float& other)
{
    x *= other;
    y *= other;
    z *= other;
    return *this;
}

Vector Vector::operator /(const Vector& other)
{
    return Vector(x / other.x, y / other.y, z / other.z);
}

Vector Vector::operator /(const float& other)
{
    return Vector(x / other, y / other, z / other);
}

Vector Vector::operator /=(const Vector& other)
{
    x /= other.x;
    y /= other.y;
    z /= other.z;
    return *this;
}

Vector Vector::operator /=(const float& other)
{
    x /= other;
    y /= other;
    z /= other;
    return *this;
}

Vector& Vector::operator =(const Vector& other)
{
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
}

Vector Vector::operator =(const float& other)
{
    x = other;
    y = other;
    z = other;
    return *this;
}

const bool Vector::operator ==(const Vector& other) const
{
    return (x == other.x && y == other.y && z == other.z);
}

const bool Vector::operator ==(const float& other) const
{
    return (x == other && y == other && z == other);
}

const bool Vector::operator !=(const Vector& other) const
{
    return (x != other.x && y != other.y && z != other.z);
}

const bool Vector::operator !=(const float& other) const
{
    return (x != other && y != other && z != other);
}

const bool Vector::operator <(const Vector& other) const
{
    return (x < other.x && y < other.y && z < other.z);
}

const bool Vector::operator <(const float& other) const
{
    return (x < other && y < other && z < other);
}

const bool Vector::operator <=(const Vector& other) const
{
    return (x <= other.x && y <= other.y && z <= other.z);
}

const bool Vector::operator <=(const float& other) const
{
    return (x <= other && y <= other && z <= other);
}

const bool Vector::operator >(const Vector& other) const
{
    return (x > other.x&& y > other.y&& z > other.z);
}

const bool Vector::operator >(const float& other) const
{
    return (x > other&& y > other&& z > other);
}

const bool Vector::operator >=(const Vector& other) const
{
    return (x >= other.x && y >= other.y && z >= other.z);
}

const bool Vector::operator >=(const float& other) const
{
    return (x >= other && y >= other && z >= other);
}

float& Vector::operator [](int iIndex)
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

const float& Vector::operator [](int iIndex) const
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

const bool Vector::empty(void) const
{
    return (x == 0.f && y == 0.f && z == 0.f);
}

const float Vector::DotProduct(const Vector& other) const
{
    return (x * other.x + y * other.y + z * other.z);
}

const float Vector::DotProduct(const float* other) const
{
    return (x * other[0] + y * other[1] + z * other[2]);
}

const Vector Vector::CrossProduct(const Vector& other)
{
    auto n_x = y * other.z - z * other.y;
    auto n_y = z * other.x - x * other.z;
    auto n_z = x * other.y - y * other.x;
    return Vector(n_x, n_y, n_z);
}

float Vector::GetLengthXYZ(void)
{
    return float(sqrtf(x * x + y * y + z * z));
}

float Vector::GetLengthXY(void)
{
    return float(sqrtf(x * x + y * y));
}

float Vector::GetLength3D(void)
{
    return GetLengthXYZ();
}

float Vector::GetLength2D(void)
{
    return GetLengthXY();
}

void Vector::Init(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

void Vector::Init(Vector& vec)
{
    x = vec.x;
    y = vec.y;
    z = vec.z;
}

void Vector::Init(const Vector& vec)
{
    x = vec.x;
    y = vec.y;
    z = vec.z;
}

void Vector::Normalize(void)
{
    float flLen = GetLengthXYZ();
    *this *= 1.f / flLen;
}

void Vector::NormalizeInPlace(void)
{
    float iradius = 1.f / (this->GetLength3D() + FLT_EPSILON);
    *this *= iradius;
}
