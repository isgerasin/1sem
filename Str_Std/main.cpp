#include <stdio.h>
#include <string.h>
#include <assert.h>

#define DEBUG

const int MAX_L = 100;

int Input_Pointer (const char* outp, char* str);

char* Input_Stat (const char* outp, int len);

char* Input_Dinamic (const char* outp, int len);

int My_Strlen (char* str);

int My_Strncpy (char* strC, const char* str, int n);

int My_Strncat (char* strfrst, const char* strscnd, int n);

char* My_Strstr (char* str1, char* str2);

char* My_Strtok (char* str1, char* str2);

int main()
{
	char str[MAX_L];
	char* str_stat = Input_Stat ("Name?\n", MAX_L);
	char* str_dinamic = Input_Dinamic ("Name?\n", MAX_L);
	
	assert (!Input_Pointer ("Name?\n", str));
	
	printf ("%i\n", My_Strlen (str_stat));
	
	fputs (str_stat, stdout);
	printf("\n\n\n");
	char* tmp = My_Strstr (str_stat, str_dinamic);
	fputs (tmp, stdout);
	
	free (str_dinamic);
	return 0;
}

int Input_Pointer (const char* outp, char* str)
{
#ifdef DEBUG
	assert (outp);
	assert (str);
#endif
	
	printf("%s", outp);
	fgets(str, MAX_L, stdin);
	return 0;
}

char* Input_Stat (const char* outp, int len)
{
#ifdef DEBUG
	assert (outp);
#endif
	
	printf("%s", outp);
	static char str[MAX_L];
	fgets(str, len-1, stdin);
	return str;
}

char* Input_Dinamic (const char* outp, int len)
{
#ifdef DEBUG
	assert (outp);
#endif
	
	printf("%s", outp);
	char* str = (char*) calloc(len+1, sizeof (*str));
	fgets(str, len - 1, stdin);
	return str;
	
}

int My_Strlen (char* str)
{
#ifdef DEBUG
	assert (str);
#endif
	
	char* strcopy = str;
	int i = 0;
	while ( (*strcopy) != '\0')
	{
		i++;
		strcopy++;
	}
	return i;
}

int My_Strncpy (char* strC, const char* str, int n)
{
#ifdef DEBUD
	assert (str);
	assert (strC);
#endif
	
	assert( strlen(strC) > n );
	assert( strlen(str) > n );
	int i = 0;
	for ( i = 0; i < n; i++)
	{
		strC[i] = str[i];
	}
	return n - i;
}

int My_Strncat (char* strfrst, const char* strscnd, int n)
{
#ifdef DEBUG
	assert (strfrst);
	assert (strscnd);
#endif
	
	int lenstr1 = My_Strlen (strfrst);
	if ( MAX_L - lenstr1 < n)
	{
		return -1;
	}
	else
	{
		int i = 0;
		for (i = 0; i < n ; i++ )
		{
			strfrst[i + lenstr1 - 1] = strscnd[i];
		}
		strfrst[i + lenstr1] = '\n';
		strfrst[i + lenstr1 + 1] = '\0';
		return 0;
	}
}

char* My_Strstr (char* str1, char* str2)
{
#ifdef DEBUG
	assert (str1);
	assert (str2);
#endif
	
	int len1 = My_Strlen (str1);
	int len2 = My_Strlen (str2);
	for (int i = 0; i < len1; i++)
	{
		if ( str1[i] == str2[0] )
		{
			
			int cmp = 0;
			for (int j = 0; j < len2; j++)
			{
				if (str1[i+j] != str2[j])
				{
					cmp++;
				}
			}
			if (cmp == 1)
			{
				return str1 + i;
			}
		}
	}
	return NULL;
}

char* My_Strtok (char* str1, char* str2)
{
#ifdef DEFINE
	assert (str1);
	assert (str2);
#endif
	
	
	int len1 = My_Strlen (str1);
	int len2 = My_Strlen (str2);
	char* str3 = (char*) calloc (len1 + 1, sizeof (*str3));
	
	for (int i = 0; i < len1; i++)
	{
		int cmp = 0;
		for (int j = 0; j < len2; j++)
		{
			if ( str1[i] == str2[j] )
			{
				cmp++;
			}
			
		}
		if (cmp == 0)
		{
			My_Strncat ( str1[i], str3 );
		}
	}
}

