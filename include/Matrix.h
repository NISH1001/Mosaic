#pragma once
#include <Vector.h>
#include <iostream>
#include <cstddef>

class Mat3
{
public:
    union
    {
        float m[3][3];
        Vec3 v[3];
    };
    
    Mat3(const Vec3& v1, const Vec3& v2, const Vec3& v3)
    {
        (*this)[0] = v1;
        (*this)[1] = v2;
        (*this)[2] = v3;
    }
    Mat3(float f = 1.0f)
    {
        (*this)[0] = Vec3(f, 0.0f, 0.0f);
        (*this)[1] = Vec3(0.0f, f, 0.0f);
        (*this)[2] = Vec3(0.0f, 0.0f, f);
    }
    Mat3(float m11, float m12, float m13,
         float m21, float m22, float m23,
         float m31, float m32, float m33)
    {
        m[0][0] = m11; m[0][1] = m12; m[0][2] = m13;
        m[1][0] = m21; m[1][1] = m22; m[1][2] = m23;
        m[2][0] = m31; m[2][1] = m32; m[2][2] = m33;
    }

    Vec3& operator[] (int n)
    {
        return v[n];
    }

    const Vec3& operator[] (int n) const
    {
         return v[n];
    }

    Mat3 operator+ (const Mat3& m2) const
    {
        return Mat3(
            m[0][0] + m2.m[0][0], m[0][1] + m2.m[0][1], m[0][2] + m2.m[0][2],
            m[1][0] + m2.m[1][0], m[1][1] + m2.m[1][1], m[1][2] + m2.m[1][2],
            m[2][0] + m2.m[2][0], m[2][1] + m2.m[2][1], m[2][2] + m2.m[2][2]
        );
    }

    Mat3 operator- (const Mat3& m2) const
    {
        return Mat3(
            m[0][0] - m2.m[0][0], m[0][1] - m2.m[0][1], m[0][2] - m2.m[0][2],
            m[1][0] - m2.m[1][0], m[1][1] - m2.m[1][1], m[1][2] - m2.m[1][2],
            m[2][0] - m2.m[2][0], m[2][1] - m2.m[2][1], m[2][2] - m2.m[2][2]
        );
    }

    Mat3 operator* (const Mat3& m2) const
    {
        return Mat3(
            (m[0][0]*m2.m[0][0] + m[0][1]*m2.m[1][0] + m[0][2]*m2.m[2][0]),
            (m[0][0]*m2.m[0][1] + m[0][1]*m2.m[1][1] + m[0][2]*m2.m[2][1]),
            (m[0][0]*m2.m[0][2] + m[0][1]*m2.m[1][2] + m[0][2]*m2.m[2][2]),
            (m[1][0]*m2.m[0][0] + m[1][1]*m2.m[1][0] + m[1][2]*m2.m[2][0]),
            (m[1][0]*m2.m[0][1] + m[1][1]*m2.m[1][1] + m[1][2]*m2.m[2][1]),
            (m[1][0]*m2.m[0][2] + m[1][1]*m2.m[1][2] + m[1][2]*m2.m[2][2]),
            (m[2][0]*m2.m[0][0] + m[2][1]*m2.m[1][0] + m[2][2]*m2.m[2][0]),
            (m[2][0]*m2.m[0][1] + m[2][1]*m2.m[1][1] + m[2][2]*m2.m[2][1]),
            (m[2][0]*m2.m[0][2] + m[2][1]*m2.m[1][2] + m[2][2]*m2.m[2][2])
        );
    }
    Vec3 operator* (const Vec3& v) const
    {
        return Vec3(
            (m[0][0]*v.x + m[0][1]*v.y + m[0][2]*v.z),
            (m[1][0]*v.x + m[1][1]*v.y + m[1][2]*v.z),
            (m[2][0]*v.x + m[2][1]*v.y + m[2][2]*v.z)
        );
    }
    Mat3 operator* (float f) const
    {
        return Mat3(
            m[0][0]*f, m[0][1]*f, m[0][2]*f,
            m[1][0]*f, m[1][1]*f, m[1][2]*f,
            m[2][0]*f, m[2][1]*f, m[2][2]*f
        );
    }
};

class Mat4
{
public:
    union
    {
        float m[4][4];
        Vec4 v[4];
    };
    
    Mat4(const Vec4& v1, const Vec4& v2, const Vec4& v3, const Vec4& v4)
    {
        (*this)[0] = v1;
        (*this)[1] = v2;
        (*this)[2] = v3;
        (*this)[3] = v4;
    }
    Mat4(float f = 1.0f)
    {
        (*this)[0] = Vec4(f, 0.0f, 0.0f, 0.0f);
        (*this)[1] = Vec4(0.0f, f, 0.0f, 0.0f);
        (*this)[2] = Vec4(0.0f, 0.0f, f, 0.0f);
        (*this)[2] = Vec4(0.0f, 0.0f, 0.0f, f);
    }
    Mat4(float m11, float m12, float m13, float m14,
         float m21, float m22, float m23, float m24,
         float m31, float m32, float m33, float m34,
         float m41, float m42, float m43, float m44)
    {
        m[0][0] = m11; m[0][1] = m12; m[0][2] = m13; m[0][3] = m14;
        m[1][0] = m21; m[1][1] = m22; m[1][2] = m23; m[1][3] = m24;
        m[2][0] = m31; m[2][1] = m32; m[2][2] = m33; m[2][3] = m34;
        m[3][0] = m41; m[3][1] = m42; m[3][2] = m43; m[3][3] = m44;
    }

    Vec4& operator[] (int n)
    {
        return v[n];
    }

    const Vec4& operator[] (int n) const
    {
         return v[n];
    }

    Mat4 operator+ (const Mat4& m2) const
    {
        return Mat4(
            m[0][0] + m2.m[0][0], m[0][1] + m2.m[0][1], m[0][2] + m2.m[0][2], m[0][3] + m2.m[0][3],
            m[1][0] + m2.m[1][0], m[1][1] + m2.m[1][1], m[1][2] + m2.m[1][2], m[1][3] + m2.m[1][3],
            m[2][0] + m2.m[2][0], m[2][1] + m2.m[2][1], m[2][2] + m2.m[2][2], m[2][3] + m2.m[2][3],
            m[3][0] + m2.m[3][0], m[3][1] + m2.m[3][1], m[3][2] + m2.m[3][2], m[3][3] + m2.m[3][3]
        );
    }

    Mat4 operator- (const Mat4& m2) const
    {
        return Mat4(
            m[0][0] - m2.m[0][0], m[0][1] - m2.m[0][1], m[0][2] - m2.m[0][2], m[0][3] - m2.m[0][3],
            m[1][0] - m2.m[1][0], m[1][1] - m2.m[1][1], m[1][2] - m2.m[1][2], m[1][3] - m2.m[1][3],
            m[2][0] - m2.m[2][0], m[2][1] - m2.m[2][1], m[2][2] - m2.m[2][2], m[2][3] - m2.m[2][3],
            m[3][0] - m2.m[3][0], m[3][1] - m2.m[3][1], m[3][2] - m2.m[3][2], m[3][3] - m2.m[3][3]
        );
    }

    Mat4 operator* (const Mat4& m2) const
    {
        return Mat4(
            (m[0][0]*m2.m[0][0] + m[0][1]*m2.m[1][0] + m[0][2]*m2.m[2][0] + m[0][3]*m2.m[3][0]),
            (m[0][0]*m2.m[0][1] + m[0][1]*m2.m[1][1] + m[0][2]*m2.m[2][1] + m[0][3]*m2.m[3][1]),
            (m[0][0]*m2.m[0][2] + m[0][1]*m2.m[1][2] + m[0][2]*m2.m[2][2] + m[0][3]*m2.m[3][2]),
            (m[0][0]*m2.m[0][3] + m[0][1]*m2.m[1][3] + m[0][2]*m2.m[2][3] + m[0][3]*m2.m[3][3]),
            (m[1][0]*m2.m[0][0] + m[1][1]*m2.m[1][0] + m[1][2]*m2.m[2][0] + m[1][3]*m2.m[3][0]),
            (m[1][0]*m2.m[0][1] + m[1][1]*m2.m[1][1] + m[1][2]*m2.m[2][1] + m[1][3]*m2.m[3][1]),
            (m[1][0]*m2.m[0][2] + m[1][1]*m2.m[1][2] + m[1][2]*m2.m[2][2] + m[1][3]*m2.m[3][2]),
            (m[1][0]*m2.m[0][3] + m[1][1]*m2.m[1][3] + m[1][2]*m2.m[2][3] + m[1][3]*m2.m[3][3]),
            (m[2][0]*m2.m[0][0] + m[2][1]*m2.m[1][0] + m[2][2]*m2.m[2][0] + m[2][3]*m2.m[3][0]),
            (m[2][0]*m2.m[0][1] + m[2][1]*m2.m[1][1] + m[2][2]*m2.m[2][1] + m[2][3]*m2.m[3][1]),
            (m[2][0]*m2.m[0][2] + m[2][1]*m2.m[1][2] + m[2][2]*m2.m[2][2] + m[2][3]*m2.m[3][2]),
            (m[2][0]*m2.m[0][3] + m[2][1]*m2.m[1][3] + m[2][2]*m2.m[2][3] + m[2][3]*m2.m[3][3]),
            (m[3][0]*m2.m[0][0] + m[3][1]*m2.m[1][0] + m[3][2]*m2.m[2][0] + m[3][3]*m2.m[3][0]),
            (m[3][0]*m2.m[0][1] + m[3][1]*m2.m[1][1] + m[3][2]*m2.m[2][1] + m[3][3]*m2.m[3][1]),
            (m[3][0]*m2.m[0][2] + m[3][1]*m2.m[1][2] + m[3][2]*m2.m[2][2] + m[3][3]*m2.m[3][2]),
            (m[3][0]*m2.m[0][3] + m[3][1]*m2.m[1][3] + m[3][2]*m2.m[2][3] + m[3][3]*m2.m[3][3])
        );
    }
    Vec4 operator* (const Vec4& v) const
    {
        return Vec4(
            (m[0][0]*v.x + m[0][1]*v.y + m[0][2]*v.z + m[0][3]*v.w),
            (m[1][0]*v.x + m[1][1]*v.y + m[1][2]*v.z + m[1][3]*v.w),
            (m[2][0]*v.x + m[2][1]*v.y + m[2][2]*v.z + m[2][3]*v.w),
            (m[3][0]*v.x + m[3][1]*v.y + m[3][2]*v.z + m[3][3]*v.w)
        );
    }
    Mat4 operator* (float f) const
    {
        return Mat4(
            m[0][0]*f, m[0][1]*f, m[0][2]*f, m[0][3]*f,
            m[1][0]*f, m[1][1]*f, m[1][2]*f, m[1][3]*f,
            m[2][0]*f, m[2][1]*f, m[2][2]*f, m[2][3]*f,
            m[3][0]*f, m[3][1]*f, m[3][2]*f, m[3][3]*f
        );
    }
};

inline std::ostream& operator << (std::ostream &os, const Mat3 &m)
{
    for (int i=0; i<3; ++i)
    {
        os << std::endl;
        for (int j=0; j<3; ++j)
            os << m.m[i][j] << "  ";
    }
    return os;
}

inline std::ostream& operator << (std::ostream &os, const Mat4 &m)
{
    for (int i=0; i<4; ++i)
    {
        os << std::endl;
        for (int j=0; j<4; ++j)
            os << m.m[i][j] << "  ";
    }
    return os;
}

