#pragma once

#include <iostream>
#include <fstream>

#include "Roi3DF.h"
#include "Roi3DF_geometricFunctions.h"


template<typename TVector3D, typename TVector4D>
void roid3df_test()
{
	using std::cout;
	using std::endl;
	using std::boolalpha;

	Roi3DF roi1{ 0, 0, 0, 10, 10, 10 };

	TVector3D start = make_vec3D<TVector3D>(5, 5, 5);
	TVector3D end = make_vec3D<TVector3D>(20, 20, 20);
	Roi3DF roi2( start, end );

	cout << "Roi 1: " << roi1 << endl;
	cout << "Roi 2: " << roi2 << endl << endl;
	
	cout << "Center Roi 1: " << roi1.center<TVector3D>() << endl;
	cout << "Center Roi 2: " << roi2.center<TVector3D>() << endl << endl;
	
	cout << "Roi 1 contains its center? -> " << boolalpha << roi1.contains(roi1.center<TVector3D>()) << endl;
	cout << "Roi 2 contains its center? -> " << boolalpha << roi2.contains(roi2.center<TVector3D>()) << endl << endl;

	TVector3D outsideRoi1 = make_vec3D<TVector3D>(0, 0, 50);
	TVector3D outsideRoi2 = make_vec3D<TVector3D>(4.9999F, 4.9999F, 4.9999F);
	cout << "Roi 1 contains " << outsideRoi1 << "? -> " << boolalpha << roi1.contains(0, 0, 50) << endl;
	cout << "Roi 2 contains " << start << "? -> " << boolalpha << roi2.contains(start) << endl;
	cout << "Roi 2 contains " << outsideRoi2 << "? -> " << boolalpha << roi2.contains(outsideRoi2) << endl << endl;

	cout << "Roi 1 size: " << roi1.size<TVector3D>() << endl;
	cout << "Roi 2 size: " << roi2.size<TVector3D>() << endl << endl;

	Roi3DF roi1_copy = roi1;
	cout << "Roi 1 == Roi 2 ? -> " << boolalpha << (roi1 == roi2) << " (" << !(roi1 != roi2) << ")" << endl;
	cout << "Roi 1 == Roi 1 Copy ? -> " << boolalpha << (roi1 == roi1_copy) << " (" << !(roi1 != roi1_copy) << ")" << endl << endl;

	Roi3DF intersection(roi1);
	intersection.intersect(roi2);

	Roi3DF unity(roi1);
	unity.unite(roi2);

	Roi3DF enlarged(roi1);
	enlarged.enlarge(2);

	cout << "Intersection Roi 1 - Roi 2: " << intersection << endl;
	cout << "Uniting Roi 1 - Roi 2: " << unity << endl;
	cout << "Roi 1 enlarged by 2: " << enlarged << endl << endl;

	const auto corners = roi1.getCorners<TVector3D>();

	cout << "Corners: [" << endl;
	for(const auto & p : corners)
	{
		cout << "\t" << p << endl;
	}
	cout << "]" << endl << endl;

	TVector3D linePoint1 = make_vec3D<TVector3D>(0, 15, 15);
	TVector3D linePoint2 = make_vec3D<TVector3D>(0, 15, 50);
	TVector3D lineDir = make_vec3D<TVector3D>(1, 0, 0);

	cout << "Roi 2 interstects " << linePoint1 << " -> " << lineDir << "? -> ";
	cout << boolalpha << intersects<TVector3D, TVector4D>(roi2, linePoint1, lineDir) << endl;

	cout << "Roi 2 interstects " << linePoint2 << " -> " << lineDir << "? -> ";
	cout << boolalpha << intersects<TVector3D, TVector4D>(roi2, linePoint2, lineDir) << endl;

	cout << "Roi 2 interstects in plane " << linePoint2 << " -> " << lineDir << "? -> ";
	cout << boolalpha << intersectsInPlane<TVector3D, TVector4D>(roi2, linePoint2, lineDir) << endl << endl;

	std::ofstream("roi1.txt") << roi1;
	Roi3DF loaded;
	std::ifstream("roi1.txt") >> loaded;

	cout << "Roi Serialization: " << endl;
	cout << boolalpha << (roi1 == loaded) << endl << endl;
	
}