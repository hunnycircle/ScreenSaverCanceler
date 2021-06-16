/* --- Copyright 2021 Hunny-CIRCLE --- */

#define		_FILESYS_C

#include	<shlwapi.h>

#include	"filesys.h"

wchar_t*
filesys_getFilename(const wchar_t *inPath)
{
	return (wchar_t*)PathFindFileName((LPCTSTR)inPath);
}
