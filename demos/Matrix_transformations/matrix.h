#ifndef MATRIX_H
#define MATRIX_H

void initialMatrix(float matrix[3][3]);

void printMatrix(float matrix[3][3]);

void multiplyMatrixes(float matrix[3][3], float matrixB[3][3], float matrixC[3][3]);

void matrix_x_Vectors(float number1,float number2, float vector[3], float matrix[3][3]);

#endif