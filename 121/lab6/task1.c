/* Programmer: Ethan Kanyid
* Class: CptS 121, Fall 2023
* Programming lab: Crow_Fly
* Date: 9/29/2023
* Description: Functions
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define PI 3.14159265

double dmsToRadians(double dms[3]) // this function is the most nested function. it takes the input and converts it to radians
{
    double radians;
    
    radians = dms[0]+(dms[1]/60)+(dms[2]/3600);

    radians = radians*PI/180;
    
    return radians;
}

void polarToCartesian(double latitude[3], double longitude[3],double position[3])
{
    double theta = dmsToRadians(latitude); //dmstoradians is nested in polarToCartesian
    double phi = dmsToRadians(longitude);
    position[0] = cos(theta) * cos(phi);
    position[1] = cos(theta) * sin(phi);
    position[2] = sin(theta);
}


double arcLength(double latitude0[3], double longitude0[3],
                 double latitude1[3], double longitude1[3])
{

    double arc_length;
    double position0[3];
    double position1[3];
    polarToCartesian(latitude0, longitude0, position0); //polar to cartesian is nested within arclength
    polarToCartesian(latitude1, longitude1, position1);
    
    arc_length = acos(position0[0]*position1[0]+position0[1]*position1[1]+position0[2]*position1[2]);
    
    return arc_length;
}


double crowFly(double latitude0[3], double longitude0[3],
               double latitude1[3], double longitude1[3])
{

    double distance;
    
    distance = arcLength(latitude0,longitude0,latitude1,longitude1)*6378; // the arclength function is nested within crowfly
    
    
    return distance;
}

int main(void) // compilation begins from the main function
{
    double latitude0[3], longitude0[3];
    double latitude1[3], longitude1[3];

    printf(" from latitude (d m s): ");
    scanf("%lf %lf %lf", &latitude0[0], &latitude0[1], &latitude0[2]);
    printf("from longitude (d m s): ");
    scanf("%lf %lf %lf", &longitude0[0], &longitude0[1], &longitude0[2]);

    printf("to latitude (d m s): ");
    scanf("%lf %lf %lf", &latitude1[0], &latitude1[1], &latitude1[2]);
    printf("  to longitude (d m s): ");
    scanf("%lf %lf %lf", &longitude1[0], &longitude1[1], &longitude1[2]);

    printf("distance: %.1f km\n",
           crowFly(latitude0, longitude0, latitude1, longitude1));
    
    // the crowfly function is called which is the trigger for all the other functions
    return 0;
}
