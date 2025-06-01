#include <stdio.h>
#include <math.h>
int main()
{

    double Power=0,Voltage=0,Resistance=0; // using integer doesnt work, it produces very inacurate solutions
    
    printf("Please enter Voltage:");
    scanf("%lf",&Voltage);
    printf("Please enter Resistance:");
    scanf("%lf",&Resistance);
    
    Power=(Voltage*Voltage)*(1/Resistance);
    
    printf("Power is %lf\n",Power);
    
    int a,b,c,d,x;
    double y;

        printf("Please enter variable a:");
        scanf("%d",&a);
        printf("Please enter variable b:");
        scanf("%d",&b);
        printf("Please enter variable c:");
        scanf("%d",&c);
        printf("Please enter variable d:");
        scanf("%d",&d);
        printf("Please enter variable x:");
        scanf("%d",&x);
        y = 3 * a*x*x*x + (1/4) * b*x*x + 10 * c*x + (-5) * d;
        
    printf("%.3lf\n",y);
    
    
    const float PI = 3.14159;
    
    double Radius, Circumference;
    
    printf("Please enter Radius:");
    scanf("%lf",&Radius);
    
    Circumference = 2*Radius*PI;
    
    printf("The Circumference is %.4lf\n",Circumference);
    
       return 0;
}
