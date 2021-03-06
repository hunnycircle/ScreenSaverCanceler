// --- Copyright 2019 Hunny-CIRCLE

#ifndef		_TASKTRAY_H
#define		_TASKTRAY_H

#include	<windows.h>

void	tasktray_addIcon(const HWND, const HINSTANCE, UINT, UINT, UINT, int, int, const wchar_t*);
void	tasktray_changeIcon(const HWND, const HINSTANCE, UINT, UINT, UINT, const wchar_t*);
void	tasktray_removeIcon(const HWND, UINT);

#endif
