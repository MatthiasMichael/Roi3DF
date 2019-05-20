#pragma once

#include "Roi3DF.h"

#include "vec_geometricOperations.h"

template<typename TVector3D, typename TVector4D>
FixedSizeVector<TVector4D, 6> getHesseNormalVectors(const Roi3DF & roi)
{
	FixedSizeVector<TVector4D, 6> hesseNormalVectors;
	for (int i = 0; i < 6; ++i)
	{
		TVector3D pointOnPlane;

		if (i < 3) // front, left, bottom
		{
			pointOnPlane = make_vec3D<TVector3D>(roi.x1, roi.y1, roi.z1);
		}
		else // back, top, right
		{
			pointOnPlane = make_vec3D<TVector3D>(roi.x2, roi.y2, roi.z2);
		}

		TVector3D normalVector;

		switch (i % 3)
		{
			case 0: normalVector = make_vec3D<TVector3D>(0, 1, 0); break; // front, back
			case 1: normalVector = make_vec3D<TVector3D>(1, 0, 0); break; // left, right
			case 2: normalVector = make_vec3D<TVector3D>(0, 0, 1); break; // top, bottom
			default: break;
		}

		hesseNormalVectors.push_back(hesseFromPointAndNormal<TVector3D, TVector4D>(pointOnPlane, normalVector));
	}
	return hesseNormalVectors;
}


template<typename TVector3D, typename TVector4D>
bool intersects(const Roi3DF & roi, const TVector3D & linePoint, const TVector3D & lineDir)
{
	const auto hesseNormalVectors = getHesseNormalVectors<TVector3D, TVector4D>(roi);
	for (const auto & v : hesseNormalVectors)
	{
		TVector3D intersectionPoint;
		intersectLineAndPlane(&intersectionPoint, linePoint, lineDir, make_vec3D<TVector3D>(x(v), y(v), z(v)), w(v));
		if (roi.contains(intersectionPoint))
		{
			return true;
		}
	}
	return false;
}


template<typename TVector3D, typename TVector4D>
bool intersectsInPlane(const Roi3DF & roi, const TVector3D & linePoint, const TVector3D & lineDir)
{
	FixedSizeVector<TVector3D, 4> linePoints, lineDirs;

	linePoints.push_back(make_vec3D<TVector3D>(roi.x1, roi.y1, 0));
	linePoints.push_back(make_vec3D<TVector3D>(roi.x1, roi.y1, 0));
	linePoints.push_back(make_vec3D<TVector3D>(roi.x2, roi.y2, 0));
	linePoints.push_back(make_vec3D<TVector3D>(roi.x2, roi.y2, 0));

	lineDirs.push_back(make_vec3D<TVector3D>(roi.x2 - roi.x1, roi.y1 - roi.y1, 0));
	lineDirs.push_back(make_vec3D<TVector3D>(roi.x1 - roi.x1, roi.y2 - roi.y1, 0));
	lineDirs.push_back(make_vec3D<TVector3D>(roi.x2 - roi.x2, roi.y1 - roi.y2, 0));
	lineDirs.push_back(make_vec3D<TVector3D>(roi.x1 - roi.x2, roi.y2 - roi.y2, 0));

	const TVector3D linePoint2D = make_vec3D<TVector3D>(x(linePoint), y(linePoint), 0.f);
	const TVector3D lineDir2D = make_vec3D<TVector3D>(x(lineDir), y(lineDir), 0.f);

	for (int i = 0; i < 4; ++i)
	{
		TVector3D closestPoint;
		float scalar1, scalar2;
		intersectLineAndLine(&closestPoint, linePoint2D, lineDir2D, linePoints[i], lineDirs[i], &scalar1, &scalar2);

		if (scalar2 >= 0 && scalar2 <= norm(lineDirs[i])) // scalar2 is for x = p2 + scala2 * (v2 / norm(v2))
		{
			return true;
		}
	}
	return false;
}