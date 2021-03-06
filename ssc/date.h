/* --- Copyright 2021 Hunny-CIRCLE --- */

#ifndef		_DATE_H
#define		_DATE_H

#include	"errors.h"

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct {
	short		year;
	char		month;
	char		day;
	char		hour;
	char		minute;
	char		second;
	char		weekday;
} DATE_INFO;

RESULTS		date_getToday(DATE_INFO*);

#ifdef	__cplusplus
}
#endif

#endif
