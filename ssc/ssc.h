// --- Copyright 2021 Hunny-CIRCLE

#ifndef		_SSC_H
#define		_SSC_H

#include	<windows.h>

#define		SSC_WM_NOTIFYICON		(WM_USER + 100)

void	ssc_init(HWND, HINSTANCE);
void	ssc_terminate(HWND);
void	ssc_state(void);
void	ssc_stateChange(HWND, HINSTANCE);
void	ssc_popup(HWND);

#endif
