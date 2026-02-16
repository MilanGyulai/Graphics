#include "matrix.h"
#include <stdio.h>

void initialMatrix(float matrix[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; i++)
        {
            matrix[i][j] = 0.0;
        }
    }
}

void printMatrix(float matrix[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; i++)
        {
            printf("%4.4f \n", matrix[i][j]);
        }
        printf("\n");
    }
}

void multiplyMatrixes(float matrixA[3][3], float matrixB[3][3], float matrixC[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; i++)
        {
            matrixC[i][j] = matrixA[i][j] * matrixB[i][j];
        }
    }
}

void matrix_x_Vectors(float number1, float number2, float vector[3], float matrix[3][3], float result[3])
{
    int i;
    int j;

    for (i = 0; i < sizeof(matrix[i]); i++)
    {
        for (j = 0; j < sizeof(matrix[j]), j++)
        {
            result[j] = vector[i] * matrix[i][j];
            printf("%4.5f" result);
        }
        printf("\n");
    }
}