//! @file 
//! @brief String Sort
//! @author NSRG
//! @version 1.0
//!
//! The program can read from the file,sort strings and write the result tu the file
#include <stdio.h>
#include <string.h>
#include <assert.h>

//! This is varible for limit of string's lenght 
const int MAX_L = 50;

//! The function read the file and copy that to two-dimensional array
//! @param Oneg file with strings
//! @param n number of strings in file
//! @param str two-dimensional array to copy file
//! @return 0 if function ends
int FileRead (FILE* Oneg, int n, char str[][MAX_L])
{
	assert (Oneg);
	assert (str);
	
	for (int i = 0; i < n; i++)
	{
		fgets(str[i], MAX_L, Oneg);
	}
	return 0;
}


//! The function copy strings and delete duplicate row
//! @param str two-dimensinal array with strings
//! @param strC two-deminsional array to copy
//! @param n number of strings in str
//! @return number of strings in strC
int CopyFilter (char str[][MAX_L], char strC[][MAX_L], int n)
{
	assert (str);
	assert (strC);
	
	strcpy(strC[0], str[0]);
	int j = 1;
	for (int i = 1; i < n; i++)
	{
		if (strcmp(str[i-1], str[i]))
		{
			strcpy(strC[j], str[i]);
			j++;
		}
	}
	return j;
}

//! The program write two-dimensinal to file
//! @param OnegC file to copy
//! @param m numbers of strings
//! @param strC two-dimensionl array to write 
//! @return 0 if function ends
int FileWrite (FILE* OnegC, int m, char strC[][MAX_L])
{
	assert (OnegC);
	assert (strC);
	
	for (int i = 0; i <= m; i++)
	{
		fputs(strC[i], OnegC);
	}
	return 0;
}

int main() 
{
	FILE* Oneg = fopen ("OneginPushkin.txt", "r");
	int n = 0;
	fscanf (Oneg, "%i\n", &n);
	char str[n][MAX_L];
	FileRead (Oneg, n, str);
	fclose (Oneg);
	
	char strC[n][MAX_L];
	int m = CopyFilter (str, strC, n); 
	
	FILE* OnegC = fopen ("OneginPushkinCopy.txt", "w");
	fprintf (OnegC, "%i\n", m);
	FileWrite (OnegC, m, strC);
	fclose (OnegC);
}