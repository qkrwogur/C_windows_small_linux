#include <stdio.h>
#include <direct.h>		
#include <errno.h>		
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <io.h>
#include <conio.h>

static char input[10][10];
static char Sinput[20];
static char where[50];

char c[100][10] = { 0, };
char treeb[100] = { 0, };
int treei = 0;
int lscc;

void start();
void pwd();
void makefile();
void cd();
void clear();
void ls();
void vi();
void  tree();
void wrmdir();
void rm();
void gotoxy(int x, int y);
int main()
{


	char a[50], * ptr, b[50] = { "" };
	_getcwd(a, 50);
	ptr = strtok(a, "\\");

	printf(a);
	while (strcmp(ptr, "project"))
	{

		strcat(b, ptr);
		strcat(b, "\\\\");
		ptr = strtok(NULL, "\\");
	}
	//strcat(b, "Desktop");			  
	printf("���� : %s\n", b);

	_chdir(b);
	strcpy(where, b);
	start();


	return 0;
}
void start()
{
	int i, j, k, leng = 0;

	while (1)
	{
		printf("# :");

		gets(Sinput);


		leng = strlen(Sinput);




		for (i = 0, k = 0, j = 0; i < leng; i++)
		{

			if (Sinput[i] != ' ')
			{
				input[j][k] = Sinput[i];
				k++;
			}

			else
			{
				j++;
				k = 0;
			}

		}


		if (strcmp(input[0], "pwd") == 0)
			pwd();
		else if (strcmp(input[0], "exit") == 0)
			break;
		else if (strcmp(input[0], "mkdir") == 0)
			makefile();
		else if (strcmp(input[0], "cd") == 0)
			cd();
		else if (strcmp(input[0], "clear") == 0)
			clear();
		else if (strcmp(input[0], "ls") == 0)
			ls();
		else if (strcmp(input[0], "vi") == 0)
			vi();
		else if (strcmp(input[0], "tree") == 0)
			tree();
		else if (strcmp(input[0], "rm") == 0)
			rm();
		else if (strcmp(input[0], "rmdir") == 0)
			wrmdir();



		for (i = 0, k = 0, j = 0; i < leng; i++)
		{

			if (Sinput[i] != ' ')
			{
				input[j][k] = NULL;
				k++;
			}

			else
			{
				j++;
				k = 0;
			}

		}


		leng = 0;


	}
}

void pwd()//���� ���� ��ġ ���
{
	char a[50];
	printf("%s\n", _getcwd(a, 50));

}
void makefile()//���� ����
{
	char strFolderPath[50] = { "" };
	int Result;
	strcpy(strFolderPath, where);
	strcat(strFolderPath, "\\\\");
	strcat(strFolderPath, input[1]);
	Result = _mkdir(strFolderPath);
	if (Result == 0)
	{
		printf("���� ���� ����\n");
	}
	else if (Result == -1)
	{
		perror("���� ���� ���� - ������ �̹� �ְų� ����Ȯ��\n");
		printf("errorno : %d\n", errno);
	}
	strcpy(strFolderPath, "");
}

void  cd()//���� �̵�
{
	int i;
	char* ptr, a[50] = { "" };


	ptr = strtok(input[1], "/");
	while (ptr != NULL)
	{
		strcat(a, "\\\\");
		strcat(a, ptr);
		ptr = strtok(NULL, "/");
	}

	strcat(where, a);
	i = _chdir(where);
	_getcwd(where, 50);
	printf("%s\n", where);
	if (i == -1)
	{
		perror("\n");
		printf("errorno : %d\n", errno);
	}


}
void clear()
{
	system("cls");
}
void ls()
{
	lscc = 0;
	struct _finddata_t c_file;
	int hFile;
	char path[] = "*.*";

	int i = 0;

	if ((hFile = _findfirst(path, &c_file)) == -1) {
		switch (errno) {
		case ENOENT:
			printf(":: ������ ���� ::\n");
			break;
		default:
			break;
		}
	}

	else {
		printf("-- ���� ��� --\n");
		do {

			printf("%s\n", c_file.name);
			strcpy(c[i], c_file.name);
			i++;
			lscc++;
		} while (_findnext(hFile, &c_file) == 0);


		_findclose(hFile);
	}

}
void vi()
{

	ls();
	clear();
	int ci = 2;
	char b[100][100] = { 0, };
	char* ptrc;
	int ic = 0, jc = 0, kc = 0;
	char a;
	int  x = 1, y = 1, i = 0, j = 0, imax = 0, k, n = 0;
	int length1 = 0, temp, flag = 0, flag2 = 0;
	char adrs[100] = { 0, };

	for (kc = 0; kc < lscc; kc++)
	{

		if (strcmp(input[1], c[ci]) == 0)//�ߺ��� ������ ������ if�� ���θ� �����Ѵ�.
		{
			FILE* fpc = fopen(input[1], "r");//������ �� �������� ����.

			fread(adrs, sizeof(adrs), 1, fpc);//100�� ũ�� ��ŭ ������ �о� �´�.
			ptrc = strtok(adrs, "\n");//�� �ٲ��� �������� ������ ������ �ڸ���.

			if (adrs != NULL)//������ ������ �����ϸ� 
			{
				while (ptrc != NULL)//������ ������ �� ���� ����
				{
					strcpy(b[ic], ptrc);//���� ������ ���� �Ѵ�. 
					ptrc = strtok(NULL, "\n");//
					ic++;
					jc++;
				}
			}
			for (ic = 0; ic <= jc; ic++)
			{

				printf("%s\n", b[ic]);
				imax++;
			}
			imax -= 2;


			fclose(fpc);
			flag2 = 1;
			flag = 1;
			break;
		}
		else
			ci++;
	}

	FILE* fp = fopen(input[1], "wt");
	while (1)
	{
		if (kbhit())
		{
		next:
			a = getch();
			if (a == 'i' || a == 'I')
			{
				i = --y;
				j = --x;
				y++, x++;

				while (1)
				{



					b[i][j] = getch();

					putch(b[i][j]);
					if (n == 1)
						putch(b[i][j]);
					if (b[i][j] == 27)
					{

						n++;
						goto next;
					}
					else if (b[i][j] == 13)
					{
						i++;
						j = 0;
						imax++;
						b[i][j] = NULL;
						gotoxy(x, ++y);
					}
					else if (b[i][j] == 8)
					{
						if (j > 0)
						{

							j--;
							b[i][j] = NULL;

							gotoxy(--x, y);
							if (x == 0)
								x++;
						}
					}
					else
					{
						j++;

					}
					n = 0;

					flag++;


				}

			}

			if (a == 27)
			{
				for (k = 0; k <= imax; k++)
				{
					length1 = strlen(b[k]);
					if (flag2 != 1)
						length1--;


					b[k][length1] = '\n';
				}

				for (k = 0; k <= imax; k++)
				{
					fprintf(fp, b[k]);
				}
				clear();
				break;
			}


			switch (a)
			{
			case 72://��

				y--;
				if (y <= 0)
					y++;
				else if (flag > 0)
				{
					temp = y;

					temp--;

					length1 = strlen(b[temp]);

					if (length1 < x)
					{
						x = length1;
					}

					length1 = 0;

				}
				gotoxy(x, y);
				break;
			case 75://����
				x--;
				if (x <= 0)
					x++;
				gotoxy(x, y);
				break;
			case 77://������
				y--;
				length1 = strlen(b[y]);
				y++;
				if (flag2 == 0)
					length1--;

				if (length1 >= x)
				{
					x++;
					gotoxy(x, y);
				}
				break;
			case 80://�Ʒ�


				if (imax >= y)
				{
					y++;

				}
				if (flag > 0)
				{
					temp = y;
					temp--;
					length1 = strlen(b[temp]);
					if (length1 < x)
					{
						x = length1;
					}
					length1 = 0;

				}

				gotoxy(x, y);
				break;
			default:
				break;

			}



		}



	}

	fclose(fp);

}
void gotoxy(int x, int y)
{
	COORD Pos = { x - 1 ,y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
void rm()
{

	int nResult = remove(input[1]);

	if (nResult == 0)
	{
		printf("���� ���� ����\n");
	}
	else if (nResult == -1)
	{
		perror("���� ���� ����\n");
	}
}
void wrmdir()
{

	int nResult = rmdir(input[1]);

	if (nResult == 0)
	{
		printf("���� ���� ����\n");
	}
	else if (nResult == -1)
	{
		perror("���� ���� ���� - ���� �ȿ� ������ �ְų� �����\n");
		printf("errorno : %d\n", errno);
	}
}
void  tree()
{

	struct _finddata_t c_file;
	int hFile;
	char path[] = "*.*";
	char a[100] = { 0, };
	int i;


	if ((hFile = _findfirst(path, &c_file)) == -1) {
		switch (errno) {
		case ENOENT:
			printf(":: ������ ���� ::\n");
			break;
		default:
			break;
		}
	}

	else {

		do {
			if (strcmp(c_file.name, ".") == 0 || strcmp(c_file.name, "..") == 0)
				goto jump;
			if (strcmp(c_file.name, treeb) == 0)
				goto dd;
			printf("|");
			for (i = 0; i < treei; i++)
			{
				printf("     ");
				printf("|");
			}

			printf("_____");
			-printf("%s\n", c_file.name);
			if (c_file.attrib == 16)
			{
				strcpy(treeb, c_file.name);
				_chdir(treeb);

				treei++;

				tree();

				treei--;

				_chdir("..");
			}
		dd:
		jump:;

		} while (_findnext(hFile, &c_file) == 0);

		_findclose(hFile);

	}
}