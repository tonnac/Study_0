#include "StdHandler.h"

std::istream& operator>>(std::istream&is, StdHandler::MENU& type)
{
	int num;
	is >> num;
	type = static_cast<StdHandler::MENU>(num);
	return is;
}

void StdHandler::MainMenu()
{
	while (1)
	{
		MENU type;
		std::cout << "[학생관리 프로그램]" << std::endl;
		std::cout << "1.학생 추가" << std::endl;
		std::cout << "2.학생 수정" << std::endl;
		std::cout << "3.학생 검색" << std::endl;
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
			std::cout << "프로그램을 종료합니다." << std::endl;
			return;
		default:
			system("cls");
			std::cout << "잘못된 입력입니다." << std::endl;
		}
	}
}
void StdHandler::AddStudent()
{
	char _Name[256];
	int Kor;
	int Mat;
	int Eng;
	std::cout << "이름 입력: ";
	std::cin >> _Name;
	std::cout << "국어점수 입력: ";
	std::cin >> Kor;
	std::cout << "수학점수 입력: ";
	std::cin >> Mat;
	std::cout << "영어점수 입력: ";
	std::cin >> Eng;
	m_dList.AddLink(*new StudentData(_Name, Kor, Mat, Eng));
	system("cls");
	std::cout << "학생이 추가되었습니다." << std::endl;
}
void StdHandler::EditStudent()
{

}
void StdHandler::DeleteStudent()
{

}
void StdHandler::SearchStudent()
{

}
void StdHandler::PrintStudent()
{

}
void StdHandler::RandomCreate()
{

}
void StdHandler::SaveFile()
{

}
void StdHandler::LoadFile()
{

}

