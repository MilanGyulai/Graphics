#ifndef MATRIX_H
#define MATRIX_H

void initialMatrix(float matrix[3][3]);
void init_identity_matrix(float matrix[3][3]);
void printMatrix(float matrix[3][3]);

void multiply_scalar(float matrix[3][3], float scalar);
void multiply_matrices(float matrixA[3][3], float matrixB[3][3], float matrixC[3][3]);

void scale(float matrix[3][3], float sx, float sy);
void shift(float matrix[3][3], float tx, float ty);
void rotate(float matrix[3][3], float angle);

void transform_point(float matrix[3][3], float point[3], float result[3]);

#endif