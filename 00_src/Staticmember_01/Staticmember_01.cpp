#include "Student1.h"

int main(void)
{
	/*cout << "������ ��:" << Student1::GetCount() << endl;
	Student1 s1("������", 23);
	Student1 s2("������", 33);
	Student1 s3("������", 22);
	s1.Show();
	s2.Show();
	s3.Show();
	cout << "������ ��:" << Student1::GetCount() << endl;*/

	int i;
	Student1 talent[] = { Student1("������",11),Student1("������",22)
		,Student1("������",33),Student1("������",44),Student1("aaa",55) };
	int count = Student1::GetCount();
	cout << "���̼�:" << endl;
	qsort(talent, count, sizeof(Student1), Student1::CompareAge);
	for (i = 0;i < count;i++)
	{
		talent[i].Show();
	}
	cout << endl << "�̸���:" << endl;
	qsort(talent, count, sizeof(Student1), Student1::CompareName);
	for (i = 0;i < count;i++)
	{
		talent[i].Show();
	}
}