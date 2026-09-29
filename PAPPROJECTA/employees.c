#include <stdio.h>
#include <string.h>
#include "employees.h"

double calculateGrossSalary(double basic, double housing, double transport) {
    return basic + housing + transport;
}

void employeeMenu(Employee employees[], int *count) {
    int choice;
    do {
        printf("\n===================================\n");
        printf("       EMPLOYEE MANAGEMENT         \n");
        printf("===================================\n");
        printf("1. Add Employee\n");
        printf("2. Display All Employees\n");
        printf("3. Search Employee\n");
        printf("4. Return to Main Menu\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }
        getchar();

        switch (choice) {
            case 1:
                addEmployee(employees, count);
                break;
            case 2:
                displayEmployees(employees, *count);
                break;
            case 3:
                searchEmployee(employees, *count);
                break;
            case 4:
                printf("Returning to main menu...\n");
                break;
            default:
                printf("Invalid selection! Please choose options 1-4.\n");
        }
    } while (choice != 4);
}

void addEmployee(Employee employees[], int *count) {
    if (*count >= MAX_EMPLOYEES) {
        printf("Error: System limit reached. Cannot add more employees.\n");
        return;
    }

    Employee emp;
    
    printf("\nEnter Employee ID: ");
    fgets(emp.id, sizeof(emp.id), stdin);
    emp.id[strcspn(emp.id, "\n")] = 0;

    printf("Enter Employee Name: ");
    fgets(emp.name, sizeof(emp.name), stdin);
    emp.name[strcspn(emp.name, "\n")] = 0;

    printf("Enter Department: ");
    fgets(emp.department, sizeof(emp.department), stdin);
    emp.department[strcspn(emp.department, "\n")] = 0;

    do {
        printf("Enter Basic Salary (N$): ");
        if (scanf("%lf", &emp.basic_salary) != 1 || emp.basic_salary < 0) {
            printf("Invalid salary! Please enter a non-negative number.\n");
            while (getchar() != '\n');
            emp.basic_salary = -1;
        }
    } while (emp.basic_salary < 0);

    do {
        printf("Enter Housing Allowance (N$): ");
        if (scanf("%lf", &emp.housing_allowance) != 1 || emp.housing_allowance < 0) {
            printf("Invalid allowance! Please enter a non-negative number.\n");
            while (getchar() != '\n');
            emp.housing_allowance = -1;
        }
    } while (emp.housing_allowance < 0);

    do {
        printf("Enter Transport Allowance (N$): ");
        if (scanf("%lf", &emp.transport_allowance) != 1 || emp.transport_allowance < 0) {
            printf("Invalid allowance! Please enter a non-negative number.\n");
            while (getchar() != '\n');
            emp.transport_allowance = -1;
        }
    } while (emp.transport_allowance < 0);
    getchar();

    emp.gross_salary = calculateGrossSalary(emp.basic_salary, emp.housing_allowance, emp.transport_allowance);

    employees[*count] = emp;
    (*count)++;

    printf("\nEmployee '%s' added successfully!\n", emp.name);
}

void displayEmployees(const Employee employees[], int count) {
    if (count == 0) {
        printf("\nNo employee records found.\n");
        return;
    }

    printf("\n%-10s %-20s %-15s %-12s %-12s\n", "ID", "Name", "Department", "Basic (N$)", "Gross (N$)");
    printf("----------------------------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-10s %-20s %-15s %-12.2f %-12.2f\n", 
               employees[i].id, 
               employees[i].name, 
               employees[i].department, 
               employees[i].basic_salary, 
               employees[i].gross_salary);
    }
}

void searchEmployee(const Employee employees[], int count) {
    if (count == 0) {
        printf("\nNo employee records available to search.\n");
        return;
    }

    char search_id[15];
    printf("\nEnter Employee ID to search: ");
    fgets(search_id, sizeof(search_id), stdin);
    search_id[strcspn(search_id, "\n")] = 0;

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(employees[i].id, search_id) == 0) {
            printf("\n--- Employee Details Found --- \n");
            printf("ID:                  %s\n", employees[i].id);
            printf("Name:                %s\n", employees[i].name);
            printf("Department:          %s\n", employees[i].department);
            printf("Basic Salary:        N$%.2f\n", employees[i].basic_salary);
            printf("Housing Allowance:   N$%.2f\n", employees[i].housing_allowance);
            printf("Transport Allowance: N$%.2f\n", employees[i].transport_allowance);
            printf("Gross Salary:        N$%.2f\n", employees[i].gross_salary);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nEmployee with ID '%s' was not found.\n", search_id);
    }
}