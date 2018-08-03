#include "Chain_of_responsibility.h"
#include <iostream>

using namespace Chain_of_Responsibility;
using namespace std;

int main()
{
	string picture;
	list<int>mode;
	ChangeHandler * handlers[3];
	handlers[0] = new GrayChangeHandler(0);
	handlers[1] = new SoftChangeHandler(1);
	handlers[2] = new RedEyeChangeHandler(2);

	UIPart * uipart = new UIPart;
	uipart->AddChangeHandler(handlers[0]);
	uipart->AddChangeHandler(handlers[1]);
	uipart->AddChangeHandler(handlers[2]);

	picture = uipart->ChangeRequest(mode, "Ä®¶ó »¡°£´« ³¯Ä«·Î¿î ¸ö¸Å");
	cout << picture << endl;
	mode.push_back(0);

	picture = uipart->ChangeRequest(mode, "Ä®¶ó »¡°£´« ³¯Ä«·Î¿î ¸ö¸Å");
	cout << picture << endl;
	mode.push_back(2);

	picture = uipart->ChangeRequest(mode, "Ä®¶ó »¡°£´« ³¯Ä«·Î¿î ¸ö¸Å");
	cout << picture << endl;
	mode.push_back(1);

	picture = uipart->ChangeRequest(mode, "Ä®¶ó »¡°£´« ³¯Ä«·Î¿î ¸ö¸Å");
	cout << picture << endl;

	return 0;
}