#include "Stumng.h"
#include "FileIO.h"


int main(void)
{
	while (1)
	{
		srand((time_t)time(NULL));
		int iSelect;
		puts("1.초기");
		puts("2.출력");
		puts("3.추가");
		puts("4.수정");
		puts("5.검색이름");
		puts("6.검색번호");
		puts("7.삭제");
		puts("8.저장");
		puts("9.불러오기");
		puts("99.종료");
		printf("메뉴선택: ");
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
			printf("검색할 이름 입력: ");
			scanf("%s", sr);
			system("cls");
			Findname(sr);
			break;
		}
		case Datafindindex:
		{
			int iSearch;
			printf("검색할 번호 입력: ");
			scanf("%d", &iSearch);
			system("cls");
			Findindex(iSearch);
			break;
		}
		case Datadelete:
		{
			char sr[4];
			printf("삭제할 이름 입력: ");
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
				puts("파일 불러오기 실패.");
			}
			break;
		}
		case Exit:
		{
			puts("프로그램을 종료합니다.");
			free(StudentData);
			return 0;
		}
		default:
		{
			puts("\n잘못된 입력입니다.\n");
		}
		}
	}
}