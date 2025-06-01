#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>

typedef struct employee
{
       char name[100];
       char title;
       double hours_worked;
       double payrate;
       double payment;

} Employee;

int main (void)
{
    int N=0;
    double sum=0,average=0,minimum=0,maximum=0;
    
    FILE *fptr;
    fptr = fopen("payroll.txt", "r");
    
    fscanf(fptr,"%d\n",&N);
    
    Employee* employee = (Employee*) malloc(N*sizeof(Employee));
    
    for (int count=0; count<N; count++)
    {
        fgets (employee[count].name, 100, fptr);
        fscanf (fptr,"%c\n", &employee[count].title);
        fscanf (fptr,"%lf\n", &employee[count].hours_worked);
        fscanf (fptr,"%lf\n", &employee[count].payrate);
        
    }

    fclose(fptr);

    for (int count=0; count <N; count++)
    {
        if (employee[count].title == 'M' && employee[count].hours_worked>80)
        {
            employee[count].payment = employee[count].payrate*(employee[count].hours_worked-80)*1.8+employee[count].payrate*80;
        }
        else if (employee[count].title == 'B' && employee[count].hours_worked>80)
        {
            employee[count].payment = employee[count].payrate*(employee[count].hours_worked-80)*1.5+employee[count].payrate*80;
        }
        else
        {
            employee[count].payment = employee[count].payrate*employee[count].hours_worked;
        }

        sum+= employee[count].payment;
    }

    /*for (int count=0; count<N; count++)
    {
        printf("Name: %s", employee[count].name);
        printf("Title: %c\n", employee[count].title);
        printf("Hours: %.2lf\n", employee[count].hours_worked);
        printf("Payrate: %.2lf\n", employee[count].payrate);
        printf("Payment: %.2lf\n\n",employee[count].payment);
    }*/

    minimum = sum; // set minimum to be a number greater than every other payment

     for (int count=0; count <N; count++)
    {
 

        if (employee[count].payment < minimum) 
        {
            minimum = employee[count].payment;
        }

        if (employee[count].payment > maximum) 
        {
            maximum = employee[count].payment;
        }

    }

    if (employee[N-1].payment < employee[0].payment && employee[N-1].payment < minimum) 
        {
            minimum = employee[N-1].payment;
        }

    if (employee[N-1].payment > employee[0].payment && employee[N-1].payment > maximum) 
        {
            maximum = employee[N-1].payment;
        }

    average = sum/N;

    FILE *wptr;
    wptr = fopen("Paid.txt", "w");

    fprintf(wptr,"Average: %.2lf\n",average);
    fprintf(wptr,"Maximum: %.2lf\n",maximum);
    fprintf(wptr,"Minimum: %.2lf\n",minimum);
    fprintf(wptr,"Sum: %.2lf\n",sum);

    fclose(wptr);

    free(employee);
    
    return 0;
}
