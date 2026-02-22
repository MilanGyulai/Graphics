#include "matrix.h"
#include <stdio.h>
#include <math.h>

#define PI 3.14159265359

void initialMatrix(float matrix[3][3])
{
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            matrix[i][j] = 0.0;
        }
    }
}

// Egysegmatrix
void init_identity_matrix(float matrix[3][3])
{
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (i == j)
                matrix[i][j] = 1.0;
            else
                matrix[i][j] = 0.0;
        }
    }
}

void printMatrix(float matrix[3][3])
{
    int i, j;
    for (i = 0; i < 3; i++) {
        printf("[ ");
        for (j = 0; j < 3; j++) {
            printf("%4.2f ", matrix[i][j]);
        }
        printf("]\n");
    }
    printf("\n");
}

void multiply_scalar(float matrix[3][3], float scalar)
{
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            matrix[i][j] *= scalar;
        }
    }
}

// Matrix szorzas
void multiply_matrices(float matrixA[3][3], float matrixB[3][3], float matrixC[3][3])
{
    int i, j, k;

    initialMatrix(matrixC);

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            for (k = 0; k < 3; k++) {
                matrixC[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
}

void copy_matrix(float dest[3][3], float src[3][3]) {
    int i, j;
    for(i=0; i<3; i++) {
        for(j=0; j<3; j++) {
            dest[i][j] = src[i][j];
        }
    }
}

// Skalazas
void scale(float matrix[3][3], float sx, float sy)
{
    float s_matrix[3][3];
    float temp[3][3];

    init_identity_matrix(s_matrix);
    s_matrix[0][0] = sx;
    s_matrix[1][1] = sy;

    // Eredeti * Skalazo
    multiply_matrices(matrix, s_matrix, temp);
    copy_matrix(matrix, temp);
}

// Eltolas
void shift(float matrix[3][3], float tx, float ty)
{
    float t_matrix[3][3];
    float temp[3][3];

    init_identity_matrix(t_matrix);
    t_matrix[0][2] = tx; // 3. oszlopban van az eltolas
    t_matrix[1][2] = ty;

    multiply_matrices(matrix, t_matrix, temp);
    copy_matrix(matrix, temp);
}

// Forgatas
void rotate(float matrix[3][3], float angle)
{
    float r_matrix[3][3];
    float temp[3][3];
    float rad = angle * (PI / 180.0); // Fok radianban

    init_identity_matrix(r_matrix);
    r_matrix[0][0] = cos(rad);
    r_matrix[0][1] = -sin(rad);
    r_matrix[1][0] = sin(rad);
    r_matrix[1][1] = cos(rad);

    multiply_matrices(matrix, r_matrix, temp);
    copy_matrix(matrix, temp);
}

// Pont transzformalasa
void transform_point(float matrix[3][3], float point[3], float result[3])
{
    int i, j;
    for(i=0; i<3; i++) {
        result[i] = 0;
        for(j=0; j<3; j++) {
            result[i] += matrix[i][j] * point[j];
        }
    }
}