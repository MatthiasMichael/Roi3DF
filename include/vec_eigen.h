#pragma once

#include "vec_template.h"

#include "Eigen/Core"

using Eigen::Vector3d;
using Eigen::Vector4d;

using Eigen::Vector3f;
using Eigen::Vector4f;

//No _HOST_DEVICE_ via "cuda_host_device.h" since nvcc can't compile Eigen anyway.

template<>
inline float x(const Vector3d & v)
{
	return static_cast<float>( v(0) );
}


template<>
inline float y(const Vector3d & v)
{
	return static_cast<float>( v(1) );
}
	
	
template<>
inline float z(const Vector3d & v)
{
	return static_cast<float>( v(2) );
}
	

template<>
inline Vector3d make_vec3D(float x, float y, float z)
{
	return Vector3d(x, y, z);
}


template<>
inline float x(const Vector4d & v)
{
	return static_cast<float>( v(0) );
}


template<>
inline float y(const Vector4d & v)
{
	return static_cast<float>( v(1) );
}


template<>
inline float z(const Vector4d & v)
{
	return static_cast<float>( v(2) );
}


template<>
inline float w(const Vector4d & v)
{
	return static_cast<float>( v(3) );
}


template<>
inline Vector4d make_vec4D(float x, float y, float z, float w)
{
	return Vector4d(x, y, z, w);
}


template<>
inline float x(const Vector3f & v)
{
	return v(0);
}


template<>
inline float y(const Vector3f & v)
{
	return v(1);
}


template<>
inline float z(const Vector3f & v)
{
	return v(2);
}


template<>
inline Vector3f make_vec3D(float x, float y, float z)
{
	return Vector3f(x, y, z);
}


template<>
inline float x(const Vector4f & v)
{
	return v(0);
}


template<>
inline float y(const Vector4f & v)
{
	return v(1);
}


template<>
inline float z(const Vector4f & v)
{
	return v(2);
}


template<>
inline float w(const Vector4f & v)
{
	return v(3);
}


template<>
inline Vector4f make_vec4D(float x, float y, float z, float w)
{
	return Vector4f(x, y, z, w);
}


template<>
struct is_vector_3D<Vector3d>
{
	using type = std::true_type;
	static constexpr bool value = true;
};


template<>
struct is_vector_3D<Vector3f>
{
	using type = std::true_type;
	static constexpr bool value = true;
};


template<>
struct is_vector_4D<Vector4d>
{
	using type = std::true_type;
	static constexpr bool value = true;
};


template<>
struct is_vector_4D<Vector4f>
{
	using type = std::true_type;
	static constexpr bool value = true;
};