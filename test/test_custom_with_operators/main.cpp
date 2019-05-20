#include <iostream>

#include "vec_template.h"
#include "Roi3DF_test.h"


// The following lines illustrate what you need to define yourself so that
// a vector type can be used in all projects that rely on the VectorTypes "library"

struct MyVector3D { float dim1, dim2, dim3; };
struct MyVector4D { float dim1, dim2, dim3, dim4; };

template<> float x(const MyVector3D & v) { return v.dim1; }
template<> float y(const MyVector3D & v) { return v.dim2; }
template<> float z(const MyVector3D & v) { return v.dim3; }

template<> float x(const MyVector4D & v) { return v.dim1; }
template<> float y(const MyVector4D & v) { return v.dim2; }
template<> float z(const MyVector4D & v) { return v.dim3; }
template<> float w(const MyVector4D & v) { return v.dim4; }

template<> MyVector3D make_vec3D(float x, float y, float z)
{
	return MyVector3D{ x, y, z };
}

template<> MyVector4D make_vec4D(float x, float y, float z, float w)
{
	return MyVector4D{ x, y, z, w };
}

template<>
struct is_vector_3D<MyVector3D>
{
	using type = std::true_type;
	static constexpr bool value = true;
};

template<>
struct is_vector_4D<MyVector4D>
{
	using type = std::true_type;
	static constexpr bool value = true;
};

MyVector3D operator+(const MyVector3D & lhs, const MyVector3D & rhs)
{
	return make_vec3D<MyVector3D>(x(lhs) + x(rhs), y(lhs) + y(rhs), z(lhs) + z(rhs));
}

MyVector4D operator+(const MyVector4D & lhs, const MyVector4D & rhs)
{
	return make_vec4D<MyVector4D>(x(lhs) + x(rhs), y(lhs) + y(rhs), z(lhs) + z(rhs), w(lhs) + w(rhs));
}

MyVector3D operator-(const MyVector3D & lhs, const MyVector3D & rhs)
{
	return make_vec3D<MyVector3D>(x(lhs) - x(rhs), y(lhs) - y(rhs), z(lhs) - z(rhs));
}

MyVector4D operator-(const MyVector4D & lhs, const MyVector4D & rhs)
{
	return make_vec4D<MyVector4D>(x(lhs) - x(rhs), y(lhs) - y(rhs), z(lhs) - z(rhs), w(lhs) - w(rhs));
}

MyVector3D operator*(const MyVector3D & lhs, float rhs)
{
	return make_vec3D<MyVector3D>(x(lhs) * rhs, y(lhs) * rhs, z(lhs) * rhs);
}

MyVector4D operator*(const MyVector4D & lhs, float rhs)
{
	return make_vec4D<MyVector4D>(x(lhs) * rhs, y(lhs) * rhs, z(lhs) * rhs, w(lhs) * rhs);
}

MyVector3D operator*(float lhs, const MyVector3D & rhs)
{
	return rhs * lhs;
}

MyVector4D operator*(float lhs, const MyVector4D & rhs)
{
	return rhs * lhs;
}

MyVector3D operator/(const MyVector3D & lhs, float rhs)
{
	return lhs * (1.f / rhs);
}

MyVector4D operator/(const MyVector4D & lhs, float rhs)
{
	return lhs * (1.f / rhs);
}

std::ostream & operator<<(std::ostream & os, const MyVector3D & v)
{
	return os << "[" << v.dim1 << ", " << v.dim2 << ", " << v.dim3 << "]";
}

std::ostream & operator<<(std::ostream & os, const MyVector4D & v)
{
	return os << "[" << v.dim1 << ", " << v.dim2 << ", " << v.dim3 << ", " << v.dim4 << "]";
}


int main(void)
{
	roid3df_test<MyVector3D, MyVector4D>();

	return 0;
}