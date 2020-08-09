#include "../mmm.h"
#include <iostream>
#include "mkl.h"

using namespace std;

// v3
void mmm(const int nrA, const int ncA, const int nrB, const int ncB,
		 const double *a, const double *b, double *c)
{
	//m*m
	if (nrA > 1 && ncB > 1)
	{
		cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, nrA, ncB, ncA,
					1.0, a, ncA,
					b, ncB,
					0.0, c, ncB);
	}
	//v*v
	else if (nrA == 1 && ncB == 1)
	{
		c[0] = cblas_ddot(ncA, a, 1, b, 1);
	}
	//m*v
	else
	{
		cblas_dgemv(CblasRowMajor, CblasNoTrans, nrA, ncB,
					1.0, a, ncA, b, 1,
					0.0, c, 1);
	}
}
