#include "Roi3DF.h"

#include "math.h"
#include <iomanip>


Roi3DF Roi3DF::EmptyRoi = Roi3DF(0, 0, 0, 0, 0, 0);


bool Roi3DF::contains(double x, double y, double z) const
{
	return 
		x >= x1 && x <= x2 &&
		y >= y1 && y <= y2 &&
		z >= z1 && z <= z2;
}


void Roi3DF::unite(const Roi3DF & other)
{
	// Unification with an empty roi should not change anything
	if(other == EmptyRoi)
	{
		return;
	}

	if(*this == EmptyRoi)
	{
		*this = other;
		return;
	}

	x1 = fmin(x1, other.x1);
	y1 = fmin(y1, other.y1);
	z1 = fmin(z1, other.z1);

	x2 = fmax(x2, other.x2);
	y2 = fmax(y2, other.y2);
	z2 = fmax(z2, other.z2);
}


void Roi3DF::intersect(const Roi3DF & other)
{
	// Interesection with an empty roi should always return an empty roi
	if (other == EmptyRoi)
	{
		*this = other;
		return;
	}

	if (*this == EmptyRoi)
	{
		return;
	}

	x1 = fmax(x1, other.x1);
	y1 = fmax(y1, other.y1);
	z1 = fmax(z1, other.z1);

	x2 = fmin(x2, other.x2);
	y2 = fmin(y2, other.y2);
	z2 = fmin(z2, other.z2);
}


void Roi3DF::enlarge(float offsetX, float offsetY, float offsetZ)
{
	x1 -= offsetX;
	y1 -= offsetY;
	z1 -= offsetZ;
	x2 += offsetX;
	y2 += offsetY;
	z2 += offsetZ;
}


bool operator==(const Roi3DF & left, const Roi3DF & right)
{
	return left.x1 == right.x1 &&
		left.y1 == right.y1 &&
		left.z1 == right.z1 &&
		left.x2 == right.x2 &&
		left.y2 == right.y2 &&
		left.z2 == right.z2;
}


bool operator!=(const Roi3DF & left, const Roi3DF & right)
{
	return !(left == right);
}


std::ostream & operator<<(std::ostream & os, const Roi3DF & roi)
{
	os << std::setprecision(std::numeric_limits<float>::max_digits10);
	os << "[ [" << roi.x1 << ", " << roi.y1 << ", " << roi.z1 << "], [" << roi.x2 << ", " << roi.y2 << ", " << roi.z2 << "] ]";
	return os;
}


std::istream & operator>>(std::istream & is, Roi3DF & roi) 
{
	is.ignore(1, '[');
	is.ignore(2, '[');
	is >> roi.x1;
	is.ignore(2, ' ');
	is >> roi.y1;
	is.ignore(2, ' ');
	is >> roi.z1;
	is.ignore(4, '[');
	is >> roi.x2;
	is.ignore(2, ' ');
	is >> roi.y2;
	is.ignore(2, ' ');
	is >> roi.z2;
	is.ignore(1, ']');
	is.ignore(2, ']');

	return is;
}
