#pragma once

#include "vec_template.h"

#include <QVector3D>
#include <QVector4D>


template<>
inline float x(const QVector3D & v)
{
	return v.x();
}


template<>
inline float y(const QVector3D & v)
{
	return v.y();
}


template<>
inline float z(const QVector3D & v)
{
	return v.z();
}


template<>
inline QVector3D make_vec3D(float x, float y, float z)
{
	return QVector3D(x, y, z);
}


template<>
inline float x(const QVector4D & v)
{
	return v.x();
}


template<>
inline float y(const QVector4D & v)
{
	return v.y();
}


template<>
inline float z(const QVector4D & v)
{
	return v.z();
}


template<>
inline float w(const QVector4D & v)
{
	return v.w();
}


template<>
inline QVector4D make_vec4D(float x, float y, float z, float w)
{
	return QVector4D(x, y, z, w);
}


template<>
struct is_vector_3D<QVector3D>
{
	using type = std::true_type;
	static constexpr bool value = true;
};


template<>
struct is_vector_4D<QVector4D>
{
	using type = std::true_type;
	static constexpr bool value = true;
};


// Lines blow here are necessary until MSVC fixes this problem: 
// https://developercommunity.visualstudio.com/content/problem/235349/conditionally-compiling-template-operator-overload.html

inline std::ostream & operator<<(std::ostream & os, const QVector3D & v)
{
	return os << "(" << v.x() << ", " << v.y() << ", " << v.z() << ")";
}


inline std::ostream & operator<<(std::ostream & os, const QVector4D & v)
{
	return os << "(" << v.x() << ", " << v.y() << ", " << v.z() << ", " << v.w() << ")";
}