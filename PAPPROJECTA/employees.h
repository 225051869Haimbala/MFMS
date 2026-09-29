#ifndef EMPLOYEES_H
#define EMPLOYEES_H

#define MAX_EMPLOYEES 100
#define NAME_LEN 50
#define DEPT_LEN 30

typedef struct {
    char id[15];
    char name[NAME_LEN];
    char department[DEPT_LEN];
    double basic_salary;
    double housing_allowance;
    double transport_allowance;
    double gross_salary;
} Employee;

void employeeMenu(Employee employees[], int *count);
void addEmployee(Employee employees[], int *count);
void displayEmployees(const Employee employees[], int count);
void searchEmployee(const Employee employees[], int count);
double calculateGrossSalary(double basic, double housing, double transport);

#endif