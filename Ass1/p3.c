#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define PI acos(-1.0)


typedef struct {
    // To be completed
    double side_a;
    double side_b;
    double angle_ab;
} Triangle;

typedef struct {
    Triangle* triangles;
    int triangle_count;
} TriangleDictionary;

void addTriangle(TriangleDictionary* dict, double side1, double side2, double angle) {
    // To be completed
    if (fabs(angle-180) < 0.01)
    {
        return;
    }
    Triangle new_triangle;
    // order the sides
    double side3 = sqrt(side1 * side1 + side2 * side2 - 2 * side1 * side2 * cos(angle * PI / 180)); // c^2 = a^2 + b^2 - 2abcosC
    double side_a, side_b, side_c;
    double sides[3] = {side1, side2, side3};
    double temp;
    for (int i = 0; i < 2; i++)
    {
        for (int j = i; j < 3; j++)
        {
            // selective sort
            if (sides[i] > sides[j])
            {
                temp = sides[i];
                sides[i] = sides[j];
                sides[j] = temp;
            }
        }
    }
    side_a = sides[0];
    side_b = sides[1];
    side_c = sides[2];

    // check if the triangle is valid
    double e = 0.01;
    if (side_a + side_b <= side_c + e)
    {
        // printf("Invalid triangle!\n");
        return;
    }

    double angel = acos((side_a * side_a + side_b * side_b - side_c * side_c) / (2 * side_a * side_b)) * 180 / PI; // in degree
    new_triangle.side_a = side_a;
    new_triangle.side_b = side_b;
    new_triangle.angle_ab = angel;

    // add to dictictionary
    dict->triangle_count++;
    dict->triangles = (Triangle*)realloc(dict->triangles, dict->triangle_count * sizeof(Triangle)); // expand the array, add one more element after the last one
    dict->triangles[dict->triangle_count - 1] = new_triangle; // assign the new triangle to the last element(just added)


        
}

bool isSimilar(const Triangle* triangle, double side1, double side2, double side3) {
    // To be completed
    double side_a, side_b, side_c;
    double sides[3] = {side1, side2, side3};
    double temp;
    for (int i = 0; i < 2; i++)
    {
        for (int j = i; j < 3; j++)
        {
            // selective sort
            if (sides[i] > sides[j])
            {
                temp = sides[i];
                sides[i] = sides[j];
                sides[j] = temp;
            }
        }
    }
    side_a = sides[0];
    side_b = sides[1];
    side_c = sides[2];
    double angel = acos((side_a * side_a + side_b * side_b - side_c * side_c) / (2 * side_a * side_b)) * 180 / PI; // in degree

    //test
    // printf("--------------------------------\n");
    // printf("Comparing:\n");
    // printf("side-a: %.2f, side-b: %.2f, angel: %.2f\n", triangle->side_a, triangle->side_b, triangle->angle_ab);
    // printf("side-a: %.2f, side-b: %.2f, side-c: %.2f, angel: %.2f\n", side_a, side_b, side_c, angel);


    // compare the angel of two shortest sides, and the ratio of two shortest sides
    double e_angel = 0.01;
    double e_ratio = 0.01;
    if (fabs(triangle->angle_ab - angel) < e_angel && fabs(triangle->side_a / triangle->side_b - side_a / side_b) < e_ratio)
    {
        return true;
    }
    else
    {
        // printf("angle diff: %.5f, ratio diff: %.5f\n", fabs(triangle->angle_ab - angel), fabs(triangle->side_a / side_a - triangle->side_b / side_b));
        return false;
    }
    
    
}

bool searchSimilar(TriangleDictionary* dict, double side1, double side2, double angle) {
    double side3 = sqrt(side1 * side1 + side2 * side2 - 2 * side1 * side2 * cos(angle * PI / 180));

    for (int i = 0; i < dict->triangle_count; ++i) {
        if (isSimilar(&dict->triangles[i], side1, side2, side3)) {
            return true;
        }
    }
    return false;
}

int main() {
    int n;
    // printf("Enter the number of operations (n): ");
    scanf("%d", &n);

    char** actions = (char**)malloc(n * sizeof(char*));
    double** parameters = (double**)malloc(n * sizeof(double*));

    for (int i = 0; i < n; ++i) {
        actions[i] = (char*)malloc(15 * sizeof(char));
        parameters[i] = (double*)malloc(3 * sizeof(double));
    }

    for (int i = 0; i < n; ++i) {
        // printf("Enter operation #%d: ", i + 1);
        scanf("%s", actions[i]);
        if (strcmp(actions[i], "addTriangle") == 0 || strcmp(actions[i], "searchSimilar") == 0) {
            scanf("%lf %lf %lf", &parameters[i][0], &parameters[i][1], &parameters[i][2]);
        }
    }

    TriangleDictionary triangleDictionary;
    triangleDictionary.triangles = NULL;
    triangleDictionary.triangle_count = 0;

    for (int i = 0; i < n; ++i) {
        if (strcmp(actions[i], "TriangleDictionary") == 0) {
            // Do nothing
        } else if (strcmp(actions[i], "addTriangle") == 0) {
            addTriangle(&triangleDictionary, parameters[i][0], parameters[i][1], parameters[i][2]);
        } else if (strcmp(actions[i], "searchSimilar") == 0) {
            int result = searchSimilar(&triangleDictionary, parameters[i][0], parameters[i][1], parameters[i][2]);
            printf(result ? "true\n" : "false\n");
        }
    }
}
