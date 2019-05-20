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


int main(void)
{
	roid3df_test<MyVector3D, MyVector4D>();

	return 0;
}