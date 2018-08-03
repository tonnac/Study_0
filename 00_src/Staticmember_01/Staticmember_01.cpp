#include "Student1.h"

int main(void)
{
	/*cout << "수강생 수:" << Student1::GetCount() << endl;
	Student1 s1("ㅂㅂㅂ", 23);
	Student1 s2("ㅈㅈㅈ", 33);
	Student1 s3("ㅋㅋㅋ", 22);
	s1.Show();
	s2.Show();
	s3.Show();
	cout << "수강생 수:" << Student1::GetCount() << endl;*/

	int i;
	Student1 talent[] = { Student1("ㄱㄱㄱ",11),Student1("ㄴㄴㄴ",22)
		,Student1("ㄷㄷㄷ",33),Student1("ㄹㄹㄹ",44),Student1("aaa",55) };
	int count = Student1::GetCount();
	cout << "나이순:" << endl;
	qsort(talent, count, sizeof(Student1), Student1::CompareAge);
	for (i = 0;i < count;i++)
	{
		talent[i].Show();
	}
	cout << endl << "이름순:" << endl;
	qsort(talent, count, sizeof(Student1), Student1::CompareName);
	for (i = 0;i < count;i++)
	{
		talent[i].Show();
	}
}