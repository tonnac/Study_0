#include "WindowClass.h"


GAMESTART
Window win;
// win.Set(WS_POPUPWINDOW);
if (win.SetWindow(hInst))
{
	win.Run();
}
GAMEEND


//
//GAMESTART
//GAMERUN(qwe,800,600)
//GAMEEND