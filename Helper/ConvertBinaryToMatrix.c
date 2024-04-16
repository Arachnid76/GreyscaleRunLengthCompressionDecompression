#include <stdio.h>
#include <stdlib.h>

int main() {
    // Open the binary file
    FILE *fp = fopen("./Binary/matrix.bin", "rb");
    if (fp == NULL) {
        printf("Error opening binary file\n");
        return 1;
    }

    // Read the dimensions of the matrix from the file header
    int rows, cols;
    if (fread(&rows, sizeof(int), 1, fp) != 1 || fread(&cols, sizeof(int), 1, fp) != 1) {
        printf("Error reading binary file header\n");
        fclose(fp);
        return 1;
    }

    // Allocate memory for the matrix
    float **matrix = (float **)malloc(rows * sizeof(float *));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (float *)malloc(cols * sizeof(float));
    }

    // Read the matrix data from the binary file
    for (int i = 0; i < rows; i++) {
        if (fread(matrix[i], sizeof(float), cols, fp) != (size_t)cols) {
            printf("Error reading binary file data\n");
            for (int j = 0; j < i; j++) {
                free(matrix[j]);
            }
            free(matrix);
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);

    // Print the matrix
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%f ", matrix[i][j]);
        }
        printf("\n");
    }

    // Free the memory allocated for the matrix
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}