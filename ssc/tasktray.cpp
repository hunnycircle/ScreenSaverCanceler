// --- Copyright 2021 Hunny-CIRCLE

#define		_TASKTRAY_CPP

#include	<windows.h>

#include	<cstdlib>
#include	<cstring>
#include	<shellapi.h>

#include	"errors.h"
#include	"except.h"

#include	"tasktray.h"

void
tasktray_addIcon(const HWND inHwnd, const HINSTANCE inInst, UINT inID, UINT inIcon, UINT inMessageID, int inRetry, int inInterval, const wchar_t *inTips)
{
	int		i;

	NOTIFYICONDATA		nid;

	ZeroMemory(&nid, sizeof(NOTIFYICONDATA));

	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hWnd = inHwnd;
	nid.uID = inID;
	nid.uFlags = (NIF_MESSAGE | NIF_ICON | NIF_TIP);
	nid.uCallbackMessage = inMessageID;
	nid.hIcon = LoadIcon(inInst, (LPCTSTR)inIcon);
	wcsncpy_s(nid.szTip, (sizeof(nid.szTip)/sizeof(wchar_t)), inTips, _TRUNCATE);

	for(i=0; i < inRetry; i++) {
		if(Shell_NotifyIcon(NIM_ADD, &nid) == TRUE) {
			break;
		} else {
			Sleep(inInterval);
		}
	}

	if(i >= inRetry) {
		throw SystemException(GetLastError());
	}
}

void
tasktray_changeIcon(const HWND inHwnd, const HINSTANCE inInst, UINT inID, UINT inIcon, UINT inMessageID, const wchar_t *inTips)
{
	NOTIFYICONDATA		nid;

	ZeroMemory(&nid, sizeof(NOTIFYICONDATA));

	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hWnd = inHwnd;
	nid.uID = inID;
	nid.uFlags = (NIF_MESSAGE | NIF_ICON | NIF_TIP);
	nid.uCallbackMessage = inMessageID;
	nid.hIcon = LoadIcon(inInst, (LPCTSTR)inIcon);
	wcsncpy_s(nid.szTip, (sizeof(nid.szTip)/sizeof(wchar_t)), inTips, _TRUNCATE);

	Shell_NotifyIcon(NIM_MODIFY, &nid);
}

void
tasktray_removeIcon(const HWND inHwnd, UINT inID)
{
	NOTIFYICONDATA		nid;

	ZeroMemory(&nid, sizeof(NOTIFYICONDATA));

	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hWnd = inHwnd;
	nid.uID = inID;

	Shell_NotifyIcon(NIM_DELETE, &nid);

	if(nid.hIcon) {
		DestroyIcon(nid.hIcon);
	}
}
