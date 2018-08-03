#include "StudentHandler.h"

std::istream& operator >> (std::istream&is, StudentHandler::MENU& type)
{
	int num;
	is >> num;
	type = static_cast<StudentHandler::MENU>(num);
	return is;
}
std::istream& operator >> (std::istream&is, StudentHandler::SELECT& type)
{
	int num;
	is >> num;
	type = static_cast<StudentHandler::SELECT>(num);
	return is;
}

void StudentHandler::MainMenu()
{
	while (1)
	{
		MENU type = MENU::ADD;
		std::cout << "[학생관리 프로그램]" << std::endl;
		std::cout << "1.학생 추가" << std::endl;
		std::cout << "2.학생 검색" << std::endl;
		std::cout << "3.학생 수정" << std::endl;
		std::cout << "4.학생 삭제" << std::endl;
		std::cout << "5.학생 출력" << std::endl;
		std::cout << "6.랜덤 입력" << std::endl;
		std::cout << "7.파일 저장" << std::endl;
		std::cout << "8.파일 로드" << std::endl;
		std::cout << "9.프로그램 종료" << std::endl;
		std::cout << "입력: ";
		std::cin >> type;
		switch (type)
		{
		case MENU::ADD:
			AddData();
			break;
		case MENU::SEARCH:
			SearchData(0);
			break;
		case MENU::EDIT:
			EditData();
			break;
		case MENU::DELETE:
			DeleteData();
			break;
		case MENU::PRINT:
			PrintData();
			break;
		case MENU::RANDOM:
			RandomInput();
			break;
		case MENU::SAVE:
			SaveFile();
			break;
		case MENU::LOAD:
			LoadFile();
			break;
		case MENU::EXIT:
			std::cout << "프로그램을 종료합니다." << std::endl;
			return;
		default:
			system("cls");
			std::cout << "잘못된 입력입니다." << std::endl;
		}
	}
}
void StudentHandler::AddData()
{
	char cName[256];
	int iKor;
	int iMat;
	int iEng;
	std::cout << "이름입력: ";
	std::cin >> cName;
	std::cout << "국어점수 입력: ";
	std::cin >> iKor;
	std::cout << "수학점수 입력: ";
	std::cin >> iMat;
	std::cout << "영어점수 입력: ";
	std::cin >> iEng;
	m_dStd.AddLink(new StudentData(cName, iKor, iMat, iEng));
	system("cls");
	std::cout << "추가 완료되었습니다." << std::endl;
}
void StudentHandler::SearchData(const int & DataType)
{
	while (1)
	{
		SELECT type = SELECT::NAME;
		std::cout << "검색방법 선택" << std::endl;
		std::cout << "1.이름으로 검색, 2.번호로 검색" << std::endl;
		std::cout << "선택: ";
		std::cin >> type;
		switch (type)
		{
		case SELECT::NAME:
			SearchName(DataType);
			return;
		case SELECT::NUMBER:
			SearchNumber(DataType);
			return;
		default:
			system("cls");
			std::cout << "잘못된 입력입니다." << std::endl;
		}
	}
}
void StudentHandler::EditData()
{
	SearchData(1);
}
void StudentHandler::DeleteData()
{
	SearchData(2);
}
void StudentHandler::PrintData()
{
	system("cls");
	m_dStd.PrintAllData();
}
void StudentHandler::RandomInput()
{
	char cName[256];
	int iKor;
	int iEng;
	int iMat;
	for (int i = 0; i < 15; i++)
	{
		cName[0] = rand() % 26 + 65;
		cName[1] = rand() % 26 + 65;
		cName[2] = rand() % 26 + 65;
		cName[3] = 0;
		iKor = rand() % 101;
		iMat = rand() % 101;
		iEng = rand() % 101;
		m_dStd.AddLink(new StudentData(cName, iKor, iMat, iEng));
	}
	system("cls");
	std::cout << "입력이 완료되었습니다." << std::endl;
}
void StudentHandler::SaveFile()
{
	m_fIO.FileSave(m_dStd);
}
void StudentHandler::LoadFile()
{
	char * szFile = NULL;

	szFile = m_fIO.Datafileload();
	if (szFile != NULL)
	{
		int Mode = m_fIO.Binarytextload(szFile);
		m_fIO.FileLoad(szFile, Mode,m_dStd);
	}
	else
	{
		system("cls");
		puts("파일 불러오기 실패.");
	}
}

void StudentHandler::SearchName(const int & type)
{
	char cName[256];
	std::cout << "이름입력: ";
	std::cin >> cName;
	std::vector<StudentData*>::iterator iter;
	iter = m_dStd.SearchByName(cName);
	if (iter == m_dStd.getEnd())
	{
		system("cls");
		std::cout << "해당하는 이름이 존재하지 않습니다." << std::endl;
		return;
	}
	system("cls");
	(*iter)->OneShow();
	if (type == 1)
	{
		m_dStd.EditLink(iter);
		return;
	}
	else if (type == 2)
	{
		char YN;
		std::cout << "정말로 삭제하시겠습니까?(Y/N): ";
		std::cin >> YN;
		if (YN == 'Y' || YN == 'y')
		{
			m_dStd.DelLink(iter);
			system("cls");
			std::cout << "삭제되었습니다." << std::endl;
			return;
		}
		else if (YN == 'N' || YN == 'n')
		{
			system("cls");
			std::cout << "취소되었습니다." << std::endl;
			return;
		}
		else
		{
			system("cls");
			std::cout << "잘못된 입력입니다." << std::endl;
			return;
		}
	}
}
void StudentHandler::SearchNumber(const int & type)
{
	int iNumber;
	std::cout << "번호입력: ";
	std::cin >> iNumber;
	std::vector<StudentData*>::iterator iter;
	iter = m_dStd.SearchByNum(iNumber);
	if (iter == m_dStd.getEnd())
	{
		system("cls");
		std::cout << "해당하는 번호가 존재하지 않습니다." << std::endl;
		return;
	}
	system("cls");
	(*iter)->OneShow();
	if (type == 1)
	{
		m_dStd.EditLink(iter);
		return;
	}
	else if (type == 2)
	{
		char YN;
		std::cout << "정말로 삭제하시겠습니까?(Y/N): ";
		std::cin >> YN;
		if (YN == 'Y' || YN == 'y')
		{
			m_dStd.DelLink(iter);
			system("cls");
			std::cout << "삭제되었습니다." << std::endl;
			return;
		}
		else if (YN == 'N' || YN == 'n')
		{
			system("cls");
			std::cout << "취소되었습니다." << std::endl;
			return;
		}
		else
		{
			system("cls");
			std::cout << "잘못된 입력입니다." << std::endl;
			return;
		}
	}
}