
#include <iostream>
#include <memory>

using namespace std;

int main()
{
	shared_ptr<int> a = make_shared<int>(349);

	weak_ptr<int> d = a;

	unique_ptr<int> b = make_unique<int>(30);

	int * ptr = b.get();

	int * ptr1 = a.get();

	auto el = d.lock().get();

	shared_ptr<int> e = std::move(a);


	b.reset();

	*a = 30;
	
	d.reset();

	a.reset();
	
	if (d.expired())
	{
		d.reset();
	}

	return 0;
}