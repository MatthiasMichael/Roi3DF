#pragma once

#include <iostream>

// CUDA includes
#include "vector_types.h" 
#include "vector_functions.h"

#include "vec_template.h"

#include "cuda_host_device.h"


template<>
inline _HOST_DEVICE_ float x(const float3 & v)
{
	return v.x;
}


template<>
inline _HOST_DEVICE_ float y(const float3 & v)
{
	return v.y;
}
	
	
template<>
inline _HOST_DEVICE_ float z(const float3 & v)
{
	return v.z;
}
	

template<>
inline _HOST_DEVICE_ float3 make_vec3D(float x, float y, float z)
{
	return make_float3(x, y, z);
}


template<>
inline _HOST_DEVICE_ float x(const float4 & v)
{
	return v.x;
}


template<>
inline _HOST_DEVICE_ float y(const float4 & v)
{
	return v.y;
}


template<>
inline _HOST_DEVICE_ float z(const float4 & v)
{
	return v.z;
}


template<>
inline _HOST_DEVICE_ float w(const float4 & v)
{
	return v.w;
}


template<>
inline _HOST_DEVICE_ float4 make_vec4D(float x, float y, float z, float w)
{
	return make_float4(x, y, z, w);
}


template<>
struct is_vector_3D<float3>
{
	using type = std::true_type;
	static constexpr bool value = true;
};


template<>
struct is_vector_4D<float4>
{
	using type = std::true_type;
	static constexpr bool value = true;
};


// Lines blow here are necessary until MSVC fixes this problem: 
// https://developercommunity.visualstudio.com/content/problem/235349/conditionally-compiling-template-operator-overload.html

inline std::ostream & operator<<(std::ostream & os, const float3 & v)
{
	return os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}


inline std::ostream & operator<<(std::ostream & os, const float4 & v)
{
	return os << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
}