/* --- Copyright 2021 Hunny-CIRCLE --- */

#define		_DATE_C

#include	<windows.h>

#include	"errors.h"

#include	"date.h"

RESULTS
date_getToday(DATE_INFO *out)
{
	RESULTS		retval = RESULT_NO_ERROR;

	SYSTEMTIME	systime;

	ZeroMemory(out, sizeof(DATE_INFO));

	GetLocalTime(&systime);

	out->year		= (short)systime.wYear;
	out->month		= (char)systime.wMonth ;
	out->day		= (char)systime.wDay;
	out->hour		= (char)systime.wHour;
	out->minute		= (char)systime.wMinute;
	out->second		= (char)systime.wSecond ;
	out->weekday	= (char)systime.wDayOfWeek+1;

	return retval ;
}
