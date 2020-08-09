#include <iostream>
#include "fstream"
#include <string>
#include <iomanip>

using namespace std;

// generator
int main(int argc, char **argv)
{
    //get arguments
    int seed = atoi(argv[1]);
    int nr1 = atoi(argv[2]);
    int nc1 = atoi(argv[3]);
    int nr2 = atoi(argv[4]);
    int nc2 = atoi(argv[5]);
    string output_filename = argv[6];

    //randon number seed
    srand(seed);

    //metrix declaration
    double *m1 = new double[nr1 * nc1];
    double *m2 = new double[nr2 * nc2];

    for (int i = 0; i < nr1; i++)
    {
        for (int j = 0; j < nc1; j++)
        {
            m1[i * nc1 + j] = (double)rand() / RAND_MAX;
        }
    }

    for (int i = 0; i < nr2; i++)
    {
        for (int j = 0; j < nc2; j++)
        {
            m2[i * nc2 + j] = (double)rand() / RAND_MAX;
        }
    }
    //output file
    ofstream fileOutput;
    fileOutput.open(output_filename, ios::out);

    if (!fileOutput.is_open())
    {
        cout << "sth wrong!!" << endl;
    }
    else
    {
        fileOutput << nr1 << " " << nc1 << " " << nr2 << " " << nc2 << endl;

        for (int i = 0; i < nr1; i++)
        {
            for (int j = 0; j < nc1; j++)
            {
                fileOutput << fixed << setprecision(1) << m1[i * nc1 + j] << "\t";
            }
            fileOutput << endl;
        }

        for (int i = 0; i < nr2; i++)
        {
            for (int j = 0; j < nc2; j++)
            {
                fileOutput << fixed << setprecision(1) << m2[i * nc2 + j] << "\t";
            }
            fileOutput << endl;
        }
    }
}
