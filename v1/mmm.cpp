#include "../mmm.h"
#include <iostream>

using namespace std;

// v1
void mmm(const int nrA, const int ncA, const int nrB, const int ncB,
		 const double *a, const double *b, double *c)
{
	int i;
	int j;
	int k;

	for (i = 0; i < nrA; i++)
	{
		for (j = 0; j < ncB; j++)
		{
			for (k = 0; k < ncA; k++)
			{
				c[i * ncB + j] += a[i * ncA + k] * b[k * ncB + j];
			}
		}
	}
}
