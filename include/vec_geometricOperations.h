#pragma once

#include <type_traits>
#include <iostream>

#include "check_function_existence.h"

// This file provides operator overloads and some general functions
// for vector types if the type does not already provide these on its own

CHECK_FUNCTION( norm, norm )
CHECK_FUNCTION( normalize, normalize )

// Check for the existence of operators is broken in older versions of MSVC
CHECK_OPERATOR(plus, +)
CHECK_OPERATOR(minus, -)
CHECK_OPERATOR(mult, *)
CHECK_OPERATOR(div, /)

CHECK_OPERATOR(out, <<)


template<typename TVector3D,
	std::enable_if_t
	<
		!has_operator_plus<TVector3D, TVector3D, TVector3D>::value &&
		is_vector_3D<TVector3D>::value
	> * = nullptr
>
TVector3D operator+(const TVector3D & lhs, const TVector3D & rhs)
{
	return make_vec3D<TVector3D>(x(lhs) + x(rhs), y(lhs) + y(rhs), z(lhs) + z(rhs));
}


template<typename TVector4D,
	std::enable_if_t
	<
		!has_operator_plus<TVector4D, TVector4D, TVector4D>::value &&
		is_vector_4D<TVector4D>::value
	> * = nullptr
>
TVector4D operator+(const TVector4D & lhs, const TVector4D & rhs)
{
	return make_vec4D<TVector4D>(x(lhs) + x(rhs), y(lhs) + y(rhs), z(lhs) + z(rhs), w(lhs) + w(rhs));
}


template<typename TVector3D,
	std::enable_if_t
	<
		!has_operator_minus<TVector3D, TVector3D, TVector3D>::value &&
		is_vector_3D<TVector3D>::value
	> * = nullptr
>
TVector3D operator-(const TVector3D & lhs, const TVector3D & rhs)
{
	return make_vec3D<TVector3D>(x(lhs) - x(rhs), y(lhs) - y(rhs), z(lhs) - z(rhs));
}


template<typename TVector4D,
	std::enable_if_t
	<
		!has_operator_minus<TVector4D, TVector4D, TVector4D>::value &&
		is_vector_4D<TVector4D>::value
	> * = nullptr
>
TVector4D operator-(const TVector4D & lhs, const TVector4D & rhs)
{
	return make_vec4D<TVector4D>(x(lhs) - x(rhs), y(lhs) - y(rhs), z(lhs) - z(rhs), w(lhs) - w(rhs));
}


template<typename TVector3D,
	std::enable_if_t
	<
		!has_operator_mult<TVector3D, TVector3D, float>::value &&
		is_vector_3D<TVector3D>::value
	> * = nullptr
>
TVector3D operator*(const TVector3D & lhs, float rhs)
{
	return make_vec3D<TVector3D>(x(lhs) * rhs, y(lhs) * rhs, z(lhs) * rhs);
}


template<typename TVector4D,
	std::enable_if_t
	<
		!has_operator_mult<TVector4D, TVector4D, float>::value &&
		is_vector_4D<TVector4D>::value
	> * = nullptr
>
TVector4D operator*(const TVector4D & lhs, float rhs)
{
	return make_vec4D<TVector4D>(x(lhs) * rhs, y(lhs) * rhs, z(lhs) * rhs, w(lhs) * rhs);
}


template<typename TVector3D,
	std::enable_if_t
	<
		!has_operator_mult<float, TVector3D, TVector3D>::value &&
		is_vector_3D<TVector3D>::value
	> * = nullptr
>
TVector3D operator*(float lhs, const TVector3D & rhs)
{
	return rhs * lhs;
}


template<typename TVector4D,
	std::enable_if_t
	<
		!has_operator_mult<float, TVector4D, TVector4D>::value &&
		is_vector_4D<TVector4D>::value
	> * = nullptr
>
TVector4D operator*(float lhs, const TVector4D & rhs)
{
	return rhs * lhs;
}


template<typename TVector3D,
	std::enable_if_t
	<
		!has_operator_div<TVector3D, TVector3D, float>::value &&
		is_vector_3D<TVector3D>::value
	> * = nullptr
>
TVector3D operator/(const TVector3D & lhs, float rhs)
{
	return lhs * (1.f / rhs);
}


template<typename TVector4D,
	std::enable_if_t
	<
		!has_operator_div<TVector4D, TVector4D, float>::value &&
		is_vector_4D<TVector4D>::value
	> * = nullptr
>
TVector4D operator/(const TVector4D & lhs, float rhs)
{
	return lhs * (1.f / rhs);
}


template<typename TVector3D,
	std::enable_if_t
	<
		!has_operator_out<TVector3D, std::ostream, TVector3D>::value &&
		is_vector_3D<TVector3D>::value
	> * = nullptr
>
std::ostream & operator<<(std::ostream & os, const TVector3D & v)
{
	return os << "(" << x(v) << ", " << y(v) << ", " << z(v) << ")";
}


template<typename TVector4D,
	std::enable_if_t
	<
		!has_operator_out<TVector4D, std::ostream, TVector4D>::value &&
		is_vector_4D<TVector4D>::value
	> * = nullptr
>
std::ostream & operator<<(std::ostream & os, const TVector4D & v)
{
	return os << "(" << x(v) << ", " << y(v) << ", " << z(v) << ", " << w(v) << ")";
}


template<typename TVector3D,
	std::enable_if_t
	<
		!has_function_norm<float(TVector3D)>::value &&
		is_vector_3D<TVector3D>::value
	> * = nullptr
>
float norm(const TVector3D & v)
{
	return sqrtf(x(v) * x(v) + y(v) * y(v) + z(v) * z(v));
}


template<typename TVector4D,
	std::enable_if_t
	<
		!has_function_norm<float(TVector4D)>::value &&
		is_vector_4D<TVector4D>::value
	> * = nullptr
>
float norm(const TVector4D & v)
{
	return sqrtf(x(v) * x(v) + y(v) * y(v) + z(v) * z(v) + w(v) * w(v));
}


template<typename TVector3D,
	std::enable_if_t
	<
		!has_function_normalize<TVector3D(TVector3D)>::value &&
		is_vector_3D<TVector3D>::value
	> * = nullptr
>
TVector3D normalize(const TVector3D & v)
{
	return v / norm(v);
}


template<typename TVector4D,
	std::enable_if_t
	<
		!has_function_normalize<TVector4D(TVector4D)>::value &&
		is_vector_4D<TVector4D>::value
	> * = nullptr
>
TVector4D normalize(const TVector4D & v)
{
	return v / norm(v);
}


template<typename TVector3D,
	std::enable_if_t
	<
		is_vector_3D<TVector3D>::value
	> * = nullptr
>
float innerProduct(const TVector3D & lhs, const TVector3D & rhs)
{
	return x(lhs) * x(rhs) + y(lhs) * y(rhs) + z(lhs) * z(rhs);
}


template<typename TVector4D,
	std::enable_if_t
	<
		is_vector_4D<TVector4D>::value
	> * = nullptr
>
float innerProduct(const TVector4D & lhs, const TVector4D & rhs)
{
	return x(lhs) * x(rhs) + y(lhs) * y(rhs) + z(lhs) * z(rhs) + w(lhs) * w(rhs);
}


template<typename TVector3D, typename TVector4D>
TVector4D hesseFromPointAndNormal(const TVector3D & point, const TVector3D & normal)
{
	const TVector3D normalizedNormal = normalize(normal);
	return make_vec4D<TVector4D>(
		x(normalizedNormal),
		y(normalizedNormal),
		z(normalizedNormal),
		innerProduct(normalizedNormal, point)
	);
}


template<typename TVector3D>
static float intersectLineAndPlane(
	TVector3D * intersectionPoint, 
	const TVector3D & linePoint, const TVector3D & lineDir, 
	const TVector3D & planeNormal, float planeDist)
{
	const TVector3D planeNormalNormalized = normalize(planeNormal);

	const float a = innerProduct(planeNormalNormalized, linePoint);
	const float b = innerProduct(planeNormalNormalized, lineDir);

	const float scal = (planeDist - a) / b;
	(*intersectionPoint) = linePoint + scal * lineDir;

	return scal;
}


template<typename TVector3D>
static float intersectLineAndLine(TVector3D * closestPoint, 
	const TVector3D & p1, const TVector3D & dir1,
	const TVector3D & p2, const TVector3D & dir2,
	float * outl1 = nullptr, float * outl2 = nullptr)
{
	const TVector3D v1 = normalize(dir1);
	const TVector3D	v2 = normalize(dir2);

	float a = innerProduct(v1, v2);
	a = 1/(a * a - 1);

	const TVector3D dp = p2 - p1;

	const TVector3D temp1 = innerProduct<TVector3D>(dp, v1) * v1;
	const TVector3D temp2 = dp - temp1;
	const float b = innerProduct<TVector3D>(temp2, v2);

	const float l2 = a * b;
	const float l1 = innerProduct<TVector3D>(dp + l2 * v2, v1);

	if (outl1)
		*outl1 = l1;
	if (outl2)
		*outl2 = l2;

	*closestPoint = 0.5 * (p1 + l1 * v1 + p2 + l2 * v2);

	return norm(static_cast<TVector3D>(p1 + l1 * v1 - (p2 + l2 * v2)));
}