#include <stdio.h>

typedef struct {
    int degree;
    float coef[101];
} polynomial;

polynomial add(polynomial a, polynomial b) {
    polynomial result;
    int i, max_degree;

    max_degree = (a.degree > b.degree)
                 ? a.degree : b.degree;

    result.degree = max_degree;

    for (i = 0; i <= max_degree; i++) {
        float ca = 0, cb = 0;

        if (i <= a.degree)
            ca = a.coef[a.degree - i];

        if (i <= b.degree)
            cb = b.coef[b.degree - i];

        result.coef[max_degree - i] = ca + cb;
    }

    return result;
}

void display(polynomial p) {
    int i, exponent, printed = 0;
    float c;

    for (i = 0; i <= p.degree; i++) {
        c = p.coef[i];
        exponent = p.degree - i;

        if (c == 0)
            continue;

        if (printed && c > 0)
            printf(" + ");
        else if (printed && c < 0)
            printf(" - ");
        else if (!printed && c < 0)
            printf("-");

        if (printed && c < 0)
            c = -c;
        else if (!printed && c < 0)
            c = -c;

        if (exponent == 0)
            printf("%.2g", c);
        else if (exponent == 1) {
            if (c == 1)
                printf("x");
            else
                printf("%.2gx", c);
        }
        else {
            if (c == 1)
                printf("x^%d", exponent);
            else
                printf("%.2gx^%d", c, exponent);
        }

        printed = 1;
    }

    if (!printed)
        printf("0");

    printf("\n");
}

void readPolynomial(polynomial *p) {
    int i;

    printf("Enter degree: ");
    scanf("%d", &p->degree);

    if (p->degree < 0 || p->degree > 100) {
        printf("Invalid degree.\n");
        p->degree = -1;
        return;
    }

    printf("Enter coefficients from highest degree to constant:\n");

    for (i = 0; i <= p->degree; i++)
        scanf("%f", &p->coef[i]);
}

int main() {
    polynomial a, b, result;

    printf("First polynomial\n");
    readPolynomial(&a);
    if (a.degree < 0)
        return 1;

    printf("Second polynomial\n");
    readPolynomial(&b);
    if (b.degree < 0)
        return 1;

    result = add(a, b);

    printf("Polynomial A: ");
    display(a);

    printf("Polynomial B: ");
    display(b);

    printf("Sum: ");
    display(result);

    return 0;
}
