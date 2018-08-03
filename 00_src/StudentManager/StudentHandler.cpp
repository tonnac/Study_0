#include "StudentHandler.h"

using namespace std;


void StudentHandler::MainMenu()
{
	while (1)
	{
		int iSelect;
		MENU type;
		cout << "[학생관리 프로그램]" << endl;
		cout << "1.학생 추가" << endl;
		cout << "2.학생 수정" << endl;
		cout << "3.학생 검색" << endl;
		cout << "4.학생 삭제" << endl;
		cout << "5.학생 출력" << endl;
		cout << "6.랜덤 입력" << endl;
		cout << "7.파일 저장" << endl;
		cout << "8.파일 로드" << endl;
		cout << "9.프로그램 종료" << endl;
		cout << "입력: ";
		cin >> iSelect;
		type = static_cast<StudentHandler::MENU>(iSelect);
		switch (type)
		{
		case MENU::ADD:
			AddStudent();
			break;
		case MENU::EDIT:
			EditStudent();
			break;
		case MENU::DELETE:
			DeleteStudent();
			break;
		case MENU::SEARCH:
			SearchStudent();
			break;
		case MENU::PRINT:
			PrintStudent();
			break;
		case MENU::RANDOM:
			RandomCreate();
			break;
		case MENU::SAVE:
			SaveFile();
			break;
		case MENU::LOAD:
			LoadFile();
			break;
		case MENU::EXIT:
			cout << "프로그램을 종료합니다." << endl;
			return;
		default:
			system("cls");
			cout << "잘못된 입력입니다." << endl;
		}
	}
}
void StudentHandler::AddStudent()
{
	char Name[256];
	int Kor;
	int Mat;
	int Eng;
	cout << "이름 입력: ";
	cin >> Name;
	cout << "국어 점수 입력: ";
	cin >> Kor;
	cout << "수학 점수 입력: ";
	cin >> Mat;
	cout << "영어 점수 입력: ";
	cin >> Eng;
	StdList.AddLink(new StudentData(Name, Kor, Mat, Eng));
	system("cls");
	cout << "추가 완료." << endl;
}
void StudentHandler::SearchStudent()
{
	char SearchName[256];
	int iSelect;
	int num;
	cout << "1. 번호로 검색, 2. 이름으로 검색" << endl;
	cout << "검색 방법 선택: ";
	cin >> iSelect;
	if (iSelect == 1)
	{
		cout << "번호 입력: ";
		cin >> num;
		StudentData * Searchdata = StdList.SearchByNumber(num);
		if (Searchdata == nullptr)
		{
			system("cls");
			cout << "해당하는 번호가 존재하지 않습니다." << endl;
			return;
		}
		else
		{
			system("cls");
			cout << "============================================" << endl;
			cout << "이름\t번호\t국어\t수학\t영어\t총점" << std::endl;
			Searchdata->ShowData();
			cout << "============================================" << endl;
		}
	}
	else
	{
		cout << "이름 입력: ";
		cin >> SearchName;
		StudentData * Searchdata = StdList.SearchByName(SearchName);
		if (Searchdata == nullptr)
		{
			system("cls");
			cout << "해당하는 이름이 존재하지 않습니다." << endl;
			return;
		}
		else
		{
			system("cls");
			cout << "============================================" << endl;
			cout << "이름\t번호\t국어\t수학\t영어\t총점" << std::endl;
			Searchdata->ShowData();
			cout << "============================================" << endl;
		}
	}
}
void StudentHandler::EditStudent()
{
	char Sel;
	char SearchName[256];
	int iSelect;
	int num;
	cout << "1. 번호로 검색, 2. 이름으로 검색" << endl;
	cout << "검색 방법 선택: ";
	cin >> iSelect;
	if (iSelect == 1)
	{
		cout << "번호 입력: ";
		cin >> num;
		StudentData * Searchdata = StdList.SearchByNumber(num);
		if (Searchdata == nullptr)
		{
			system("cls");
			cout << "해당하는 번호가 존재하지 않습니다." << endl;
			return;
		}
		else
		{
			cout << "============================================" << endl;
			cout << "이름\t번호\t국어\t수학\t영어\t총점" << std::endl;
			Searchdata->ShowData();
			cout << "============================================" << endl;
			cout << "자료를 수정하시겠습니까(Y/N):";
			cin >> Sel;
			if (Sel == 'Y' || Sel == 'y')
			{
				StdList.EditLink(Searchdata);
				system("cls");
				cout << "수정 완료" << endl;
			}
			else
			{
				system("cls");
				return;
			}
		}
	}
	else
	{
		cout << "이름 입력: ";
		cin >> SearchName;
		StudentData * Searchdata = StdList.SearchByName(SearchName);
		if (Searchdata == nullptr)
		{
			system("cls");
			cout << "해당하는 이름이 존재하지 않습니다." << endl;
			return;
		}
		else
		{
			cout << "============================================" << endl;
			cout << "이름\t번호\t국어\t수학\t영어\t총점" << std::endl;
			Searchdata->ShowData();
			cout << "============================================" << endl;
			cout << "자료를 수정하시겠습니까(Y/N):";
			cin >> Sel;
			if (Sel == 'Y' || Sel == 'y')
			{
				StdList.EditLink(Searchdata);
				system("cls");
				cout << "수정 완료" << endl;
			}
			else
			{
				system("cls");
				return;
			}
		}
	}
}
void StudentHandler::DeleteStudent()
{
	char Sel;
	char SearchName[256];
	int iSelect;
	int num;
	cout << "1. 번호로 검색, 2. 이름으로 검색" << endl;
	cout << "검색 방법 선택: ";
	cin >> iSelect;
	if (iSelect == 1)
	{
		cout << "번호 입력: ";
		cin >> num;
		StudentData * Searchdata = StdList.SearchByNumber(num);
		if (Searchdata == nullptr)
		{
			system("cls");
			cout << "해당하는 번호가 존재하지 않습니다." << endl;
			return;
		}
		else
		{
			cout << "============================================" << endl;
			cout << "이름\t번호\t국어\t수학\t영어\t총점" << std::endl;
			Searchdata->ShowData();
			cout << "============================================" << endl;
			cout << "자료를 삭제하시겠습니까(Y/N):";
			cin >> Sel;
			if (Sel == 'Y' || Sel == 'y')
			{
				StdList.DelLink(Searchdata);
				system("cls");
				cout << "삭제 완료" << endl;
			}
			else
			{
				system("cls");
				return;
			}
		}
	}
	else
	{
		cout << "이름 입력: ";
		cin >> SearchName;
		StudentData * Searchdata = StdList.SearchByName(SearchName);
		if (Searchdata == nullptr)
		{
			system("cls");
			cout << "해당하는 이름이 존재하지 않습니다." << endl;
			return;
		}
		else
		{
			cout << "============================================" << endl;
			cout << "이름\t번호\t국어\t수학\t영어\t총점" << std::endl;
			Searchdata->ShowData();
			cout << "============================================" << endl;
			cout << "자료를 삭제하시겠습니까(Y/N):";
			cin >> Sel;
			if (Sel == 'Y' || Sel == 'y')
			{
				StdList.DelLink(Searchdata);
				system("cls");
				cout << "삭제 완료" << endl;
			}
			else
			{
				system("cls");
				return;
			}
		}
	}
}
void StudentHandler::PrintStudent()
{
	system("cls");
	StudentData * temp = StdList.getHead();
	int iCnt = StudentData::m_sCounter;
	std::cout << "============================================" << std::endl;
	std::cout << "이름\t번호\t국어\t수학\t영어\t총점" << std::endl;
	for (int i = 1; i < iCnt; i++)
	{
		temp->ShowData();
		temp = temp->m_pNext;
	}
	std::cout << "============================================" << std::endl;
}
void StudentHandler::RandomCreate()
{
	char ch[4];
	int Kor;
	int Mat;
	int Eng;
	for (int i = 0; i < 30; i++)
	{
		ch[0] = rand() % 26 + 65;
		ch[1] = rand() % 26 + 65;
		ch[2] = rand() % 26 + 65;
		ch[3] = 0;
		Kor = rand() % 101;
		Mat = rand() % 101;
		Eng = rand() % 101;
		StdList.AddLink(new StudentData(ch, Kor, Mat, Eng));
	}
	system("cls");
	cout << "생성 완료" << endl;
}
void StudentHandler::SaveFile()
{
	m_fIO.FileSave(StdList);
}
void StudentHandler::LoadFile()
{
	char * szFile = NULL;

	szFile = m_fIO.Datafileload();
	if (szFile != NULL)
	{
		m_fIO.FileLoad(szFile, 1, &StdList);
	}
	else
	{
		system("cls");
		puts("파일 불러오기 실패.");
	}
}