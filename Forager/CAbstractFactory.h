#pragma once

#include "CObj.h"
#include "CUI.h"

template<typename T>
class CAbstractFactory
{
public:
	static CObj* Create()
	{
		CObj* pObj = new T;
		pObj->Initialize();

		return pObj;
	}

	static CObj* Create(float fX, float fY)
	{
		CObj* pObj = new T;
		pObj->Set_Pos(fX, fY);
		pObj->Initialize();
		return pObj;
	}

	static CUI* CreateUI()
	{
		CUI* pObj = new T;
		pObj->Initialize();

		return pObj;
	}

	static CUI* CreateUI(float fX, float fY)
	{
		CUI* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(fX, fY);

		return pObj;
	}
};

