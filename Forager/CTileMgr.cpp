#include "pch.h"
#include "CTileMgr.h"
#include "CAbstractFactory.h"
#include "CScrollMgr.h"
#include "Define.h"
#include "CManager.h"
#include <algorithm>


CTileMgr* CTileMgr::m_pInstance = nullptr;

CTileMgr::CTileMgr() 
{
	m_vecTile.reserve(TILEX * TILEY);

}

CTileMgr::~CTileMgr()
{
	Release();
}

void CTileMgr::Initialilze()
{
	for (int i = 0; i < TILEY; ++i)
	{
		for (int j = 0; j < TILEX; ++j)
		{
			float fX = float((j * TILECX) + (TILECX >> 1));
			float fY = float((i * TILECY) + (TILECY >> 1));

			CObj* pTile = CAbstractFactory<CTile>::Create(fX, fY);
			m_vecTile.push_back(pTile);
		}
	}

	m_vecCopyIsland = CManager::User()->Get_Island();

	Load_Tile();

}

int CTileMgr::Update()
{
	for (int i = 0; i < m_vecCopyIsland.size(); ++i) {
		if (CManager::User()->Get_IsBuyIsland(i)) {
			for (int j = m_vecCopyIsland[i].iMinX; j <= m_vecCopyIsland[i].iMaxX; ++j) {
				for (int k = m_vecCopyIsland[i].iMinY; k <= m_vecCopyIsland[i].iMaxY; ++k) {
					m_vecTile[k * TILEX + j]->Update();
				}
			}
			
		}
	}

	//for (auto& pTile : m_vecTile)
	//	pTile->Update();

	return 0;
}

void CTileMgr::Late_Update()
{
	for (int i = 0; i < m_vecCopyIsland.size(); ++i) {
		if (CManager::User()->Get_IsBuyIsland(i)) {
			for (int j = m_vecCopyIsland[i].iMinX; j <= m_vecCopyIsland[i].iMaxX; ++j) {
				for (int k = m_vecCopyIsland[i].iMinY; k <= m_vecCopyIsland[i].iMaxY; ++k) {
					m_vecTile[k * TILEX + j]->Late_Update();
				}
			}
		}
	}

}

void CTileMgr::Render(HDC hDC)
{

	int	iScrollX = CScrollMgr::Get_Instance()->Get_ScrollX() >100.f ? 0 : abs((int)CScrollMgr::Get_Instance()->Get_ScrollX() / TILECX);
	int	iScrollY = abs((int)CScrollMgr::Get_Instance()->Get_ScrollY() / TILECY);

	int	 iMaxX = iScrollX + 20; // WINCX / TILECX + 2;
	int	 iMaxY = iScrollY + 12; // WINCY / TILECY + 2;

	for (size_t i = 0; i < m_vecCopyIsland.size(); ++i) {
		if (CManager::User()->Get_IsBuyIsland(i))
		{
			//화면 크기 WINCX x WINCY 만큼만 
			for (int y = iScrollY; y < iMaxY; ++y)
			{
				for (int x = iScrollX; x < iMaxX; ++x)
				{
					
					if( m_vecCopyIsland[i].iMinY <= y && y <= m_vecCopyIsland[i].iMaxY && m_vecCopyIsland[i].iMinX <= x && x <= m_vecCopyIsland[i].iMaxX)
					{
						int	iIndex = y * TILEX + x;

						if (0 > iIndex || (size_t)iIndex >= m_vecTile.size())
							continue;

						m_vecTile[iIndex]->Render(hDC);
					}
				}
			}

			//for (int j = m_vecCopyIsland[i].iMinX; j <= m_vecCopyIsland[i].iMaxX; ++j) {
			//	for (int k = m_vecCopyIsland[i].iMinY; k <= m_vecCopyIsland[i].iMaxY; ++k) {
			//		m_vecTile[k * TILEX + j]->Render(hDC);
			//	}
			//}
		}
	}
}

void CTileMgr::Release()
{
	for_each(m_vecTile.begin(), m_vecTile.end(), SafeDelete<CObj*>);
	m_vecTile.clear();
}

void CTileMgr::Save_Tile()
{
	HANDLE hFile = CreateFile(L"../Data/Tile.dat",		// 파일 이름이 명시된 경로
		GENERIC_WRITE,		// 모드 설정(GENERIC_WRITE : 쓰기, GENERIC_READ : 읽기)
		NULL,				// 공유 방식, 파일이 열려있는 상태에서 다른 프로세스가 오픈할 때 허가할 것인가, NULL인 경우 공유하지 않음
		NULL,				// 보안 속성(NULL인 경우 기본값에 해당하는 보안상태 유지)
		CREATE_ALWAYS,		// 생성 방식(파일이 없을 경우, 파일을 생성하여 쓰기, 있을 경우 덮어쓰기) / OPEN_EXISTING(파일이 있을 경우에만 불러오기)
		FILE_ATTRIBUTE_NORMAL, // 파일 속성(아무런 속성이 없는 일반적인 파일 생성)
		NULL);				//생성될 파일의 속성을 제공할 템플릿 파일(사용하지 않기 때문에 NULL)

	if (INVALID_HANDLE_VALUE == hFile)
	{
		// _T : 아스키 코드 문자열을 유니코드로 전환
		MessageBox(g_hWnd, _T("Save File"), L"Fail", MB_OK);
		return;
	}

	DWORD	dwByte(0);
	int		iDrawID(0), iOption(0);

	for (auto& pTile : m_vecTile)
	{
		iDrawID = dynamic_cast<CTile*>(pTile)->Get_DrawID();
		iOption = dynamic_cast<CTile*>(pTile)->Get_Option();

		WriteFile(hFile, pTile->Get_Info(), sizeof(INFO), &dwByte, NULL);
		WriteFile(hFile, &iDrawID, sizeof(int), &dwByte, NULL);
		WriteFile(hFile, &iOption, sizeof(int), &dwByte, NULL);
	}

	CloseHandle(hFile);
	MessageBox(g_hWnd, L"Tile Save", L"성공", MB_OK);
}

void CTileMgr::Load_Tile()
{
	HANDLE hFile = CreateFile(L"../Data/Tile.dat",		// 파일 이름이 명시된 경로
		GENERIC_READ,		// 모드 설정(GENERIC_WRITE : 쓰기, GENERIC_READ : 읽기)
		NULL,				// 공유 방식, 파일이 열려있는 상태에서 다른 프로세스가 오픈할 때 허가할 것인가, NULL인 경우 공유하지 않음
		NULL,				// 보안 속성(NULL인 경우 기본값에 해당하는 보안상태 유지)
		OPEN_EXISTING,		// 생성 방식(파일이 없을 경우, 파일을 생성하여 쓰기, 있을 경우 덮어쓰기) / OPEN_EXISTING(파일이 있을 경우에만 불러오기)
		FILE_ATTRIBUTE_NORMAL, // 파일 속성(아무런 속성이 없는 일반적인 파일 생성)
		NULL);				//생성될 파일의 속성을 제공할 템플릿 파일(사용하지 않기 때문에 NULL)

	if (INVALID_HANDLE_VALUE == hFile)
	{
		// _T : 아스키 코드 문자열을 유니코드로 전환
		MessageBox(g_hWnd, _T("Load File"), L"Fail", MB_OK);
		return;
	}

	DWORD	dwByte(0);
	int		iDrawID(0), iOption(0), iIndex(0);
	INFO	tInfo{};

	Release();

	while (true)
	{
		ReadFile(hFile, &tInfo, sizeof(INFO), &dwByte, NULL);
		ReadFile(hFile, &iDrawID, sizeof(int), &dwByte, NULL);
		ReadFile(hFile, &iOption, sizeof(int), &dwByte, NULL);

		if (0 == dwByte)
			break;

		CObj* pObj = CAbstractFactory<CTile>::Create(tInfo.fX, tInfo.fY);

		dynamic_cast<CTile*>(pObj)->Set_DrawID(iDrawID);
		dynamic_cast<CTile*>(pObj)->Set_Option(iOption);

		m_vecTile.push_back(pObj);

		//if (iOption >= 1)
		//	m_vecBlock.push_back(iIndex);

		++iIndex;
	}

	CloseHandle(hFile);
	//MessageBox(g_hWnd, L"Tile Load", L"성공", MB_OK);
}

void CTileMgr::Picking_Tile(POINT ptMouse, int iDrawID, int iOption)
{
	int x = ptMouse.x / TILECX;
	int y = ptMouse.y / TILECY;

	int	iIndex = y * TILEX + x;

	if (0 > iIndex || (size_t)iIndex >= m_vecTile.size())
		return;

	dynamic_cast<CTile*>(m_vecTile[iIndex])->Set_DrawID(iDrawID);
	dynamic_cast<CTile*>(m_vecTile[iIndex])->Set_Option(iOption);
	
}
