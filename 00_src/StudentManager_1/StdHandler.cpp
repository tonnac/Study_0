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
		std::cout << "[�л����� ���α׷�]" << std::endl;
		std::cout << "1.�л� �߰�" << std::endl;
		std::cout << "2.�л� ����" << std::endl;
		std::cout << "3.�л� �˻�" << std::endl;
		std::cout << "4.�л� ����" << std::endl;
		std::cout << "5.�л� ���" << std::endl;
		std::cout << "6.���� �Է�" << std::endl;
		std::cout << "7.���� ����" << std::endl;
		std::cout << "8.���� �ε�" << std::endl;
		std::cout << "9.���α׷� ����" << std::endl;
		std::cout << "�Է�: ";
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
			std::cout << "���α׷��� �����մϴ�." << std::endl;
			return;
		default:
			system("cls");
			std::cout << "�߸��� �Է��Դϴ�." << std::endl;
		}
	}
}
void StdHandler::AddStudent()
{
	char _Name[256];
	int Kor;
	int Mat;
	int Eng;
	std::cout << "�̸� �Է�: ";
	std::cin >> _Name;
	std::cout << "�������� �Է�: ";
	std::cin >> Kor;
	std::cout << "�������� �Է�: ";
	std::cin >> Mat;
	std::cout << "�������� �Է�: ";
	std::cin >> Eng;
	m_dList.AddLink(*new StudentData(_Name, Kor, Mat, Eng));
	system("cls");
	std::cout << "�л��� �߰��Ǿ����ϴ�." << std::endl;
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

