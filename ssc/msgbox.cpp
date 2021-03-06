// --- Copyright 2021 Hunny-CIRCLE

#define		_MSGBOX_CPP

#include	<afx.h>
#include	<afxwin.h>
#include	<atlstr.h>

#include	<cstdlib>
#include	<wchar.h>

#include	"debuglog.h"
#include	"errors.h"
#include	"except.h"

#include	"msgbox.h"

#include	"resource.h"

void
msgbox_showMessage(HINSTANCE inInst, RESULTS inErrNo, const wchar_t *inSupp)
{
	msgbox_showResourceMessage(inInst, (DWORD)inErrNo, inSupp);
}

void
msgbox_showResourceMessage(HINSTANCE inInst, DWORD inRSID, const wchar_t *inSupp)
{
	HINSTANCE	inst = NULL;

	CString		cstr;
	CString		msgstr;

	DEBUGLOG_ENTER_FUNCTION();

	try {
		inst = AfxGetResourceHandle();

		if(inInst)AfxSetResourceHandle(inInst);

		if(cstr.LoadString(inInst, inRSID) == FALSE) {
			throw Exception(RESULT_RSRC_NOT_FOUND);
		}

		AfxFormatString2(msgstr, IDS_FMT_RESMSG, cstr, (inSupp) ? inSupp : L"");

		AfxMessageBox(msgstr);

	} catch(...) {
		DEBUGLOG_PRINT_VALUE(L"Resource not found", inRSID);
	}

	if(inst) AfxSetResourceHandle(inst);

	DEBUGLOG_RETURN_FUNCTION();
}

void
msgbox_showSystemMessage(HINSTANCE inInst, DWORD inErrNo, const wchar_t *inSupp)
{
	HINSTANCE	inst = NULL;
	LPVOID		msg = NULL;

	CString		msgstr;

	DEBUGLOG_ENTER_FUNCTION();

	try {
		inst = AfxGetResourceHandle();

		if(FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, inErrNo, MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ),
			(LPTSTR)&msg, 0, NULL) == 0)
		{
			throw Exception(RESULT_FATAL_ERROR);
		}

		if(inInst) AfxSetResourceHandle(inInst);

		AfxFormatString2(msgstr, IDS_FMT_SYSERR, (LPCTSTR)msg, (inSupp) ? inSupp : L"");

		AfxMessageBox(msgstr);

	} catch(...) {
		DEBUGLOG_PRINT_VALUE(L"Failure FormatMessage() ", inErrNo);
	}

	if(inst) AfxSetResourceHandle(inst);

	if(msg) LocalFree(msg);

	DEBUGLOG_RETURN_FUNCTION();
}
