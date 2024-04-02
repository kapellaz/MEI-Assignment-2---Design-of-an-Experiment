/*
This C program is designed to manage employee data. It dynamically allocates memory for an array of employees, takes user input for each employee's ID, name, and salary, updates the salaries by increasing them by 10%, prints the employee details before and after the salary update, calculates and prints the average salary of all employees, and then frees the allocated memory.
 */
// Bugs can be of the following types:
// 1. Logical bug
// 2. Performance bug
// 3. Variable type bug
// 4. Memory managment bug
// 5. Documentation bug

// The review should take no longer than 10 minutes.
// Review starts on Line 24 and ends in line 116

#include <stdio.h>
#include <stdlib.h>

// define Struct
typedef struct {
    int id;
    char name[50];
    float salary;
} Employee;

// REVIEW STARTS HERE

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

    // print employees details
    printf("Employee details before salary update:\n");
    for (int i = 0; i < employeeCount; i++) {
        printEmployeeDetails(&employees[i]);
    }

    // Update salaries
    for (int i = 0; i < employeeCount; i++) {
        updateSalary(&employees[i], 10.0); 
    }

    // Print employees details
    printf("\nEmployee details after salary update:\n");
    for (int i = 0; i < employeeCount; i++) {
        printEmployeeDetails(&employees[i]);
    }

    // calculate the average salary for all employees
    float averageSalary = calculateAverageSalary(employees, employeeCount);
    printf("\nAverage Salary: $%.2f\n", averageSalary);

    free(employees);

    return 0;
}
/****************************************************************
* Function: Update salary
*
* Parameters: employe structure pointer and percent float
* Comments:  increase 10% in main
* Out: void
***************************************************************/
void updateSalary(Employee *employee, float percent) {
    employee->salary *= (1 + percent);
}
/****************************************************************
* Function: print employee details
*
* Parameters: employee structure pointer
* Out: void
***************************************************************/
void printEmployeeDetails(const Employee *employee) {
    printf("ID: %d\n", employee->id);
    printf("Name: %s\n", employee->name);
    printf("Salary: $%.2f\n", employee->salary);
}
/****************************************************************
* Function: calculate an average of the salary of all employees
*
* Parameters: pointer to the struct of employees; count variable
* Out: average salary
***************************************************************/
float calculateAverageSalary(const Employee *employees, int count) {
    float totalSalary = 0;

    for (int i = 0; i < count; i++) {
        totalSalary += employees[i].salary;
    }

    return totalSalary / count;
}
// REVIEW ENDS HERE
