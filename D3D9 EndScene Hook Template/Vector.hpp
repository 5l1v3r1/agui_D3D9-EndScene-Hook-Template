#pragma once


class Vector3;
struct matrix3x3;
struct matrix3x4_t;
typedef Vector3 QAngle;

class Vector3
{
public:
    union
    {
        struct
        {
            float x;
            float y;
            float z;
        };
    };

public:
    Vector3(void);
    Vector3(float x, float y, float z);
    Vector3(const Vector3& vec);
    Vector3 operator +(const Vector3& other);
    Vector3 operator +(const float& other);
    Vector3 operator +=(const Vector3& other);
    Vector3 operator +=(const float& other);
    Vector3 operator -(const Vector3& other);
    Vector3 operator -(const float& other);
    Vector3 operator -=(const Vector3& other);
    Vector3 operator -=(const float& other);
    Vector3 operator *(const Vector3& other);
    Vector3 operator *(const float& other);
    Vector3 operator *=(const Vector3& other);
    Vector3 operator *=(const float& other);
    Vector3 operator /(const Vector3& other);
    Vector3 operator /(const float& other);
    Vector3 operator /=(const Vector3& other);
    Vector3 operator /=(const float& other);
    Vector3& operator =(const Vector3& other);
    Vector3 operator =(const float& other);
    const bool operator ==(const Vector3& other) const;
    const bool operator ==(const float& other) const;
    const bool operator !=(const Vector3& other) const;
    const bool operator !=(const float& other) const;
    const bool operator <(const Vector3& other) const;
    const bool operator <(const float& other) const;
    const bool operator <=(const Vector3& other) const;
    const bool operator <=(const float& other) const;
    const bool operator >(const Vector3& other) const;
    const bool operator >(const float& other) const;
    const bool operator >=(const Vector3& other) const;
    const bool operator >=(const float& other) const;
    float& operator [](int iIndex);
    const float& operator [](int iIndex) const;
    const bool empty(void) const;
    const float DotProduct(const Vector3& other) const;
    const float DotProduct(const float* other) const;
    const Vector3 CrossProduct(const Vector3& other);
    float GetLengthXYZ(void);
    float GetLengthXY(void);
    float GetLength3D(void);
    float GetLength2D(void);
    void Init(float x, float y, float z);
    void Init(Vector3& vec);
    void Init(const Vector3& vec);
    void Normalize(void);
    void NormalizeInPlace(void);
};

struct matrix3x4_t
{
    matrix3x4_t()
    {
    }

    matrix3x4_t(
        float m00, float m01, float m02, float m03,
        float m10, float m11, float m12, float m13,
        float m20, float m21, float m22, float m23)
    {
        m_flMatVal[0][0] = m00;
        m_flMatVal[0][1] = m01;
        m_flMatVal[0][2] = m02;
        m_flMatVal[0][3] = m03;
        m_flMatVal[1][0] = m10;
        m_flMatVal[1][1] = m11;
        m_flMatVal[1][2] = m12;
        m_flMatVal[1][3] = m13;
        m_flMatVal[2][0] = m20;
        m_flMatVal[2][1] = m21;
        m_flMatVal[2][2] = m22;
        m_flMatVal[2][3] = m23;
    }

    //-----------------------------------------------------------------------------
    // Creates a matrix where the X axis = forward
    // the Y axis = left, and the Z axis = up
    //-----------------------------------------------------------------------------
    void Init(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis, const Vector3& vecOrigin)
    {
        m_flMatVal[0][0] = xAxis.x;
        m_flMatVal[0][1] = yAxis.x;
        m_flMatVal[0][2] = zAxis.x;
        m_flMatVal[0][3] = vecOrigin.x;
        m_flMatVal[1][0] = xAxis.y;
        m_flMatVal[1][1] = yAxis.y;
        m_flMatVal[1][2] = zAxis.y;
        m_flMatVal[1][3] = vecOrigin.y;
        m_flMatVal[2][0] = xAxis.z;
        m_flMatVal[2][1] = yAxis.z;
        m_flMatVal[2][2] = zAxis.z;
        m_flMatVal[2][3] = vecOrigin.z;
    }

    //-----------------------------------------------------------------------------
    // Creates a matrix where the X axis = forward
    // the Y axis = left, and the Z axis = up
    //-----------------------------------------------------------------------------
    matrix3x4_t(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis, const Vector3& vecOrigin)
    {
        Init(xAxis, yAxis, zAxis, vecOrigin);
    }

    inline void SetOrigin(Vector3 const& p)
    {
        m_flMatVal[0][3] = p.x;
        m_flMatVal[1][3] = p.y;
        m_flMatVal[2][3] = p.z;
    }

    float* operator[](int i)
    {
        return m_flMatVal[i];
    }

    const float* operator[](int i) const
    {
        return m_flMatVal[i];
    }

    float* Base()
    {
        return &m_flMatVal[0][0];
    }

    const float* Base() const
    {
        return &m_flMatVal[0][0];
    }

    float m_flMatVal[3][4];
};

struct AABB
{
    Vector3 vMin;
    Vector3 vMax;
};

const Vector3 vec_origin(0, 0, 0);
