//
//
//  Homework#1 Task#1
//
//  Created by Ethan Kanyid on 9/16/23.
//

#include <stdio.h>
#define PI 3.141592653

int main(void)
{
    double radius, circumference, area;

    printf("Enter a radius: ");
    scanf("%lf", &radius);
    
    printf("The Area is %.3lf\n",area = PI * radius * radius);
    printf("The Circumference is %.3lf\n",circumference = 2 * PI * radius);
    
    
return 0;
}
