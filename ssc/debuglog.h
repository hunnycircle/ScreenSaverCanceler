/* --- Copyright 2021 Hunny-CIRCLE --- */

#ifndef		_DEBUGLOG_H
#define		_DEBUGLOG_H

#include	<tchar.h>

#ifdef	__cplusplus
extern "C" {
#endif

int			debuglog_init(const wchar_t*, int, const wchar_t*, const wchar_t*);
int			debuglog_terminate(const wchar_t*, int, const wchar_t*);
int			debuglog_enterFunction(const wchar_t*, int, const wchar_t*);
int			debuglog_returnFunction(const wchar_t*, int, const wchar_t*);
int			debuglog_printString(const wchar_t*, int, const wchar_t*, const wchar_t*);
int			debuglog_printValue(const wchar_t*, int, const wchar_t*, int);

#ifdef	USE_DEBUGLOG
#define		DEBUGLOG_INIT(s,p)				debuglog_init(_T(__FILE__), __LINE__, (const wchar_t*)s, (const wchar_t*)p)
#define		DEBUGLOG_TERMINATE(s)			debuglog_terminate(_T(__FILE__), __LINE__, (const wchar_t*)s)
#define		DEBUGLOG_ENTER_FUNCTION()		debuglog_enterFunction(_T(__FILE__), __LINE__, _T(__FUNCTION__))
#define		DEBUGLOG_RETURN_FUNCTION()		debuglog_returnFunction(_T(__FILE__), __LINE__, _T(__FUNCTION__))
#define		DEBUGLOG_PRINT_STRING(s,p)		debuglog_printString(_T(__FILE__), __LINE__, (const wchar_t*)s, (const wchar_t*)p)
#define		DEBUGLOG_PRINT_VALUE(s,n)		debuglog_printValue(_T(__FILE__), __LINE__, (const wchar_t*)s, (long)n)
#else
#define		DEBUGLOG_INIT(s,p)
#define		DEBUGLOG_TERMINATE(s)
#define		DEBUGLOG_ENTER_FUNCTION()
#define		DEBUGLOG_RETURN_FUNCTION()
#define		DEBUGLOG_PRINT_STRING(s,p)
#define		DEBUGLOG_PRINT_VALUE(s,n)
#endif

#ifdef	__cplusplus
}
#endif

#endif
