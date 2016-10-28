/*
 ============================================================================
 Name        : geometry.c
 Author      : David Katz
 Homework    : 1
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static int area_square(int length);
static int area_rectangle(int length, int width);
static int area_triangle(int base, int height);
static double area_circle(int radius);

int main(void) {
	printf("Hello! What shape would you like to calculate the area for?\n");

	printf("\t 1) square?\n");
	printf("\t 2) rectangle?\n");
	printf("\t 3) triangle?\n");
	printf("\t 4) circle?\n");
	printf("\t 5) quit the program.\n");

	printf("Enter your the number of your choice: ");
	int choice;
	scanf("%d", &choice);
	int area;

	while (choice != 5) {
		if (choice == 1) {
			printf("What is the side length of your square: ");
			int side;
			scanf("\n%d", &side);
			area = area_square(side);
			printf("The area of your square is %d units.", area);
		}

		if (choice == 2) {
			printf("What is the length of your rectangle: ");
			int length;
			scanf("\n%d", &length);
			printf("What is the width of your rectangle: ");
			int width;
			scanf("\n%d", &width);
			area = area_rectangle(length, width);
			printf("The area of your rectangle is %d units.", area);
		}

		if (choice == 3) {
			printf("What is the base of your triangle: ");
			int base;
			scanf("\n%d", &base);
			printf("What is the height of your triangle: ");
			int height;
			scanf("\n%d", &height);
			area = area_triangle(base, height);
			printf("The area of your triangle is %d units.", area);
		}

		if (choice == 4) {
			printf("What is radius of your circle: ");
			int radius;
			scanf("\n%d", &radius);
			double area = area_circle(radius);
			printf("The area of your circle is %f units.", area);
		}
		printf("\n\nAnother one! Enter your the number of your choice: ");
		scanf("%d", &choice);
	}

	printf("Exited the program");
	return EXIT_SUCCESS;
}

// returns the area of a square
static int area_square(int length) {
	return length*length;
}

// returns the area of a rectangle
static int area_rectangle(int length, int width) {
	return length*width;
}

//returns the area of a triangle
static int area_triangle(int base, int height) {
	return (base*height)/2;
}

//returns the area of a circle
static double area_circle(int radius) {
	double pi = 4.0 * atan(1.0);
	return pi*(radius*radius);
}
