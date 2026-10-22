#include <stdio.h>
#include <stdlib.h>

typedef enum {
    FULL_TIME, CONTRACT
} EmployeeType;

typedef struct {
    char name[20];
    int emp_id;
    EmployeeType type;

    union {
        float salary;
        struct {
            float hourly_rate;
            int hours_worked;
        } contract_info;
    } pay;

} Employee;

int main() {
    Employee *e;
    int n, i;
    float total_bill = 0, amount;

    printf("Enter number of employees: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid number of employees.\n");
        return 1;
    }

    e = malloc(n * sizeof(Employee));

    if (e == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (i = 0; i < n; i++) {
        printf("\nEnter employee name and ID: ");
        scanf("%19s %d", (e + i)->name,
              &(e + i)->emp_id);

        printf("Enter type (0=Full-time, 1=Contract): ");
        scanf("%d", (int *)&(e + i)->type);

        if ((e + i)->type == FULL_TIME) {
            printf("Enter monthly salary: ");
            scanf("%f", &(e + i)->pay.salary);
        }
        else if ((e + i)->type == CONTRACT) {
            printf("Enter hourly rate and hours worked: ");
            scanf("%f %d",
                &(e + i)->pay.contract_info.hourly_rate,
                &(e + i)->pay.contract_info.hours_worked);
        }
        else {
            printf("Invalid employee type.\n");
            free(e);
            return 1;
        }
    }

    printf("\n--- EMPLOYEE PAYSLIPS ---\n");

    for (i = 0; i < n; i++) {
        if ((e + i)->type == FULL_TIME) {
            amount = (e + i)->pay.salary;
        }
        else {
            amount =
                (e + i)->pay.contract_info.hourly_rate *
                (e + i)->pay.contract_info.hours_worked;
        }

        printf("\nEmployee: %s\n", (e + i)->name);
        printf("Employee ID: %d\n", (e + i)->emp_id);
        printf("Total Pay: %.2f\n", amount);

        total_bill += amount;
    }

    printf("\nTotal salary bill: %.2f\n", total_bill);

    free(e);
    return 0;
}
