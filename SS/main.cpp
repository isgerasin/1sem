//! @file 
//! @brief Solves square 
//! @author NSRG
//! @version 1.0
//!
//! The program can equation liner and solves squere
#include <stdio.h>
#include <math.h>
#include <assert.h>

//! This is varible for designation infinity roots
const int SS_INF_ROOTS= -1;
//! This is varible for mistakes
const double EPS=1E-6; 


//!The function compares the number with zero, with an error
//!@param a real numbers
//!@return true or false
int IsZero(double a)
{
	if (fabs(a)<EPS)
	{
		return 1;
	}
	else
	{
		return 0;
	}
};


//! The function solves linear equation
//!@param b, c coefficients of the equation
//!@param x1 variable for root
//!@return numbers of solutions(-1 infinity roots)
int SolveLiner(double b, double c, double* x1)
{
	if (IsZero(b))
	{
		return -1;
	}
	if (IsZero(c))
	{
		return 1;
	}
	else
	{
		*x1 = -c/b ;
		assert(x1);
		return 1;
	}
};

//!The function solves square equation
//!@param a, b, c coefficients of the equation
//!@param x1, x2 variable for root
//!@return numbers of solutions(-1 infinity roots)
int SolveSquare(double a, double b, double c, double* x1, double* x2)
{
	assert(x1);
	assert(x2);
	assert(x1 != x2);
	
	
	if (IsZero(a))
	{
		return SolveLiner(b, c, x1);
	}
	else
	{
		double D=b*b-4*a*c;
		if (D<0)
		{
			return 0;
		}
		else if (D==0)
		{
			*x1=-b/(2*a);
			return 1;
		}
		else 
		{
			double sqrtD=sqrt(D);
			*x1=(-b-sqrtD)/(2*a);
			*x2=(-b+sqrtD)/(2*a);
			return 2;
		}
	}
};


//!The function scans coefficients and prints root
//!@return 0 if programm print roots
int main()
{
	double a=0, b=0, c=0, p=0;
	
	do
	{
		printf("#This is SolveSquare v.1.0 (c) NSRG\n");
		printf("#Enter a b c, float numbers\n");
		fflush(stdin);
		p = scanf("%lg %lg %lg", &a, &b, &c);
	} while (p != 3);
	
	double x1=0, x2=0;
	int n = SolveSquare(a, b, c, &x1, &x2);
	switch (n)
	{
		case 1: // One root
			printf("x1=%lg", x1);
			break;
		case 2: // Two roots
			printf("x1=%lg x2=%lg", x1, x2);
			break;
		case 0: // No roots
			printf("No Roots");
			break;
		case SS_INF_ROOTS: // Infinity roots
			printf("Infinity Roots");
			break;
	}

	return 0;
}