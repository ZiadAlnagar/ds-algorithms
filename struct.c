#include <stdio.h>
#include <string.h>

void main() {
    struct employee
    {
        char Name[200];
        int SSN;
        float Salary;
    } emps[1000];

    int size = sizeof emps / sizeof emps[0];
    float Highest;
    char EmpName[200];
    int EmpCount;

    for (int i = 0; i < size; i++)
    {
        if (emps[i].Salary > emps[i - 1].Salary)
        {
            Highest = emps[i].Salary;
            EmpName = emps[i].Name;
        } 
    }

    for (int i = 0; i < size; i++)
    {
        if (emps[i].Salary < 5000.0)
        {
            Highest = emps[i].Salary;
            EmpCount++;
        }
    }
}

