#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define STEPS 1000
#define REPEATS 1000

int main() {
    int i, j;
    int x, y;
    double displacement, total = 0.0;

    FILE *fp = fopen("random_walk.dat", "w");
    if (fp == NULL) {
        printf("File error\n");
        return 1;
    }

    srand(time(NULL));

    fprintf(fp, "#Trial FinalX FinalY Displacement\n");

    for (i = 0; i < REPEATS; i++) {
        x = 0;
        y = 0;

        for (j = 0; j < STEPS; j++) {
            int d = rand() % 4;
            if (d == 0) x++;
            else if (d == 1) x--;
            else if (d == 2) y++;
            else y--;
        }

        displacement = sqrt(x*x + y*y);
        total += displacement;

        fprintf(fp, "%d %d %d %.2f\n", i+1, x, y, displacement);
    }

    fclose(fp);

    printf("Average displacement = %.2f\n", total / REPEATS);
    printf("Data saved to random_walk.dat\n");

    return 0;
}
