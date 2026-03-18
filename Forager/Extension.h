#pragma once
#include "Define.h"
#include <cstdlib> 
#include <ctime> 


template<typename T>
void SafeDelete(T& p) {
	if (p) {
		delete p;
		p = nullptr;
	}
}

struct DeleteObj
{
	template<typename T>
	void	operator()(T& p)
	{
		if (p)
		{
			delete p;
			p = nullptr;
		}
	}
};

struct DeleteMap
{
	template<typename T>
	void	operator()(T& MyPair)
	{
		if (MyPair.second)
		{
			delete MyPair.second;
			MyPair.second = nullptr;
		}
	}
};

struct tagFinder
{
	tagFinder(const TCHAR* pTag) : m_pTag(pTag) {}

	template<typename T>
	bool	operator()(T& MyPair)
	{
		return !lstrcmp(MyPair.first, m_pTag);
	}


	const TCHAR* m_pTag;
};


inline bool CheckScreenOut(const RECT& rect)
{
	return rect.left <= 0 || rect.right >= WINCX || rect.top <= 0 || rect.bottom >= WINCY;
}

namespace Random
{
	inline void InitRandom()
	{
		srand(static_cast<unsigned int>(time(nullptr)));
	}
	inline int GetInt(int min, int max)
	{
		return min + (rand() % (max - min + 1));
	}
}

//흰색 숫자
inline const TCHAR* NumToTchar(int _n)
{
	static const TCHAR* arrayType[] = {
		L"0",
		L"1",
		L"2",
		L"3",
		L"4",
		L"5",
		L"6",
		L"7",
		L"8",
		L"9",
	};
	return arrayType[_n];
}

//노란색 숫자
inline const TCHAR* NumToTchar2(int _n)
{
	static const TCHAR* arrayType[] = {
		L"Y0",
		L"Y1",
		L"Y2",
		L"Y3",
		L"Y4",
		L"Y5",
		L"Y6",
		L"Y7",
		L"Y8",
		L"Y9",
	};
	return arrayType[_n];
}


inline const TCHAR* enumTotchar_Equip(int _eq)
{
	static const TCHAR* arrayType[] = {
	L"Pickax1",
	//L"Pickax1",
	//L"Pickax1",

	};
	return arrayType[_eq];
}

inline const TCHAR* enumTotchar_Equip_Kr(int _eq)
{
	static const TCHAR* arrayType[] = {
	L"기본 곡괭이",
	//L"Pickax1",
	//L"Pickax1",

	};
	return arrayType[_eq];
}

inline const TCHAR* enumTotchar_Item(int _it)
{
	static const TCHAR* arrayType[] = {
	L"Berry_Fruit",
	L"Coal",
	L"Gold_Ore",
	L"Iron_Ore",
	L"Stone",
	L"Wood",
	L"Sand",
	L"Smelt_Gold",
	L"Smelt_Iron",
	L"Brick",
	L"Citrus_Drop",
	L"Fish",
	L"Cook_Fish",


	};
	return arrayType[_it];
}


inline const TCHAR* enumTotchar_Item_Kr(int _it)
{
	static const TCHAR* arrayType[] = {
	L"열매",
	L"석탄",
	L"금광석",
	L"철광석",
	L"돌",
	L"나무",
	L"모래",
	L"금괴",
	L"철",
	L"벽돌",
	L"감귤",
	L"물고기",
	L"구운 물고기",

	};
	return arrayType[_it];
}



inline const int* eunmTointArr_Furnace_ItemCost(int _type) {
	//베리 석탄 금광석 철광석 돌 나무 모래 금괴 철괴 벽돌 감귤 물고기 구운고기
	static int coal[] =			{ 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 };	//석탄
	static int smeltGold[] =	{ 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };	//금괴
	static int smeltIron[] =	{ 0, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };	//철
	static int brick[] =		{ 0, 1, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 };	// 벽돌
	static int cookFish[] =		{ 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 };	//구운고기


	static int dummy[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100, 100,100 };

	static const int* arrayType[] = {
		dummy,
		coal,
		dummy,dummy,dummy,dummy,dummy,
		smeltGold,
		smeltIron,
		brick,
		dummy,dummy,
		cookFish
	};

	return arrayType[_type];
}

//스킬 이미지중에서 몇번 째 모션인지
inline const int enumToint_Skill(int _sk) {
	static const int arrayType[] = {
		15, 14, 13, 12,		12, 13, 14, 15,
		11, 10, 9, 8,		8, 9, 10, 11,
		7, 6, 5, 4,			4, 5, 6, 7,
		3, 2, 1, 0,			0, 1, 2, 3,
		
		3, 2, 1, 0,			0, 1, 2, 3,
		7, 6, 5, 4,			4, 5, 6, 7,
		11, 10, 9, 8,		8, 9, 10, 11,
		15, 14, 13, 12,		12, 13, 14, 15
	};
	return arrayType[_sk];
}

//건물 버튼 UI
inline const TCHAR* enumTotchar_Structure(int _type) {
	static const TCHAR* arrayType[] = {
		L"Main_Industry",
		L"Main_Farming",
		L"Main_Economy",
		L"Main_Magic",
	};
	return arrayType[_type];
}

//서브 건설 버튼 UI
inline const TCHAR* enumTotchar_Sub_Structure(int _type, int _sub) {
	int iIndex = _type * 5 + _sub;

	static const TCHAR* arrayType[] = {
		L"Sub_I_0", L"Sub_I_1", L"Sub_I_2", L"Sub_I_3", L"Sub_I_4",//L"Sub_I_Empty",
		L"Sub_F_0", L"Sub_F_1", L"Sub_F_2", L"Sub_F_3", L"Sub_F_4",//L"Sub_F_Empty",
		L"Sub_E_0", L"Sub_E_1", L"Sub_E_2", L"Sub_E_3", L"Sub_E_4",//L"Sub_E_Empty",
		L"Sub_M_0", L"Sub_M_1", L"Sub_M_2", L"Sub_M_3", L"Sub_M_4",//L"Sub_M_Empty",
	};
	return arrayType[iIndex];
}

//프리뷰에 사용하는 건설아이콘
inline const TCHAR* enumTotchar_BuildingIcon(int _type) {
	static const TCHAR* arrayType[] = {
		L"SI_I_0", L"SI_I_1", L"SI_I_2", L"SI_I_3", L"SI_I_4",
		L"SI_F_0", L"SI_F_1", L"SI_F_2", L"SI_F_3", L"SI_F_4",
		L"SI_E_0", L"SI_E_1", L"SI_E_2", L"SI_E_3", L"SI_E_4",
		L"SI_M_0", L"SI_M_1", L"SI_M_2", L"SI_M_3", L"SI_M_4"
	};
	return arrayType[_type];
}


inline const int* eunmTointArr_BuildingCost(int _type) {
						//베리 석탄 금광석 철광석 돌 나무 모래 금괴 철괴 벽돌
	static int I_0[] = {  0,   0,	 0,    0,   3,  0,  0,   0,  0 , 0		,0 ,0 ,0 };	//용광로
	static int I_1[] = {  0,   0,	 0,    0,   0,  0,  0,   0,  3 , 3		,0 ,0 ,0 };	//모루
	static int I_2[] = {  0,   0,	 0,    0,   3,  0,  5,   0,  0 , 0		,0 ,0 ,0 };	//재봉소

	static int F_0[] = {  0,   0,	 0,    0,   0,  1,  0,   0,  0 , 0		,0 ,0 ,0 };	//다리
	static int F_1[] = {  1,   0,	 0,    0,   0,  0,  0,   0,  0 , 0		,0 ,0 ,0 };	//통발

	static int E_0[] = {  0,   0,	 3,    0,   2,  5,  0,   0,  0 , 0		,0 ,0 ,0 };	//은행
	static int E_1[] = {  10,  0,	 0,    0,   3,  0,  0,   1,  0 , 0		,0 ,0 ,0 };	//시장
	static int E_2[] = {  0,   0,	 0,    0,   5,  5,  0,   2,  0 , 0		,0 ,0 ,0 };	//금고
	static int E_3[] = {  0,   0,	 0,    0,   0,  0,  0,   0,  5 , 5		,0 ,0 ,0 };	//등대
	static int E_4[] = {  0,   0,	 0,    0,   0,  0,  0,   5,  0 , 0		,0 ,0 ,0 };	//슬롯머신

	static int dummy[] = { 0,   0,	 0,    0,   0,  0,  0,   0,  0 , 0		,0 ,0 ,0 };
	static int test[] =  { 0,	0,	 0,    0,   0,  0,  0,   0,  0 , 0		,0 ,0 ,0 };

	static const int* arrayType[] = {
		//test,test,test,test,test,
		//test,test,test,test,test,
		//test,test,test,test,test,
		//test,test,test,test,test,

		I_0, I_1, I_2,	dummy,dummy,
		F_0, F_1,	dummy,dummy,dummy,
		E_0, E_1, E_2, E_3, E_4,
		dummy,dummy,dummy,dummy,dummy,
	};

	return arrayType[_type];
}


//섬들 가격
inline const int eunmToint_IslandsCost(int type) {

	static const int arrayType[] = {
		0,
		50,
		500,

		1000,
		1500,
		2000,

		3000,
		5000,
		7000,
	};

	return arrayType[type];
}


inline const float Heal_Item_Power(int type) {
	static const float arrayType[] = {
		//베리, 감귤, 물고기 ,구운 물고기
		10,0,0,0,0,0,0 ,0,0,0 ,10, 30 ,60
	};
	return arrayType[type];
}