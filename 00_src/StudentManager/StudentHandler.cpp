#include "StudentHandler.h"

using namespace std;


void StudentHandler::MainMenu()
{
	while (1)
	{
		int iSelect;
		MENU type;
		cout << "[�л����� ���α׷�]" << endl;
		cout << "1.�л� �߰�" << endl;
		cout << "2.�л� ����" << endl;
		cout << "3.�л� �˻�" << endl;
		cout << "4.�л� ����" << endl;
		cout << "5.�л� ���" << endl;
		cout << "6.���� �Է�" << endl;
		cout << "7.���� ����" << endl;
		cout << "8.���� �ε�" << endl;
		cout << "9.���α׷� ����" << endl;
		cout << "�Է�: ";
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
			cout << "���α׷��� �����մϴ�." << endl;
			return;
		default:
			system("cls");
			cout << "�߸��� �Է��Դϴ�." << endl;
		}
	}
}
void StudentHandler::AddStudent()
{
	char Name[256];
	int Kor;
	int Mat;
	int Eng;
	cout << "�̸� �Է�: ";
	cin >> Name;
	cout << "���� ���� �Է�: ";
	cin >> Kor;
	cout << "���� ���� �Է�: ";
	cin >> Mat;
	cout << "���� ���� �Է�: ";
	cin >> Eng;
	StdList.AddLink(new StudentData(Name, Kor, Mat, Eng));
	system("cls");
	cout << "�߰� �Ϸ�." << endl;
}
void StudentHandler::SearchStudent()
{
	char SearchName[256];
	int iSelect;
	int num;
	cout << "1. ��ȣ�� �˻�, 2. �̸����� �˻�" << endl;
	cout << "�˻� ��� ����: ";
	cin >> iSelect;
	if (iSelect == 1)
	{
		cout << "��ȣ �Է�: ";
		cin >> num;
		StudentData * Searchdata = StdList.SearchByNumber(num);
		if (Searchdata == nullptr)
		{
			system("cls");
			cout << "�ش��ϴ� ��ȣ�� �������� �ʽ��ϴ�." << endl;
			return;
		}
		else
		{
			system("cls");
			cout << "============================================" << endl;
			cout << "�̸�\t��ȣ\t����\t����\t����\t����" << std::endl;
			Searchdata->ShowData();
			cout << "============================================" << endl;
		}
	}
	else
	{
		cout << "�̸� �Է�: ";
		cin >> SearchName;
		StudentData * Searchdata = StdList.SearchByName(SearchName);
		if (Searchdata == nullptr)
		{
			system("cls");
			cout << "�ش��ϴ� �̸��� �������� �ʽ��ϴ�." << endl;
			return;
		}
		else
		{
			system("cls");
			cout << "============================================" << endl;
			cout << "�̸�\t��ȣ\t����\t����\t����\t����" << std::endl;
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
	cout << "1. ��ȣ�� �˻�, 2. �̸����� �˻�" << endl;
	cout << "�˻� ��� ����: ";
	cin >> iSelect;
	if (iSelect == 1)
	{
		cout << "��ȣ �Է�: ";
		cin >> num;
		StudentData * Searchdata = StdList.SearchByNumber(num);
		if (Searchdata == nullptr)
		{
			system("cls");
			cout << "�ش��ϴ� ��ȣ�� �������� �ʽ��ϴ�." << endl;
			return;
		}
		else
		{
			cout << "============================================" << endl;
			cout << "�̸�\t��ȣ\t����\t����\t����\t����" << std::endl;
			Searchdata->ShowData();
			cout << "============================================" << endl;
			cout << "�ڷḦ �����Ͻðڽ��ϱ�(Y/N):";
			cin >> Sel;
			if (Sel == 'Y' || Sel == 'y')
			{
				StdList.EditLink(Searchdata);
				system("cls");
				cout << "���� �Ϸ�" << endl;
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
		cout << "�̸� �Է�: ";
		cin >> SearchName;
		StudentData * Searchdata = StdList.SearchByName(SearchName);
		if (Searchdata == nullptr)
		{
			system("cls");
			cout << "�ش��ϴ� �̸��� �������� �ʽ��ϴ�." << endl;
			return;
		}
		else
		{
			cout << "============================================" << endl;
			cout << "�̸�\t��ȣ\t����\t����\t����\t����" << std::endl;
			Searchdata->ShowData();
			cout << "============================================" << endl;
			cout << "�ڷḦ �����Ͻðڽ��ϱ�(Y/N):";
			cin >> Sel;
			if (Sel == 'Y' || Sel == 'y')
			{
				StdList.EditLink(Searchdata);
				system("cls");
				cout << "���� �Ϸ�" << endl;
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
	cout << "1. ��ȣ�� �˻�, 2. �̸����� �˻�" << endl;
	cout << "�˻� ��� ����: ";
	cin >> iSelect;
	if (iSelect == 1)
	{
		cout << "��ȣ �Է�: ";
		cin >> num;
		StudentData * Searchdata = StdList.SearchByNumber(num);
		if (Searchdata == nullptr)
		{
			system("cls");
			cout << "�ش��ϴ� ��ȣ�� �������� �ʽ��ϴ�." << endl;
			return;
		}
		else
		{
			cout << "============================================" << endl;
			cout << "�̸�\t��ȣ\t����\t����\t����\t����" << std::endl;
			Searchdata->ShowData();
			cout << "============================================" << endl;
			cout << "�ڷḦ �����Ͻðڽ��ϱ�(Y/N):";
			cin >> Sel;
			if (Sel == 'Y' || Sel == 'y')
			{
				StdList.DelLink(Searchdata);
				system("cls");
				cout << "���� �Ϸ�" << endl;
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
		cout << "�̸� �Է�: ";
		cin >> SearchName;
		StudentData * Searchdata = StdList.SearchByName(SearchName);
		if (Searchdata == nullptr)
		{
			system("cls");
			cout << "�ش��ϴ� �̸��� �������� �ʽ��ϴ�." << endl;
			return;
		}
		else
		{
			cout << "============================================" << endl;
			cout << "�̸�\t��ȣ\t����\t����\t����\t����" << std::endl;
			Searchdata->ShowData();
			cout << "============================================" << endl;
			cout << "�ڷḦ �����Ͻðڽ��ϱ�(Y/N):";
			cin >> Sel;
			if (Sel == 'Y' || Sel == 'y')
			{
				StdList.DelLink(Searchdata);
				system("cls");
				cout << "���� �Ϸ�" << endl;
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
	std::cout << "�̸�\t��ȣ\t����\t����\t����\t����" << std::endl;
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
	cout << "���� �Ϸ�" << endl;
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
		puts("���� �ҷ����� ����.");
	}
}