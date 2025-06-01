#include <stdio.h>

typedef struct employee
{
       char name[100];      // employee's name - last, first
       char title;          // title 'B' or 'M'
       double hours_worked; // total number of hours worked
       double payrate;      // pay rate per hour
       double payment;      // total payment for the pay period – you will compute!

} Employee;

Employee employee[];

int main (void)
{
    FILE *fptr;
    fptr = fopen("payroll.txt", "r");
    char c;
    for (int count=0; count <=3; count++)
    {
        
        fscanf (fptr,"%[^,\n]s", employee[count].name);
        fscanf (fptr,"%[^,\n]c", &employee[count].title);
        fscanf (fptr,"%[^,\n]lf", &employee[count].hours_worked);
        fscanf (fptr,"%[^,\n]lf", &employee[count].payrate);
        
    }

    fclose(fptr);
    
    for (int count=0; count <=3; count++)
    {
        
        printf("Name: %s\n", employee[count].name);
        printf("Title: %c\n", employee[count].title);
        printf("Hours: %.2lf\n", employee[count].hours_worked);
        printf("Payrate: %.2lf\n", employee[count].payrate);
        printf("Payment: %.2lf\n\n",employee[count].payrate*employee[count].hours_worked);
    }

    
    return 0;
}
