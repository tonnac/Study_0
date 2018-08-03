#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> 
#include <conio.h>

void DrawText()
{
	FILE* fp = fopen("FILE_IO_Example.c", "r");
	char buffer[255] = { 0, };
	int iLine = 0;
	while (!feof(fp))
	{
		printf("\n%05d : ", ftell(fp));
		for (int i = 0; i < 10; i++)
		{
			buffer[i] = fgetc(fp);
			if (feof(fp))break;
		}
		for (int i = 0; i < 10; i++)
		{
			if (buffer[i] == '\n' || buffer[i] == '\t' || buffer[i] == '\r')
			{
				buffer[i] = ' ';
			}
			printf("%c", buffer[i]);
		}
		iLine++;
		if (iLine % 10 == 0)
		{
			printf("\n아무키나 누르시오");
			_getch();
		}
		/*fgets(buffer, sizeof(char) * 255, fp);
		printf("\n%s", buffer);*/
	}
	fclose(fp);
}
void copy(const char*srcFile, const char*destFile)
{
	FILE* readfp = fopen(srcFile, "r");
	FILE* writefp = fopen(destFile, "wb");
	fseek(readfp, 0, SEEK_END);
	int iTotalsize = ftell(readfp);
	char * buffer = (char*)malloc(iTotalsize * sizeof(char));
	memset(buffer, 0, sizeof(char)*iTotalsize);			//메모리 내용 0으로 초기화
	fseek(readfp, 0, SEEK_SET);
	fread((void*)buffer, sizeof(char), iTotalsize, readfp);
	fwrite((void*)buffer, sizeof(char), iTotalsize, writefp);

	free(buffer);
	fclose(readfp);
	fclose(writefp);
}
int main()
{
	DrawText();
	system("cls");
	copy("Note.c", "copy1.h");



	return 0;
}