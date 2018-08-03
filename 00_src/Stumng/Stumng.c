#include "Stumng.h"
#include "FileIO.h"


int main(void)
{
	while (1)
	{
		srand((time_t)time(NULL));
		int iSelect;
		puts("1.�ʱ�");
		puts("2.���");
		puts("3.�߰�");
		puts("4.����");
		puts("5.�˻��̸�");
		puts("6.�˻���ȣ");
		puts("7.����");
		puts("8.����");
		puts("9.�ҷ�����");
		puts("99.����");
		printf("�޴�����: ");
		scanf("%d", &iSelect);
		ClearBuffer();
		switch (iSelect)
		{
		case Datainput:
		{
			system("cls");
			InputData();
			break;
		}
		case Dataprint:

		{
			system("cls");
			PrintData();
			break;
		}
		case Datafindname:
		{
			char sr[4];
			printf("�˻��� �̸� �Է�: ");
			scanf("%s", sr);
			system("cls");
			Findname(sr);
			break;
		}
		case Datafindindex:
		{
			int iSearch;
			printf("�˻��� ��ȣ �Է�: ");
			scanf("%d", &iSearch);
			system("cls");
			Findindex(iSearch);
			break;
		}
		case Datadelete:
		{
			char sr[4];
			printf("������ �̸� �Է�: ");
			scanf("%s", sr);
			ClearBuffer();
			DeleteData(sr);
			break;
		}
		case DataAdd:
		{
			AddData();
			break;
		}
		case DataEdit:
		{
			EditData();
			break;
		}
		case DataSave:
		{
			FileSave();
			break;
		}
		case DataLoad:
		{
			char * szFile = NULL;
			
			szFile = Datafileload();
			if (szFile != NULL)
			{
				int Mode = Binarytextload(szFile);
				FileLoad(szFile, Mode);
			}
			else
			{
				system("cls");
				puts("���� �ҷ����� ����.");
			}
			break;
		}
		case Exit:
		{
			puts("���α׷��� �����մϴ�.");
			free(StudentData);
			return 0;
		}
		default:
		{
			puts("\n�߸��� �Է��Դϴ�.\n");
		}
		}
	}
}