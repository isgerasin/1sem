#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <malloc.h>

#define DEBUG 

int File_Len (FILE* fl1);

int Open_File (FILE* fl1, char* buf, int len);

int Set_Pointer (char* buf, char* Original[]);

int File_Write (FILE* fl, int strnum, char* strC[]);

int Str_Sort_Max (char* str[], int strnum);

int Str_Sort_Bubble (char* str[], int strnum);

int Str_Sort (char* str[], int strnum, char Mode);

int Cpy_Char (char* str[], char* strC[], int strnum);

int Swap_str (char* str1, char* str2);

int Rhyme_Sort (char* str[], int strnum);

int Str_Rh_Cmp (char* str1, char* str2);

int main(int argc, char **argv)
{
	FILE* fl1 = fopen ("Shak.txt", "r");
	int len = File_Len (fl1);
	char* buf= (char*) calloc(len+1, sizeof(*buf)); 
	int strnum = Open_File (fl1, buf, len);
	char* Original[strnum];
	assert (! Set_Pointer (buf, Original));
	fclose (fl1);
	
	FILE* fl0 = fopen("Shak2.txt", "w");
	assert (! File_Write (fl0, strnum, Original));
	fclose(fl0);
	
	char* Rh_Sort[strnum];
	assert (! Cpy_Char (Original, Rh_Sort, strnum));
	assert (!Rhyme_Sort (Rh_Sort, strnum));
	
	FILE* fl2 = fopen("Shak_Rhyme_sort.txt", "w");
	assert (! File_Write (fl2, strnum, Rh_Sort));
	fclose(fl2);
	
	
	char* ABC_Sort[strnum];
	assert (! Cpy_Char (Original, ABC_Sort, strnum));
	assert (! Str_Sort (ABC_Sort, strnum, 'b'));
	
	FILE* fl3 = fopen("Shak_ABC_sort.txt", "w");
	assert (! File_Write (fl3, strnum, ABC_Sort));
	fclose(fl3);
	
	free (buf); // !!!
}

int Open_File (FILE* fl1, char* buf, int len)
{
#ifdef DEBUG
	assert (fl1);
	assert (buf);
	assert (len);
#endif
	
	int strnum = 0;
	fread (buf, sizeof (*buf), len+1, fl1);
	
	for (char* c = strchr (buf, '\n'); c > 0; c = strchr(c + 1, '\n'))
	{
		strnum++;
	}
	return strnum;
}

int File_Len (FILE* fl1)
{
#ifdef DEBUG
	assert (fl1);
#endif
	
	fseek (fl1, 0, SEEK_END);
	int end = ftell (fl1);
	
	fseek (fl1, 0, SEEK_SET);
	int start = ftell (fl1);
	
	return (end - start);
}

int Set_Pointer (char* buf, char* Original[])
{
#ifdef DEBUG
	assert(buf);
	assert(Original);
#endif
	
	Original[0] = buf;
	int i = 1;
	for (char* c = strchr(buf, '\n'); c; c = strchr(c+1, '\n'))
	{
		*c = '\0';
		Original[i] = c + 1;
		i++;
	}
	return 0;
}

int File_Write (FILE* fl, int strnum, char* strC[])
{
#ifdef DEBUG
	assert (fl);
	assert (strC);
#endif
	
	for (int i = 0; i < strnum; i++)
	{
		fputs(strC[i], fl);
		fputc('\n', fl);
	}
	return 0;
}

int Str_Sort_Max (char* str[], int strnum)
{
#ifdef DEBUG
	assert (str);
#endif
	
	for (int i = 0; i < strnum; i++)
	{
		int minS = i;
		for (int k = i +1 ; k < strnum; k ++)
		{
			if (strcmp(str[k], str[minS]) < 0)
			{
				minS = k;
			}
		}
		char* temp = str[i];
		str[i] = str[minS];
		str[minS] = temp;
	}
	return 0;
}

int Str_Sort_Bubble (char* str[], int strnum)
{
#ifdef DEBUG
	assert(str);
#endif
	
	for (int i = 0; i < strnum-1; i++)
	{
		for (int j = 0; j < strnum-1; j++)
		{
			if (strcmp(str[j], str[j+1]) > 0)
			{
				char* temp = str[j];
				str[j] = str[j+1];
				str[j+1] = temp;
			}
		}
	}
	return 0;
}

int Str_Sort (char* str[], int strnum, char Mode)
{
#ifdef DEBUG
	assert (str);
#endif
	
	switch(Mode)
	{
		case 'm': Str_Sort_Max(str, strnum); break;
		case 'b': Str_Sort_Bubble(str, strnum); break;
	}
	return 0;
}

int Swap_str (char* str1, char* str2)
{
#ifdef DEBUG
	assert(str1);
	assert(str2);
#endif
	
	char* temp = str1;
	str1 = str2;
	str2 = temp;
	return 0;
}

int Rhyme_Sort (char* str[], int strnum) 
{
#ifdef DEBUG
	assert (str);
#endif
	
	for (int i = 0; i < strnum; i++)
	{
		int minS = i;
		for (int k = i +1 ; k < strnum; k ++)
		{
			if (Str_Rh_Cmp (str[k], str[minS]) < 0)
			{
				minS = k;
			}
		}
		char* temp = str[i];
		str[i] = str[minS];
		str[minS] = temp;
	}
	return 0;
}

int Str_Rh_Cmp (char* str1, char* str2)
{
#ifdef DEBUG
	assert(str1);
	assert(str2);
#endif
	
	int len1 = strlen(str1);
	
	int len2 = strlen(str2);
	
	while ((len1 > 0) && (len2 > 0))
	{
		len1--;
		len2--;
		
		while ( !( ('A' <= str1[len1]) && (str1[len1] <= 'z')  || ('0' <= str1[len1]) && (str1[len1] <= '9') ) )
		{
			len1--;
		} 
		while ( !( ('A' <= str2[len2]) && (str2[len2] <= 'z')  || ('0' <= str2[len2]) && (str2[len2] <= '9') ) )
		{
			len2--;
		}
		if (str1[len1] > str2[len2])
		{
			return 1;
		}
		else if (str1[len1] < str2[len2])
		{
			return -1;
		}

	}
	
	return 0;
}

int Cpy_Char (char* str[], char* strC[], int strnum)
{
#ifdef DEBUG
	assert (str);
	assert (strC);
#endif
	
	for (int i = 0; i < strnum; i++)
	{
		strC[i] = str[i];
	}
	return 0;
}


// qsort()
//