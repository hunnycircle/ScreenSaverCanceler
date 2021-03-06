// --- Copyright 2021 Hunny-CIRCLE

#define		_SSC_CPP

#include	<atlstr.h>
#include	<windows.h>

#include	<cstdlib>
#include	<cstring>

#include	"debuglog.h"
#include	"except.h"
#include	"tasktray.h"
#include	"winmain.h"

#include	"ssc.h"
#include	"resource.h"

#define		NOTIFY_RETRY			(20)
#define		NOTIFY_INTERVAL			(2000)

static bool		_run = true;
static HMENU	_menu = NULL;

void
ssc_init(HWND inHwnd, HINSTANCE inInst)
{
	DEBUGLOG_ENTER_FUNCTION();

	if((_menu = LoadMenu(inInst, MAKEINTRESOURCE(IDR_POPUP_MENU))) == NULL) {
		throw SystemException(GetLastError(), L"IDR_POPUP_MENU");
	}

	tasktray_addIcon(inHwnd, inInst, IDI_ICON_ON, IDI_ICON_ON, SSC_WM_NOTIFYICON, NOTIFY_RETRY, NOTIFY_INTERVAL, WINDOW_NAME);

	DEBUGLOG_RETURN_FUNCTION();
}

void
ssc_terminate(HWND inHwnd)
{
	DEBUGLOG_ENTER_FUNCTION();

	if(_menu) {
		DestroyMenu(_menu);
		_menu = NULL;
	}

	tasktray_removeIcon(inHwnd, IDI_ICON_ON);

	DEBUGLOG_RETURN_FUNCTION();
}

void
ssc_state()
{
	INPUT	input[1];

	DEBUGLOG_ENTER_FUNCTION();

	if(!_run) return;

	ZeroMemory(input, sizeof(input));

	input[0].type = INPUT_MOUSE;
	input[0].mi.dwFlags = MOUSEEVENTF_MOVE;
	input[0].mi.dx = 0;
	input[0].mi.dy = 0;

	SendInput(1, input, sizeof(input));

	DEBUGLOG_RETURN_FUNCTION();
}

void
ssc_stateChange(HWND inHwnd, HINSTANCE inInst)
{
	UINT	icon = 0;

	DEBUGLOG_ENTER_FUNCTION();

	_run = !_run;

	DEBUGLOG_PRINT_VALUE(L"_run", _run);

	icon = (_run) ? IDI_ICON_ON : IDI_ICON_OFF;

	tasktray_changeIcon(inHwnd, inInst, IDI_ICON_ON, icon, SSC_WM_NOTIFYICON, WINDOW_NAME);

	DEBUGLOG_RETURN_FUNCTION();
}

void
ssc_popup(HWND inHwnd)
{
	POINT		point;

	DEBUGLOG_ENTER_FUNCTION();

	ZeroMemory(&point, sizeof(point));

	SetForegroundWindow(inHwnd);
	SetFocus(inHwnd);

	GetCursorPos(&point);

	DEBUGLOG_PRINT_VALUE(L"x", point.x);
	DEBUGLOG_PRINT_VALUE(L"y", point.y);

	TrackPopupMenuEx(GetSubMenu(_menu, 0), TPM_CENTERALIGN | TPM_VCENTERALIGN | TPM_RIGHTBUTTON, point.x, point.y, inHwnd, NULL);

	PostMessage(inHwnd, WM_NULL, 0, 0);

	DEBUGLOG_RETURN_FUNCTION();
}
