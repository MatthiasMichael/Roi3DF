#pragma once

#include <iostream>

#include "vec_template.h"

#include <osg/Vec3>
#include <osg/Vec4>


template<>
inline float x(const osg::Vec3 & v)
{
	return v.x();
}


template<>
inline float y(const osg::Vec3 & v)
{
	return v.y();
}
	
	
template<>
inline float z(const osg::Vec3 & v)
{
	return v.z();
}
	

template<>
inline osg::Vec3 make_vec3D(float x, float y, float z)
{
	return osg::Vec3(x, y, z);
}


template<>
inline float x(const osg::Vec4 & v)
{
	return v.x();
}


template<>
inline float y(const osg::Vec4 & v)
{
	return v.y();
}


template<>
inline float z(const osg::Vec4 & v)
{
	return v.z();
}


template<>
inline float w(const osg::Vec4 & v)
{
	return v.w();
}


template<>
inline osg::Vec4 make_vec4D(float x, float y, float z, float w)
{
	return osg::Vec4(x, y, z, w);
}


template<>
struct is_vector_3D<osg::Vec3>
{
	using type = std::true_type;
	static constexpr bool value = true;
};


template<>
struct is_vector_4D<osg::Vec4>
{
	using type = std::true_type;
	static constexpr bool value = true;
};


// Lines blow here are necessary until MSVC fixes this problem: 
// https://developercommunity.visualstudio.com/content/problem/235349/conditionally-compiling-template-operator-overload.html

inline std::ostream & operator<<(std::ostream & os, const osg::Vec3 & v)
{
	return os << "(" << v.x() << ", " << v.y() << ", " << v.z() << ")";
}


inline std::ostream & operator<<(std::ostream & os, const osg::Vec4 & v)
{
	return os << "(" << v.x() << ", " << v.y() << ", " << v.z() << ", " << v.w() << ")";
}


inline osg::Vec3 operator*(float f, const osg::Vec3 & v)
{
	return v * f;
}


inline osg::Vec4 operator*(float f, const osg::Vec4 & v)
{
	return v * f;
}