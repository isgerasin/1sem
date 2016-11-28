#include <stdio.h>
#include <math.h>

int SetEllips (double weight, double height, double x0, double y0, double rX, double rY, double step)
{
	if (weight < (fabs(x0) + rX))
	{
		weight = fabs(x0) + rX;
	}
	if (height < (fabs(y0) + rY))
	{
		height = fabs(y0) + rY;
	}
	
	double rY2 = rY*rY, rXY2 = (rX / rY) * (rX / rY);
	for (int x = 0; x <= (rX); x+= step)
	{
		double y = y0 + sqrt (rY2 - rXY2 * (x - x0));
		setPoint (x, y);
		setPoint (x0 - x, y);
		setPoint (x, y0 - y);
		setPoint (x0 - x, y0 - y);
	}
	return 0;
}


int main(int argc, char **argv)
{
	double weight = 0, height = 0, x0 = 0, y0 = 0, rX = 0, rY = 0;
	scanf("%lg %lg %lg %lg %lg %lg", &weight, &height, &x0, &y0, &rX, &rY);
	
	double step = (1/100);
	return SetEllips (weight, height, x0, y0, rX, rY, step);
}
