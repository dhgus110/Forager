#pragma once

#include "Extension.h"

class CKeyMgr
{
private:
	CKeyMgr();
	CKeyMgr(const CKeyMgr& rhs) = delete;
	CKeyMgr& operator=(CKeyMgr& rKey) = delete;
	~CKeyMgr();


public:
	static CKeyMgr* Get_Instance() {
		if (m_pInstance == nullptr)
			m_pInstance = new CKeyMgr();

		return m_pInstance;
	}
	static void Destroy_Instance() {
		if (m_pInstance != nullptr)
			delete m_pInstance;
		m_pInstance = nullptr;
	}

public:
	void Late_Update();

public:
	bool Key_Pressing(int _iKey);
	bool Key_Down(int _iKey);
	bool Key_Up(int _iKey);


private:
	static CKeyMgr* m_pInstance;

	bool			m_bKeyState[VK_MAX];
};

