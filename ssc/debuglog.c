/* --- Copyright 2021 Hunny-CIRCLE --- */

#define		_DEBUGLOG_C

#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

#include	"date.h"
#include	"filesys.h"

#include	"debuglog.h"

#define		MODE_A		L"a+, ccs=UTF-8"
#define		MODE_W		L"w, ccs=UTF-8"

static int	putfunc(const wchar_t*, int, const wchar_t*, const wchar_t*);

static wchar_t		*_filename		= NULL;

int
debuglog_init(const wchar_t *inSource, int inLine, const wchar_t *inProductName, const wchar_t *inFilename)
{
	int			retval		= -1;

	wchar_t		*source;
	FILE		*fp			= NULL;

	DATE_INFO	today;

	if((_filename = _wcsdup( inFilename )) == NULL) {
		goto ERROR_EXCEPTION;
	}

	if(date_getToday(&today) != RESULT_NO_ERROR) {
		goto ERROR_EXCEPTION;
	}

	if(_wfopen_s( &fp, _filename, MODE_W) != 0) {
		fp = NULL;
		goto ERROR_EXCEPTION;
	}

	source = filesys_getFilename(inSource);

	fwprintf(fp, L"%-16s(%4d): Starting %s at %4d/%02d/%02d %02d:%02d:%02d\n",
		(source) ? source : L"(NULL)",
		inLine, inProductName,
		(int)(today.year), (int)(today.month),  (int)(today.day),
		(int)(today.hour), (int)(today.minute), (int)(today.second)
	);

	retval = 0;

ERROR_EXCEPTION:

	if(fp) fclose(fp);

	return retval ;
}

int
debuglog_terminate(const wchar_t *inSource, int inLine, const wchar_t *inProductName)
{
	int			retval		= -1;

	wchar_t		*source;
	FILE		*fp			= NULL;

	DATE_INFO	today;

	if(!_filename) goto ERROR_EXCEPTION;

	if(date_getToday(&today) != RESULT_NO_ERROR) {
		goto ERROR_EXCEPTION;
	}

	if(_wfopen_s(&fp, _filename, MODE_A) != 0) {
		fp = NULL;
		goto ERROR_EXCEPTION;
	}

	source = filesys_getFilename(inSource);

	fwprintf(fp, L"%-16s(%4d): End of %s\n",
		(source) ? source : L"(NULL)",
		inLine, inProductName
	);

	retval = 0;

ERROR_EXCEPTION:

	if(fp) fclose(fp);

	if(_filename) {
		free(_filename);
		_filename = NULL;
	}

	return retval;
}

static int
putfunc(const wchar_t *inSource, int inLine, const wchar_t *inFunction, const wchar_t *inDir)
{
	int			retval	= -1;

	wchar_t		*source;
	FILE		*fp		= NULL;

	if(_wfopen_s(&fp, _filename, MODE_A) != 0) {
		fp = NULL;
		goto ERROR_EXCEPTION;
	}

	source = filesys_getFilename(inSource);

	fwprintf(fp, L"%-16s(%4d): %s %s()\n",
		(source) ? source : L"(NULL)",
		inLine, 
		inDir,
		inFunction
	);

	retval = 0;

ERROR_EXCEPTION:

	if(fp) fclose(fp);

	return retval;
}

int
debuglog_enterFunction(const wchar_t *inSource, int inLine, const wchar_t *inFunction)
{
	int retval = -1;

	if(_filename) {
		retval = putfunc(inSource, inLine, inFunction, L"=>");
	}

	return retval;
}

int
debuglog_returnFunction(const wchar_t *inSource, int inLine, const wchar_t *inFunction)
{
	int retval = -1;

	if(_filename) {
		retval = putfunc(inSource, inLine, inFunction, L"<=");
	}

	return retval;
}

int
debuglog_printString(const wchar_t *inSource, int inLine, const wchar_t *inSubject, const wchar_t *inValue)
{
	int			retval	= -1;

	wchar_t		*source;
	FILE		*fp		= NULL;

	if(!_filename) goto ERROR_EXCEPTION ;

	if(_wfopen_s(&fp, _filename, MODE_A) != 0) {
		fp = NULL;
		goto ERROR_EXCEPTION;
	}

	source = filesys_getFilename(inSource);

	if(inSubject) {
		fwprintf(fp, L"%-16s(%4d): %s=%s\n",
			(source) ? source : L"(NULL)",
			inLine,
			inSubject,
			(inValue) ? inValue : L"(NULL)"
		);
	} else {
		fwprintf(fp, L"%-16s(%4d): %s\n",
			(source) ? source : L"(NULL)",
			inLine,
			(inValue) ? inValue : L"(NULL)"
		);
	}

	retval = 0;

ERROR_EXCEPTION:

	if(fp) fclose(fp);

	return retval;
}


int
debuglog_printValue(const wchar_t *inSource, int inLine, const wchar_t *inSubject, int inValue)
{
	int			retval	= -1;

	wchar_t		*source;
	FILE		*fp		= NULL;

	if(!_filename) goto ERROR_EXCEPTION;

	if(_wfopen_s(&fp, _filename, MODE_A) != 0) {
		fp = NULL;
		goto ERROR_EXCEPTION;
	}

	source = filesys_getFilename(inSource);

	if(inSubject) {
		fwprintf(fp, L"%-16s(%4d): %s=%ld\n",
			(source) ? source : L"(NULL)",
			inLine, inSubject, inValue
		);
	} else {
		fwprintf(fp, L"%-16s(%4d): %ld\n",
			(source) ? source : L"(NULL)",
			inLine, inValue
		);
	}

	retval = 0;

ERROR_EXCEPTION:

	if(fp) fclose(fp);

	return retval;
}
