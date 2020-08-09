#include <iostream>
#include <string>
#include "mmm.h"
#include "fstream"

#include "stopWatch.h"
#include <math.h>

using namespace std;

// implement your main program here..ZZ
int main(int argc, char **argv)
{

	string input_filename, output_filename;
	//command line arguments method
	if (argc > 1)
	{
		input_filename = argv[1];
		output_filename = argv[2];
	}
	else
	{
		//active-keyboard method
		cout << "\nPlease input the input filename: ";
		cin >> input_filename;
		cout << "\nPlease input the output filename: ";
		cin >> output_filename;
		cout << "\ninput file: " << input_filename << endl;
		cout << "\noutput file: " << output_filename << endl;
	}

	//Excetion Hendle-----------------------
	ifstream fileInput;
	fileInput.open(input_filename, ios::in);
	if (!fileInput.is_open())
	{
		cout << "sth wrong!!" << endl;
	}
	else
	{
		// cout << "haha sucessful!!" << endl;
	}
	//declaration and file input-----------
	int nrA;
	fileInput >> nrA;
	int ncA;
	fileInput >> ncA;
	int nrB;
	fileInput >> nrB;
	int ncB;
	fileInput >> ncB;

	double *a = new double[nrA * ncA];

	double *b = new double[nrB * ncB];

	double *c = new double[nrA * ncB];

	for (int i = 0; i < nrA; i++)
	{
		for (int j = 0; j < ncA; j++)
		{
			fileInput >> a[i * ncA + j];
			//cout << a[i*ncA + j] << " ";
		}
		//cout << endl;
	}

	for (int i = 0; i < nrB; i++)
	{
		for (int j = 0; j < ncB; j++)
		{
			fileInput >> b[i * ncB + j];
			//cout << b[i*ncB + j] << " ";
		}
		//cout << endl;
	}

	fileInput.close();
	//timer and function -----------------
	stopWatch timer;
	int count = 0;
	double t = 0;
	do
	{
		timer.start();
		mmm(nrA, ncA, nrB, ncB, a, b, c);
		timer.stop();
		t += timer.elapsedTime();
		count++;
	} while (t < 0.1);
	//output result ----------------------

	double nr1 = nrA;
	double nc1 = ncA;
	double nr2 = nrB;
	double nc2 = ncB;
	double mem_size = (sizeof(a) * nrA * ncA + sizeof(b) * nrB * ncB + sizeof(c) * nrA * ncB) / 1024.0;
	double sum = 0.0;
	for (int i = 0; i < nrA; i++)
	{
		for (int j = 0; j < ncB; j++)
		{
			sum += pow(c[i * ncB + j], 2);
		}
	}
	double norm = sqrt(sum);
	double secs = t / count;
	double flop = nrA * ncA * ncB * 2;
	double mem_r = nrA * ncA * ncB * 2;
	double mem_w = nrA * ncB;
	double mflops = flop / (secs * 1000000.0);
	double bw_r = mem_r * 8 / (secs * 1024 * 1024);
	double bw_w = mem_w * 8 / (secs * 1024 * 1024);

	// cout << "A[" << nr1 << "x" << nc1 << "] x B[" << nr2 << "x" << nc2 << "]" << endl;
	// cout << "Memory : " << mem_size << " (kilo-bytes)" << endl;
	// cout << "Norm : " << norm << endl;
	// cout << "Time used : " << secs << " (sec)" << endl;
	// cout << "flop : " << flop << endl;
	// cout << "mem_r : " << mem_r << "\tmem_w : " << mem_w << endl;
	// cout << mflops << " mflops/s" << endl;
	// cout << "memory bandwidth(reading) : " << bw_r << " (MB/s)" << endl;
	// cout << "memory bandwidth(write) : " << bw_w << " (MB/s)" << endl;

	cout << nr1 << ", " << nc1 << ", " << nr2 << ", " << nc2 << ", ";
	cout << mem_size << ", " << norm << ", " << secs << ", " << flop << ", ";
	cout << mem_r << ", " << mem_w << ", " << mflops << ", " << bw_r << ", " << bw_w << endl;
	ofstream fileOutput;
	fileOutput.open(output_filename, ios::out);

	if (!fileOutput.is_open())
	{
		cout << "sth wrong!!" << endl;
	}
	else
	{
		//number of floating-point operations, and number of memory references
		fileOutput << nr1 << ", " << nc1 << ", " << nr2 << ", " << nc2 << ", ";
		fileOutput << mem_size << ", " << norm << ", " << secs << ", " << flop << ", ";
		fileOutput << mem_r << ", " << mem_w << ", " << mflops << ", " << bw_r << ", " << bw_w << endl;
	}

	fileOutput.close();
	//-------------------------------------

	delete[] a;
	delete[] b;
	delete[] c;
	//-------------------------------------

	return 0;
}
