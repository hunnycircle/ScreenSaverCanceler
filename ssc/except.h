// --- Copyright 2021 Hunny-CIRCLE

#ifndef		_EXCEPT_H
#define		_EXCEPT_H

#include	<atlstr.h>

#include	<windows.h>
#include	<winerror.h>

#include	"errors.h"

class Exception
{
	public :
		RESULTS		result;
		CString		message;

	public :
		Exception( RESULTS inNo ) { result = inNo; };
		Exception( RESULTS inNo, const wchar_t *inMessage ) { result = inNo; message = inMessage; };
};

class SystemException
{
	public :
		DWORD		result;
		CString		message;

	public :
		SystemException( DWORD inNo ) { result = inNo; } ;
		SystemException( DWORD inNo, const wchar_t *inMessage ) { result = inNo; message = inMessage; };
};

#endif
