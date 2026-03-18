#pragma once
#include "pch.h"
#include "Enum.h"

typedef struct tagInfomation {
	float fX, fY;
	float fCX, fCY;
}INFO;


typedef struct tagLinePoint {
	float fX, fY;

	tagLinePoint() { ZeroMemory(this, sizeof(tagLinePoint)); }
	tagLinePoint(float _fX, float _fY) : fX(_fX), fY(_fY) {}
}LINEPOINT;

typedef struct tagLine {
	LINEPOINT tLPoint;
	LINEPOINT tRPoint;
	tagLine() { ZeroMemory(this, sizeof(tagLine)); }
	tagLine(LINEPOINT _lPoint, LINEPOINT _rPoint) : tLPoint(_lPoint), tRPoint(_rPoint) {}
}LINE;

typedef struct tagFrame
{
	int	iStart;
	int iEnd;
	int	iMotion;
	DWORD dwSpeed;
	DWORD dwTime;

}FRAME;

typedef struct tagIsland {
	int iMinX;
	int iMinY;
	int iMaxX;
	int iMaxY;
}ISLAND;

typedef struct tagUIPos {
	float x;
	float y;
}UIPOS;

typedef struct tagSkill {
	SKILLID eId;
	bool bUnlock = false;
	bool bLearnable = false;
	tagSkill() { ZeroMemory(this, sizeof(tagSkill)); }
	tagSkill(SKILLID _id) :eId(_id) {}
	tagSkill(SKILLID _id, bool _bUnlock) :eId(_id), bUnlock(_bUnlock){}
	tagSkill(SKILLID _id, bool _bUnlock, bool _bLean) :eId(_id), bUnlock(_bUnlock), bLearnable(_bLean){}
}SKILL;
 