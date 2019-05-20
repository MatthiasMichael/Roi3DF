#pragma once

#include <type_traits>

#include "cuda_host_device.h"


template<typename TVector>
_HOST_DEVICE_ float x(const TVector & v)
{
#ifndef __CUDACC__
	static_assert(false, "Provide your own implementation of component access for your specific vector type.");
#endif
	return 0;
}


template<typename TVector>
_HOST_DEVICE_ float y(const TVector & v)
{
#ifndef __CUDACC__
	static_assert(false, "Provide your own implementation of component access for your specific vector type.");
#endif
	return 0;
}


template<typename TVector>
_HOST_DEVICE_ float z(const TVector & v)
{
#ifndef __CUDACC__
	static_assert(false, "Provide your own implementation of component access for your specific vector type.");
#endif
	return 0;
}


template<typename TVector>
_HOST_DEVICE_ float w(const TVector & v)
{
#ifndef __CUDACC__
	static_assert(false, "Provide your own implementation of component access for your specific vector type.");
#endif
	return 0;
}


template<typename TVector3D>
_HOST_DEVICE_ TVector3D make_vec3D(float x, float y, float z)
{
#ifndef __CUDACC__
	static_assert(false, "Provide your own implementation of vector creation");
#endif
	return TVector3D();
}


template<typename TVector4D>
_HOST_DEVICE_ TVector4D make_vec4D(float x, float y, float z, float w)
{
#ifndef __CUDACC__
	static_assert(false, "Provide your own implementation of vector creation");
#endif
	return TVector4D();
}


template<typename TVector>
struct is_vector_3D
{
	using type = std::false_type;
	static constexpr bool value = false;
};


template<typename TVector>
struct is_vector_4D
{
	using type = std::false_type;
	static constexpr bool value = false;
};