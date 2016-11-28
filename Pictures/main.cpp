#include <stdio.h>
#include <string.h>
#include <fstream>

const int MAXL = 100;

int PicComp (char p1[], char p2[])
{
	if (sizeof(p1) != sizeof(p2))
		return 0;
	int len = strlen(p1);
	for (int i = 0; i < len; i++)
		if (p1[i] != p2[i])
			return 0;
	return 1;
}  

int DoFile(FILE* pic, char p[])
{
	int m = fgetc(pic), n = fgetc(pic);
	for (int i =0; i < m*n; i++)
		p[i] = fgetc(pic);
}

int main()
{
	FILE* pic1 = fopen("picture1.txt", "r");
	FILE* pic2 = fopen("picture2.txt", "r");
	
	char p1[MAXL], p2[MAXL];
	
	DoFile(pic1, p1);
	DoFile(pic2, p2);

}
