#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <opencv2/opencv.hpp>

int main() {
    // Read the image data from the binary file
    FILE *fp = fopen("./Binary/OriginalImage.bin", "rb");
    if (fp == NULL) {
        printf("Error opening binary file\n");
        return 1;
    }

    // Get the dimensions of the image from the file header
    int height, width;
    if (fread(&height, sizeof(int), 1, fp) != 1 || fread(&width, sizeof(int), 1, fp) != 1) {
        printf("Error reading binary file header\n");
        fclose(fp);
        return 1;
    }

    // Allocate memory for the image data
    uint8_t *image_data = (uint8_t *)malloc(height * width * sizeof(uint8_t));

    // Read the image data from the binary file
    if (fread(image_data, sizeof(uint8_t), height * width, fp) != (size_t)(height * width)) {
        printf("Error reading binary file data\n");
        fclose(fp);
        free(image_data);
        return 1;
    }

    fclose(fp);

    // Reshape the image data into the original shape (assuming grayscale image)
    cv::Mat image(height, width, CV_8UC1, image_data);

    // Save the image
    cv::imwrite("./Resources/OriginalImage_reconstructed.jpg", image);

    printf("Image reconstructed as OriginalImage_reconstructed.jpg\n");

    free(image_data);
    return 0;
}