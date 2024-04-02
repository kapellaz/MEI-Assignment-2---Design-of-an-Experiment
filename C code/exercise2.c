/*
This C program is designed to manage employee data. It dynamically allocates memory for an array of employees, takes user input for each employee's ID, name, and salary, updates the salaries by increasing them by 10% (due to the intentional bug, this part won't work correctly), prints the employee details before and after the salary update, calculates and prints the average salary of all employees, and then frees the allocated memory.
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    float salary;
} Employee;

void updateSalary(Employee *employee, float percent) {
    // Bug: Missing division by 100
    employee->salary *= (1 + percent);  // Bug: Missing division by 100
    //employee->salary *= (1 + percent / 100);
}

void printEmployeeDetails(const Employee *employee) {
    printf("ID: %d\n", employee->id);
    printf("Name: %s\n", employee->name);
    printf("Salary: $%.2f\n", employee->salary);
}

float calculateAverageSalary(const Employee *employees, int count) {
    float totalSalary = 0;

    for (int i = 0; i < count; i++) {
        totalSalary += employees[i].salary;
    }

    return totalSalary / count;
}

int main() {
    int employeeCount;
    printf("Enter the number of employees: ");
    scanf("%d", &employeeCount);

    if (employeeCount <= 0) {
        printf("Please enter a positive number of employees.\n");
        return 1;
    }

    Employee *employees = (Employee *)malloc(sizeof(Employee) * employeeCount);

    if (!employees) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < employeeCount; i++) {
        printf("Enter details for employee %d:\n", i + 1);
        employees[i].id = i + 1;

        printf("Name: ");
        scanf("%s", employees[i].name);

        printf("Salary: $");
        scanf("%f", &employees[i].salary);

        printf("\n");
    }

    printf("Employee details before salary update:\n");
    for (int i = 0; i < employeeCount; i++) {
        printEmployeeDetails(&employees[i]);
    }

    // Update salaries
    for (int i = 0; i < employeeCount; i++) {
        updateSalary(&employees[i], 10.0);  // Bug: Missing division by 100
    }

    printf("\nEmployee details after salary update:\n");
    for (int i = 0; i < employeeCount; i++) {
        printEmployeeDetails(&employees[i]);
    }

    float averageSalary = calculateAverageSalary(employees, employeeCount);
    printf("\nAverage Salary: $%.2f\n", averageSalary);

    free(employees);

    return 0;
}