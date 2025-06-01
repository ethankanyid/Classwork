#include "grafic.h"

void line(double p0[2], double p1[2]);

void color(double r, double g, double b);
    //Bright green: (0.0, 1.0, 0.0)
    //Magenta: (1.0, 0.0, 1.0)
    //Gray: (0.5, 0.5, 0.5)
    //Dark blue: (0.0, 0.0, 0.5)

void fractalTriangle(double p0[],double p1[],double p2[], int i);

void init(const char **appTitle_pp)
{
    *appTitle_pp = "\"grafic\" square demo";
}

void middle(double p0[], double p1[], double s, double r[2]) 
{
    r[0] = p[0]+(p1[0]-p[0])/3;                           // needs to find the midpoint of the line in thirds 
    r[1] = 
}

void triangleDraw(double p0[], double p1[], double p2[], double p3[],double p4[]) 
{
    // Draw lines to create the triangle.
    
    line(p0, p1);
    line(p1, p2);
    line(p2, p3);
    line(p3, p4);
}

void redraw(void)
{
    double p0[2] = (-0.5, 0);
    double p1[2] = (0, 1);
    double p2[2] = (0.5, 0);
    double p3[2];
    double p4[2];
    double mp01[3], mp12[3], mp20[3];


    middle(p0, p1, 1/3, mp01);
    middle(p1, p2, 1/3, mp12);      //calculates the line in thrids
    middle(p2, p0, 1/3, mp20);



    triangleDraw(p0, p1, p2, p3, p4);       // draws the koch curve

                                            //somehow need to undraw a line???

    triangleDraw(p0, mp01, mp20);
    triangleDraw(mp01, p1, mp12);       // draws new lines with those three points
    triangleDraw(mp20, mp12, p2);

    fractaltriangle(p0, mp01, mp20,4);
    fractaltriangle(mp01, p1, mp12,4);      //recursive step
    fractaltriangle(mp20, mp12, p2,4);
}



void fractalTriangle( double p0[],double p1[],double p2[], int i)
{

    if (i <0)          // Base case will go here. 
    {   
        return;
    }

    double mp01[2], mp12[2], mp20[2];

    switch (i)
    {
    case 1:
        color (0.5,0.0,0.5);
        break;
    case 2:
        color (0.0,1.0,0.0);
        break;
    case 3:
        color (0.0,0.5,1.0);
        break;
    case 4:
        color (1.0,0.5,1.0);
        break;
    default:
        break;
    }

    middle(p0, p1, 0.5, mp01);
    middle(p1, p2, 0.5, mp12);
    middle(p2, p0, 0.5, mp20);


    triangleDraw(p0, mp01, mp20);
    triangleDraw(mp01, p1, mp12);
    triangleDraw(mp20, mp12, p2);
    

    fractaltriangle(p0, mp01, mp20,i-1);
    fractaltriangle(mp01, p1, mp12,i-1);
    fractaltriangle(mp20, mp12, p2,i-1);    // Recursive step will go here

}