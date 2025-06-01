//
//  main.c
//  Task2
//
//  Created by Ethan Kanyid on 9/16/23.
//


#include <stdio.h>

int main(void)
{
    
    double dbl = -49.14141;
    int j = 99;
    
    /* See if you can figure out what
    * the different printf statements below are doing
    * based on the output of the program.
    */
    
    /*printf("%lf\n", dbl);       //This line is printing double db1
    printf("%.10lf\n", dbl);    //This line is printing double db1 to 10 decimal places
    printf("%20lf\n", dbl);     //This line is printing double db1 in 20 character places
    printf("%d\n", j);          //This line is printing integer j
    printf("%10d\n", j);        //This line is printing integer j in 10 character places
    printf("%010d\n", j);       //This line is printing integer j in 10 character places with leading 0's*/
    
    
    
    FILE *fp;
    fp = fopen("task2.txt","w");

        fprintf(fp,"%lf\n", dbl);
        fprintf(fp,"%.10lf\n", dbl);
        fprintf(fp,"%20lf\n", dbl);
        fprintf(fp,"%d\n", j);
        fprintf(fp,"%10d\n", j);
        fprintf(fp,"%010d\n", j);
    
    fclose(fp);
    return 0;
}
