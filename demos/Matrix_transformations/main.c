#include "matrix.h"

int main(int argc, char *argv[])
{

    float A[3][3] = {
        {1.0, 2.0, 3.0},
        {4.0, 5.0, 6.0},
        {7.0, 8.0, 9.0}};

    float B[3][3];

    initialMatrix(B);
    printMatrix(A);
    printMatrix(B);

    return 0;
}
