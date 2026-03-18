#pragma once
#include "pch.h"

#define			WINCX			1050
#define			WINCY			600

#define			PURE			= 0 

#define			OBJ_NOEVENT		0
#define			OBJ_DEAD		1
#define			UI_NOEVENT		0
#define			UI_DEAD			1

#define			PI				3.141592f

#define			VK_MAX			0xff

#define			OFFSET_MAX_X	625
#define			OFFSET_MIN_X	425

#define			OFFSET_MAX_Y	400
#define			OFFSET_MIN_Y	200

//타일 몇 개 깔것인가?
#define		TILEX		40
#define		TILEY		40

//타일 크기
#define			TILECX		56
#define			TILECY		56

#define			BASE_SIZE	56

#define			WEAPON_SLOT_CNT		7
#define			Item_SLOT_CNT		24


extern HWND	 g_hWnd;
extern bool bCheckFPS;
