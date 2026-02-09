#include "rectangle.h"

#include <stdio.h>

int main(int argc, char* argv[])
{
	Rectangle rectangle;
	double area;

		set_rectangle_data(&rectangle, 5, 10);
		area = calc_rectangle_area(&rectangle);

		printf("Rectangle area: %lf\n", area);


/*
	float length, width, area;
	printf("Enter the length: \n");
	scanf("%f", &length);
	printf("Enter the width: \n");
	scanf("%f", &width);

	area = width * length;

	printf("The area of the rectangle is %.2f", area);*/

	return 0;
}
