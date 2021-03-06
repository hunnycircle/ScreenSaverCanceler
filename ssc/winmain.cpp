// --- Copyright 2021 Hunny-CIRCLE

#define		_WINMAIN_CPP

#include	<afxwin.h>

#include	<cstdlib>
#include	<shellapi.h>
#include	<winuser.h>

#include	"debuglog.h"
#include	"except.h"
#include	"msgbox.h"
#include	"ssc.h"

#include	"winmain.h"
#include	"resource.h"

#define		DEFAULT_INTERVAL	(3)

static UINT			getInterval(UINT);
static ATOM			registFrameWindow(HINSTANCE);
static HWND			initFrameWindow(HINSTANCE);
static LRESULT		mainWindowProc(HWND, UINT, WPARAM, LPARAM);

static UINT
getInterval(UINT inDefault)
{
	UINT	retval = inDefault;
	UINT	val = 0;

	int			argc = 0;
	LPWSTR		*argv = NULL;

	DEBUGLOG_ENTER_FUNCTION();

	if((argv = CommandLineToArgvW(GetCommandLine(), &argc)) != NULL) {

		DEBUGLOG_PRINT_VALUE(L"argc", argc);

		if(argc == 2) {
			DEBUGLOG_PRINT_STRING(L"val", argv[1]);

			if((val = _wtoi(argv[1])) > 0) {
				DEBUGLOG_PRINT_VALUE(L"val", val);
				retval = val;
			}
		}

		LocalFree(argv);
	}

	DEBUGLOG_RETURN_FUNCTION();

	return retval;
}

static ATOM
registFrameWindow(HINSTANCE inInst)
{
	WNDCLASS	wc;

	wc.style         = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc   = (WNDPROC)mainWindowProc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = inInst;
	wc.hIcon         = LoadIcon(inInst, (LPCWSTR)IDI_ICON_APPL);
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_3DFACE+1);
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = CLASS_NAME;

	return RegisterClass(&wc);
}

static HWND
initFrameWindow(HINSTANCE inInst)
{
	return CreateWindow(
		CLASS_NAME, WINDOW_NAME,
//		WS_OVERLAPPED | WS_VISIBLE | WS_SYSMENU,
		0,
		CW_USEDEFAULT, CW_USEDEFAULT, 0, 0,
		NULL,
		NULL,
		inInst,
		NULL
	);
}

static LRESULT
mainWindowProc(HWND inHwnd, UINT inMsg, WPARAM wParam, LPARAM lParam)
{
	switch( inMsg ) 
	{
		case SSC_WM_NOTIFYICON:
		{
			if(lParam == WM_LBUTTONUP) {
				ssc_stateChange(inHwnd, GetModuleHandle(0));
			} else if(lParam == WM_RBUTTONUP) {
				ssc_popup(inHwnd);
			}
		}
		break;

		case WM_TIMER:
		{
			ssc_state();
		}
		break;

		case WM_COMMAND:
		{
			if(LOWORD(wParam) == IDM_EXIT) {
				DestroyWindow(inHwnd);
			}
		}
		return 0;

		case WM_DESTROY:
		{
			PostQuitMessage(0);
		}
		return 0;
	}

	return DefWindowProc(inHwnd, inMsg, wParam, lParam);
}

int WINAPI 
WinMain(HINSTANCE inInst, HINSTANCE inPrevInst, LPSTR inLPCmdLine, int inCmdShow)
{
	int			retval = 0;
	UINT		interval = DEFAULT_INTERVAL;

	HWND		hwnd = NULL;
	MSG			msg;
	UINT_PTR	timer = NULL;

	DEBUGLOG_INIT(L"MYAPP", L"DEBUG.TXT");

	try {
		AfxSetResourceHandle(inInst);

		if(registFrameWindow(inInst) == (ATOM)0) {
			throw SystemException(GetLastError());
		}

		if((hwnd = initFrameWindow(inInst)) == NULL) {
			throw SystemException(GetLastError());
		}

		ssc_init(hwnd, inInst);

		interval = getInterval(interval);

		if((timer = SetTimer(hwnd, NULL, (interval*60*1000), NULL)) == NULL) {
			throw SystemException(GetLastError());
		}

		while(!0) {
			if((retval = GetMessage(&msg, NULL, 0, 0)) >= 0) {
				if(msg.message != WM_QUIT) {
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				} else {
					retval = (int)msg.wParam;
					break;
				}
			} else {
				break;
			}
		}

	} catch(SystemException se) {
		msgbox_showSystemMessage(NULL, se.result, se.message);
		retval = 1;
	} catch(Exception e) {
		msgbox_showMessage(NULL, e.result, e.message);
		retval = 1;
	}

	if(hwnd && timer) KillTimer(hwnd, timer);

	ssc_terminate(hwnd);

	DEBUGLOG_TERMINATE(L"MYAPP");

	return retval;
}
