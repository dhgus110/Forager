#pragma once
#include "pch.h"
#include "BaseStruct.h"
#include "Define.h"


namespace UIPos {
	const UIPOS MenuTapIn = { WINCX * 0.5f - 187.f, 10.f };

	const UIPOS ExpBarOut = { (float)WINCX * 0.5f - 350.f, -35.f };

	inline const UIPOS SubMenu(int _n)
	{
		static const UIPOS arrayType[] = {
			{(WINCX * 0.5f) - 187.f , 10.f},
			{(WINCX * 0.5f) - 112.2f, 10.f},
			{(WINCX * 0.5f) - 37.f , 10.f},
			{(WINCX * 0.5f) + 37.4f , 10.f},
			{(WINCX * 0.5f) + 112.2f, 10.f},
		};
		return arrayType[_n];
	}

	inline const UIPOS SubMenuIconSize(int _n)
	{
		static const UIPOS arrayType[] = {
			{58.f,81.f},
			{81.f,83.f},
			{62.f,83.f},
			{116.f,82.f},
			{74.f,86.f},
		};
		return arrayType[_n];
	}


	//92 만큼씩 이동
	inline const UIPOS Item_Slot(int _n)
	{
		static const UIPOS arrayType[] = {
			{169.f,210.f},{261.f,210.f},{353.f,210.f},{445.f,210.f},{537.f,210.f},{629.f,210.f},{721.f,210.f},{813.f,210.f},
			{169.f,302.f},{261.f,302.f},{353.f,302.f},{445.f,302.f},{537.f,302.f},{629.f,302.f},{721.f,302.f},{813.f,302.f},
			{169.f,394.f},{261.f,394.f},{353.f,394.f},{445.f,394.f},{537.f,394.f},{629.f,394.f},{721.f,394.f},{813.f,394.f},
		};
		return arrayType[_n];
	}
	const UIPOS ItemToolTip = { 791.f, 125.f };


	const UIPOS WeaponInven = { 234.f, 130.f };
	const UIPOS AccesoryInven = { 234.f, 260.f };
	const UIPOS SkillBtn = { 600.f, 300.f };
	const UIPOS WordIslandCnt = { 600.f, 420.f };


	inline const UIPOS Weapon_Slot(int _n)
	{
		static const UIPOS arrayType[] = {
			{248.f,145.f},
			{329.f,145.f},
			{410.f,145.f},
			{489.f,145.f},
			{569.f,145.f},
			{649.f,145.f},
			{729.f,145.f},
		};
		return arrayType[_n];
	}




	inline const UIPOS SkillPos(int _n)
	{
		static const UIPOS arrayType[] = {
			{273.f, 48.f}	, { 337.f, 48.f } , { 401.f, 48.f } , { 465.f, 48.f } , { 529.f, 48.f } , { 593.f, 48.f } , { 657.f, 48.f } , { 721.f, 48.f } ,
			{ 273.f, 112.f }, {337.f, 112.f }, { 401.f, 112.f }, { 465.f, 112.f }, { 529.f, 112.f }, { 593.f, 112.f }, { 657.f, 112.f }, { 721.f, 112.f },
			{ 273.f, 176.f }, {337.f, 176.f }, { 401.f, 176.f }, { 465.f, 176.f }, { 529.f, 176.f }, { 593.f, 176.f }, { 657.f, 176.f }, { 721.f, 176.f },
			{ 273.f, 240.f }, {337.f, 240.f }, { 401.f, 240.f }, { 465.f, 240.f }, { 529.f, 240.f }, { 593.f, 240.f }, { 657.f, 240.f }, { 721.f, 240.f },
			{ 273.f, 304.f }, {337.f, 304.f }, { 401.f, 304.f }, { 465.f, 304.f }, { 529.f, 304.f }, { 593.f, 304.f }, { 657.f, 304.f }, { 721.f, 304.f },
			{ 273.f, 368.f }, {337.f, 368.f }, { 401.f, 368.f }, { 465.f, 368.f }, { 529.f, 368.f }, { 593.f, 368.f }, { 657.f, 368.f }, { 721.f, 368.f },
			{ 273.f, 432.f }, {337.f, 432.f }, { 401.f, 432.f }, { 465.f, 432.f }, { 529.f, 432.f }, { 593.f, 432.f }, { 657.f, 432.f }, { 721.f, 432.f },
			{ 273.f, 496.f }, {337.f, 496.f }, { 401.f, 496.f }, { 465.f, 496.f }, { 529.f, 496.f }, { 593.f, 496.f }, { 657.f, 496.f }, { 721.f, 496.f },
		};
		return arrayType[_n];
	}

	// 메인 건설 버튼 (5번째들 위치가 기본 위치)
	inline const UIPOS Main_Structure_Button(int type, int pos)
	{

		int iIndex = (5 * type) + pos;

		static const UIPOS arrayType[] = {
			{750.f, 50.f},{750.f, 50.f},{750.f, 50.f},{750.f, 50.f},{750.f, 50.f},
			{750.f, 345.f},{750.f, 120.f},{750.f, 120.f},{750.f, 120.f},{750.f, 120.f},
			{750.f, 415.f},{750.f, 415.f},{750.f, 190.f},{750.f, 190.f},{750.f, 190.f},
			{750.f, 490.f},{750.f, 490.f},{750.f, 490.f},{750.f, 260.f},{750.f, 260.f},
		};
		return arrayType[iIndex];
	}

	//서브 건설 버튼들
	inline const UIPOS Sub_Structure_Button(int type, int sub)
	{
		int iIndex = type * 5 + sub;
		static const UIPOS arrayType[] = {
			{765.f, 115.f},{765.f, 160.f},{765.f, 205.f},{765.f, 250.f},{765.f, 295.f},
			{765.f, 185.f},{765.f, 230.f},{765.f, 275.f},{765.f, 320.f},{765.f, 365.f},
			{765.f, 255.f},{765.f, 300.f},{765.f, 345.f},{765.f, 390.f},{765.f, 435.f},
			{765.f, 335.f},{765.f, 380.f},{765.f, 425.f},{765.f, 470.f},{765.f, 515.f},
		};
		return arrayType[iIndex];
	}

}