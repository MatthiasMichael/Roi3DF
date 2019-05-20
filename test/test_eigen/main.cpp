#include "Roi3DF_eigen.h"
#include "Roi3DF_test.h"

int main(void)
{
	roid3df_test<Vector3f, Vector4f>();
	roid3df_test<Vector3d, Vector4d>();

	return 0;
}