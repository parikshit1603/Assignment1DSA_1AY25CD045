#include <stdio.h>

#define MAX 100
#define SIZE 20

typedef struct {
    int row, col, value;
} term;

void printTriples(term a[]) {
    int i;

    printf("Row\tColumn\tValue\n");

    for (i = 0; i <= a[0].value; i++)
        printf("%d\t%d\t%d\n",
               a[i].row, a[i].col, a[i].value);
}

void fast_transpose(term a[], term b[]) {
    int row_terms[SIZE] = {0};
    int starting_pos[SIZE] = {0};
    int position[SIZE];
    int i, j, num_cols, num_terms;

    num_cols = a[0].col;
    num_terms = a[0].value;

    b[0].row = a[0].col;
    b[0].col = a[0].row;
    b[0].value = num_terms;

    if (num_terms == 0)
        return;

    /* Count terms in each column of original matrix */
    for (i = 1; i <= num_terms; i++)
        row_terms[a[i].col]++;

    /* Calculate starting position of each transposed row */
    starting_pos[0] = 1;

    for (i = 1; i < num_cols; i++)
        starting_pos[i] =
            starting_pos[i - 1] + row_terms[i - 1];

    printf("\nrow_terms[]:\n");
    for (i = 0; i < num_cols; i++)
        printf("%d ", row_terms[i]);

    printf("\nstarting_pos[]:\n");
    for (i = 0; i < num_cols; i++)
        printf("%d ", starting_pos[i]);

    /* Copy starting positions so the original
       array remains available for display */
    for (i = 0; i < num_cols; i++)
        position[i] = starting_pos[i];

    /* Place each element directly in its final position */
    for (i = 1; i <= num_terms; i++) {
        j = position[a[i].col]++;

        b[j].row = a[i].col;
        b[j].col = a[i].row;
        b[j].value = a[i].value;
    }

    printf("\n");
}

int main() {
    int matrix[SIZE][SIZE];
    int rows, cols, i, j, count = 0;
    term a[MAX], b[MAX];

    printf("Enter number of rows and columns: ");
    scanf("%d %d", &rows, &cols);

    if (rows <= 0 || cols <= 0 ||
        rows > SIZE || cols > SIZE ||
        rows * cols >= MAX) {
        printf("Invalid matrix dimensions.\n");
        return 1;
    }

    printf("Enter matrix elements row by row:\n");

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            scanf("%d", &matrix[i][j]);

            if (matrix[i][j] != 0) {
                count++;
                if (count >= MAX) {
                    printf("Too many non-zero elements.\n");
                    return 1;
                }

                a[count].row = i;
                a[count].col = j;
                a[count].value = matrix[i][j];
            }
        }
    }

    a[0].row = rows;
    a[0].col = cols;
    a[0].value = count;

    printf("\nOriginal triples (header included):\n");
    printTriples(a);

    fast_transpose(a, b);

    printf("\nTransposed triples (header included):\n");
    printTriples(b);

    printf("\nTransposed triples are in row-major order.\n");

    return 0;
}
