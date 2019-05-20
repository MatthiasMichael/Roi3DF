#pragma once

#include <iostream>

#include "FixedSizeVector.h"

#include "cuda_host_device.h"
#include "vec_template.h"


// Temporary Workaround until we are migrating to a compiler that supports using aliases
template<typename TVector3D>
struct Corners
{
	enum : unsigned int{ NumPoints = 8 };
	typedef FixedSizeVector<TVector3D, 8> type;
};


// TODO: Consistency Check beim erstellen: x1 < x2 ...
struct Roi3DF
{
	// Init can't be done since we want to use Roi3DF in GPU const memory which does not support dynamic initialization
	_HOST_DEVICE_ Roi3DF() //: x1(0), y1(0), z1(0), x2(0), y2(0), z2(0)
	{
		// empty
	}

	_HOST_DEVICE_ Roi3DF( float x1, float y1, float z1, float x2, float y2, float z2 ) : 
		x1(x1), y1(y1), z1(z1), x2(x2), y2(y2), z2(z2)
	{
		// empty
	}

	template<typename TVector3D>
	_HOST_DEVICE_ Roi3DF(const TVector3D & start, const TVector3D & end) : 
		x1(x(start)), y1(y(start)), z1(z(start)), x2(x(end)), y2(y(end)), z2(z(end))
	{
		// empty
	}

	template<typename TVector3D> _HOST_DEVICE_ TVector3D start() const { return make_vec3D<TVector3D>(x1, y1, z1); }
	template<typename TVector3D> _HOST_DEVICE_ TVector3D end() const { return make_vec3D<TVector3D>(x2, y2, z2); }
	template<typename TVector3D> _HOST_DEVICE_ TVector3D size() const { return end<TVector3D>() - start<TVector3D>(); }
	template<typename TVector3D> _HOST_DEVICE_ TVector3D center() const
	{
		return make_vec3D<TVector3D>(x1 + 0.5f * (x2 - x1), y1 + 0.5f * (y2 - y1), z1 + 0.5f * (z2 - z1));
	}

	_HOST_DEVICE_ bool contains(double x, double y, double z) const;
	template<typename TVector3D> _HOST_DEVICE_ bool contains(const TVector3D & p) const { return contains(x(p), y(p), z(p)); }

	_HOST_DEVICE_ void unite(const Roi3DF & other);

	_HOST_DEVICE_ void intersect(const Roi3DF & other);

	_HOST_DEVICE_ void enlarge(float offset) { enlarge(offset, offset, offset); }
	_HOST_DEVICE_ void enlarge(float offsetX, float offsetY, float offsetZ);

	template<typename TVector3D> _HOST_DEVICE_ FixedSizeVector<TVector3D, 8> getCorners() const;

	static Roi3DF EmptyRoi;

	float x1, y1, z1;
	float x2, y2, z2;
};


_HOST_DEVICE_ bool operator==(const Roi3DF & left, const Roi3DF & right);
_HOST_DEVICE_ bool operator!=(const Roi3DF & left, const Roi3DF & right);

std::ostream & operator<<(std::ostream & os, const Roi3DF & roi);
std::istream & operator>>(std::istream & is, Roi3DF & roi);

template<typename TVector3D>
_HOST_DEVICE_ FixedSizeVector<TVector3D, 8> Roi3DF::getCorners() const
{
	FixedSizeVector<TVector3D, 8> corners;

	corners.push_back( make_vec3D<TVector3D>(x1, y1, z1) );
	corners.push_back( make_vec3D<TVector3D>(x1, y1, z2) );
	corners.push_back( make_vec3D<TVector3D>(x1, y2, z1) );
	corners.push_back( make_vec3D<TVector3D>(x1, y2, z2) );
	corners.push_back( make_vec3D<TVector3D>(x2, y1, z1) );
	corners.push_back( make_vec3D<TVector3D>(x2, y1, z2) );
	corners.push_back( make_vec3D<TVector3D>(x2, y2, z1) );
	corners.push_back( make_vec3D<TVector3D>(x2, y2, z2) );

	return corners;
}