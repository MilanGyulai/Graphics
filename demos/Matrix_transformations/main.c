#include "matrix.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    float m[3][3];
    float point[3] = {10.0, 10.0, 1.0}; // Homogen koord (x, y, 1)
    float transformed_point[3];

    // Egysegmatrix inicializalas
    printf("1. Egysegmatrix:\n");
    init_identity_matrix(m);
    printMatrix(m);

    // Skalazas (2x nagyitas)
    printf("2. Skalazas (2.0, 2.0):\n");
    scale(m, 2.0, 2.0);
    printMatrix(m);

    // Forgatas (90 fok)
    printf("3. Forgatas (90 fok):\n");
    rotate(m, 90.0);
    printMatrix(m);

    // Eltolas (5, 5)
    printf("4. Eltolas (x=5, y=5):\n");
    shift(m, 5.0, 5.0);
    printMatrix(m);

    // Pont transzformacioja
    printf("5. Pont transzformalasa az aktualis matrixszal:\n");
    printf("Eredeti pont: x=%.2f, y=%.2f\n", point[0], point[1]);

    transform_point(m, point, transformed_point);

    printf("Transzformalt pont: x=%.2f, y=%.2f\n", transformed_point[0], transformed_point[1]);

    return 0;
}