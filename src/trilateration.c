#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct point 
{
    float x,y;
};
typedef struct point POINT;


POINT trilateration(POINT point1, POINT point2, POINT point3, float r1, float r2, float r3);
float calcul_dist(float RSSI);

int main (void)
{    
	POINT R1, R2, R3, T1;
	float RSSI1, RSSI2, RSSI3;

    	R1.x = 0;
    	R1.y = 0;

    	R2.x = 0;
    	R2.y = 1;

    	R3.x = 1;
    	R3.y = 0;

	RSSI1 = -72.011611734;
	RSSI2 = -72.011611734;
	RSSI3 = -72.011611734;

	T1 = trilateration(R1, R2, R3, RSSI1, RSSI2, RSSI3);

   	fprintf(stderr, "**** Résultat: ***** \n");
   	fprintf(stderr, "x: %f \n", T1.x);
   	fprintf(stderr, "y: %f \n", T1.y);

	return 0;
}

float calcul_dist(float RSSI)
{
	float calcul, nbpuiss;
	nbpuiss=(((-69)-(RSSI))/(10*2));

	calcul = pow(10,nbpuiss);

	return calcul;
}


POINT trilateration(POINT point1, POINT point2, POINT point3, float RSSI1, float RSSI2, float RSSI3)
{
    POINT result;
    float d1, d2, d3;
    
    double x,y;
    double u, v;

    d1 = calcul_dist(RSSI1);
    d2 = calcul_dist(RSSI2);
    d3 = calcul_dist(RSSI3);

    u = point3.x - point1.x;
    v = point2.y - point1.y;

    x = ( ((u * u) + ((d1 * d1) - (d2 * d2))  ) / (2 * u));
    y = ( ((v * v) + ((d1 * d1) - (d3 * d3))  ) / (2 * v));

    result.x = x;
    result.y = y;
    return (result);
}