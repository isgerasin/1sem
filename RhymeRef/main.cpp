#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>

//! This is varible for limit of string's lenght 
const int MAX_L = 100;

//! The function read the file and copy that to two-dimensional array
//! @param fl file with strings
//! @param n number of strings in file
//! @param str two-dimensional array to copy file
//! @return 0 if function ends
int FileRead (FILE* fl, int n, char str[][MAX_L])
{
	assert (fl);
	assert (str);
	
	for (int i = 0; i < n; i++)
	{
		fgets(str[i], MAX_L, fl);
	}
	return 0;
}

//! The program write two-dimensinal to file
//! @param fl file to write
//! @param n numbers of strings
//! @param strC two-dimensionl array to read
//! @return 0 if function ends
int FileWrite (FILE* fl, int n, char strC[][MAX_L])
{
	assert (fl);
	assert (strC);
	
	for (int i = 0; i < n; i++)
	{
		fputs(strC[i], fl);
	}
	return 0;
}

//! The function copy two-dimensinal array
//! @param str two-dimensinal array 
//! @param n number of strings in file
//! @param str two-dimensional array to copy str
//! @return 0 if function ends
int TwoArrCpy (char str[][MAX_L], char strC[][MAX_L], int n)
{
	assert (str);
	assert (strC);
	
	for (int i = 0; i < n; i++)
	{
		strcpy (strC[i], str[i]);
	}
	return 0;
}

//! The function swap two strings
//! @param str string 
//! @param strC string 
//! @return 0 if function ends
int swapStr (char str[], char strC[])
{
	assert (str);
	assert (strC);
	
	char buf[MAX_L] = {};
	strcpy (buf, str);
	strcpy (str, strC);
	strcpy (strC, buf);
	return 0;
}

int RhymeCmp (char str1[], char str2[])
{
	assert(str1);
	assert(str2);
	
	unsigned int i1 = strlen(str1);
	unsigned int i2 = strlen(str2);
	
	while ( (i1  > 0) && (i2 > 0) )
	{
		i1--;
		i2--;
		while ( !( ('A' <= str1[i1]) && (str1[i1] <= 'z') ) )
		{
			i1--;
		}
		while ( !( ('A' <= str2[i2]) && (str2[i2] <= 'z') ) )
		{
			i2--;
		}
		if (str1[i1] < str2[i2])
		{
			return str1[i1] - str2[i2];
		}
		else if (str1[i1] > str2[i2])
		{
			return str1[i1] - str2[i2];
		}
	}

	return i1-i2;
}

int RhymeSort (char str[][MAX_L], char strC[][MAX_L], int n)
{
	assert (str);
	assert (strC);
	
	TwoArrCpy (str, strC, n);
	
	for (int i = 0; i < n; i++)
	{
		int minS = i;
		for (int j = i+1; j < n; j ++)
		{
			if ( RhymeCmp (strC[i], strC[minS]) > 0)
			{
				minS = i;
			}
		}
		swapStr (strC[i], strC[minS]);
	}
	return 0;
}

int main(int argc, char **argv)
{
	FILE* fl1 = fopen ("Shakespeare.txt", "r");
	int n = 0;
	fscanf (fl1, "%i\n", &n);
	char str[n][MAX_L];
	FileRead (fl1, n, str);
	fclose (fl1);
	
	char strC[n][MAX_L] = {};
	RhymeSort (str, strC, n);
	
	FILE* fl2 = fopen ("ShakespeareSortRhyme.txt", "w");
	fprintf (fl2, "%i\n", n);
	FileWrite (fl2, n, strC);
	fclose (fl2);
}