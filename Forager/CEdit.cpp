#include "pch.h"
#include "CEdit.h"
#include "CManager.h"
#include "CAbstractFactory.h"
#include "CMouse.h"

CEdit::CEdit() :m_pFrameKey(nullptr), m_iDrawID(0), m_iOption(0)
{
	ZeroMemory(&m_szTest, sizeof(m_szTest));

}

CEdit::~CEdit()
{
	Release();
}

void CEdit::Initailize()
{
	//CManager::Bmp()->Insert_Bmp(L"../Image/Tile/Tile_Edge_D.bmp", L"Tile_Edge_D");
	//CManager::Bmp()->Insert_Bmp(L"../Image/Tile/Tile_Edge_L.bmp", L"Tile_Edge_L");
	//CManager::Bmp()->Insert_Bmp(L"../Image/Tile/Tile_Edge_LD.bmp", L"Tile_Edge_LD");
	//CManager::Bmp()->Insert_Bmp(L"../Image/Tile/Tile_Edge_LU.bmp", L"Tile_Edge_LU");
	//CManager::Bmp()->Insert_Bmp(L"../Image/Tile/Tile_Edge_R.bmp", L"Tile_Edge_R");
	//CManager::Bmp()->Insert_Bmp(L"../Image/Tile/Tile_Edge_RD.bmp", L"Tile_Edge_RD");
	//CManager::Bmp()->Insert_Bmp(L"../Image/Tile/Tile_Edge_RU.bmp", L"Tile_Edge_RU");
	//CManager::Bmp()->Insert_Bmp(L"../Image/Tile/Tile_Edge_U.bmp", L"Tile_Edge_U");
	//CManager::Bmp()->Insert_Bmp(L"../Image/Tile/Tile_Normal.bmp", L"Tile_Normal");
	//CManager::Bmp()->Insert_Bmp(L"../Image/Tile/Tile_Puddle.bmp", L"Tile_Puddle");
	//CManager::Bmp()->Insert_Bmp(L"../Image/Tile/Tile_Spot.bmp", L"Tile_Spot");
	//CManager::Bmp()->Insert_Bmp(L"../Image/Tile/Tile_Stone.bmp", L"Tile_Stone");
	//CManager::Bmp()->Insert_Bmp(L"../Image/Tile/Tile_Water.bmp", L"Tile_Water");
	//CManager::Bmp()->Insert_Bmp(L"../Image/Tile/Tile_Wave_1.bmp", L"Tile_Wave_1");

	CManager::Bmp()->Insert_Bmp(L"../Image/Tile/Tile.bmp", L"Tile");
	//CManager::Bmp()->Insert_Bmp(L"../Image/Tile/Tile_Wave_3.bmp", L"Tile_Wave_3");

	m_pFrameKey = L"Tile";


	CManager::Tile()->Initialilze();
	//CManager::Obj()->Add_Object(OBJ_MOUSE, CAbstractFactory<CMouse>::Create());
	CManager::UI()->AddObject(UI_MOUSE, CAbstractFactory<CMouse>::CreateUI());
}

void CEdit::Update()
{
	CManager::Tile()->Update();
	//CManager::Obj()->Get_ObjectBack(OBJ_MOUSE)->Update();
	CManager::UI()->Get_ObjectBack(UI_MOUSE)->Update();

	Key_Input();

}

void CEdit::Late_Update()
{
	CManager::Tile()->Late_Update();
	//CManager::Obj()->Get_ObjectBack(OBJ_MOUSE)->Late_Update();
	CManager::UI()->Get_ObjectBack(UI_MOUSE)->Late_Update();



}

void CEdit::Render(HDC hDC)
{
	HDC	hBackDC = CBmpMgr::Get_Instance()->Find_Img(L"Back");
	HDC	hGroundDC = CBmpMgr::Get_Instance()->Find_Img(L"Temp");

	BitBlt(hBackDC,		// 복사 받을 화면 dc
		0,	// 복사 받을 위치 좌표
		0,
		WINCX,		// 복사 받을 이미지 가로, 세로 사이즈
		WINCY,
		hGroundDC,		// 복사할 이미지 dc
		0, 0,		// 비트맵 출력 자표
		SRCCOPY);

	CManager::Tile()->Render(hBackDC);
	//CManager::Obj()->Get_ObjectBack(OBJ_MOUSE)->Render(hBackDC);
	CManager::UI()->Get_ObjectBack(UI_MOUSE)->Render(hBackDC);


	BitBlt(hDC,		// 복사 받을 화면 dc
		0,	// 복사 받을 위치 좌표
		0,
		WINCX,		// 복사 받을 이미지 가로, 세로 사이즈
		WINCY,
		hBackDC,		// 복사할 이미지 dc
		0, 0,		// 비트맵 출력 자표
		SRCCOPY);	// 그대로 출력



	//wsprintf(m_szTest, L"vecBlock_Size : %d", CManager::Tile()->Get_BlockSize());
	//TextOut(hDC, 100, 20, m_szTest, lstrlen(m_szTest));
}

void CEdit::Release()
{
}

void CEdit::Key_Input()
{
	if (CManager::Key()->Key_Pressing('Q'))
	{
		m_iDrawID = 0;
		m_iOption = 0;
	}

	if (CManager::Key()->Key_Pressing('W'))
	{
		m_iDrawID = 1;
		m_iOption = 0;
	}
	if (CManager::Key()->Key_Pressing('E'))
	{
		m_iDrawID = 2;
		m_iOption = 0;
	}
	if (CManager::Key()->Key_Pressing('A'))
	{
		m_iDrawID = 3;
		m_iOption = 0;
	}
	if (CManager::Key()->Key_Pressing('S'))
	{
		m_iDrawID = 4;
		m_iOption = 0;
	}
	if (CManager::Key()->Key_Pressing('D'))
	{
		m_iDrawID = 5;
		m_iOption = 0;
	}
	if (CManager::Key()->Key_Pressing('Z'))
	{
		m_iDrawID = 6;
		m_iOption = 0;
	}
	if (CManager::Key()->Key_Pressing('X'))
	{
		m_iDrawID = 7;
		m_iOption = 0;
	}
	if (CManager::Key()->Key_Pressing('C'))
	{
		m_iDrawID = 8;
		m_iOption = 0;
	}
	if (CManager::Key()->Key_Pressing('1')) //얼룩
	{
		m_iDrawID = 9;
		m_iOption = 0;
	}
	if (CManager::Key()->Key_Pressing('2')) //파임
	{
		m_iDrawID = 10;
		m_iOption = 0;
	}
	if (CManager::Key()->Key_Pressing('3')) //돌
	{
		m_iDrawID = 11;
		m_iOption = 0;
	}

	if (CManager::Key()->Key_Pressing('G')) //물
	{
		m_iDrawID = 12;
		m_iOption = 1;
	}
	if (CManager::Key()->Key_Pressing('H')) //wave
	{
		m_iDrawID = 13;
		m_iOption = 2;
	}
	if (CManager::Key()->Key_Pressing('J')) //wave ( 벡터에 저장안됨) 
	{
		m_iDrawID = 12;
		m_iOption = 0;
	}


	if (CManager::Key()->Key_Pressing(VK_LEFT))
		CManager::Scroll()->Set_ScrollX(5.f);

	if (CManager::Key()->Key_Pressing(VK_RIGHT))
		CManager::Scroll()->Set_ScrollX(-5.f);

	if (CManager::Key()->Key_Pressing(VK_UP))
		CManager::Scroll()->Set_ScrollY(5.f);

	if (CManager::Key()->Key_Pressing(VK_DOWN))
		CManager::Scroll()->Set_ScrollY(-5.f);

	if (CManager::Key()->Key_Pressing('O'))
		CManager::Tile()->Save_Tile();

	if (CManager::Key()->Key_Pressing('P'))
		CManager::Tile()->Load_Tile();


	if (CManager::Key()->Key_Pressing(VK_LBUTTON))
	{
		POINT	ptMouse{};
		GetCursorPos(&ptMouse);
		ScreenToClient(g_hWnd, &ptMouse);

		ptMouse.x -= (int)CManager::Scroll()->Get_ScrollX();
		ptMouse.y -= (int)CManager::Scroll()->Get_ScrollY();

		CManager::Tile()->Picking_Tile(ptMouse, m_iDrawID, m_iOption);
	}
}
