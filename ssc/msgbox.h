// --- Copyright 2021 Hunny-CIRCLE

#ifndef	_MSGBOX_H
#define	_MSGBOX_H

#include	<windows.h>
#include	<wchar.h>

#include	"errors.h"

void	msgbox_showMessage(HINSTANCE, RESULTS, const wchar_t*);
void	msgbox_showResourceMessage(HINSTANCE, DWORD, const wchar_t*);
void	msgbox_showSystemMessage(HINSTANCE, DWORD, const wchar_t*);

#endif
