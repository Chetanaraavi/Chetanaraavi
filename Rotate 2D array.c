#include <stdio.h>

void rotateMatrix(int n, int mat[n][n]) {
    for (int i = 0; i < n / 2; i++) {
        for (int j = i; j < n - i - 1; j++) {
            int temp = mat[i][j];
            mat[i][j] = mat[n - j - 1][i];
            mat[n - j - 1][i] = mat[n - i - 1][n - j - 1];
            mat[n - i - 1][n - j - 1] = mat[j][n - i - 1];
            mat[j][n - i - 1] = temp;
        }
    }
}

void printMatrix(int n, int mat[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n = 4; // Change this to the desired size of the matrix
    int mat[4][4] = {{1, 2, 3, 4},
                    {5, 6, 7, 8},
                    {9, 10, 11, 12},
                    {13, 14, 15, 16}};

    printf("Original Matrix:\n");
    printMatrix(n, mat);

    rotateMatrix(n, mat);

    printf("\nMatrix after rotation:\n");
    printMatrix(n, mat);

    return 0;
}
