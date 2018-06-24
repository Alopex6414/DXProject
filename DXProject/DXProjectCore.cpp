/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		DXProjectCore.cpp
* @brief	This File is DXProject Core Class.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2018-06-23	v1.00a	alopex	Create This File.
*/
#include "DXProjectCore.h"

//CDXProjectCore 构造函数
CDXProjectCore::CDXProjectCore()
{
	m_pDirectGraphicsMain = NULL;
	m_pDirectGraphics3DMain = NULL;
	m_pDirectGraphics3DTitle = NULL;
	//m_pDirectSurface = NULL;
	m_pCerasusfpsMain = NULL;
}

//CDXProjectCore 析构函数
CDXProjectCore::~CDXProjectCore()
{
	SAFE_DELETE(m_pCerasusfpsMain);
	//SAFE_DELETE(m_pDirectSurface);
	SAFE_DELETE(m_pDirectGraphics3DTitle);
	SAFE_DELETE(m_pDirectGraphics3DMain);
	SAFE_DELETE(m_pDirectGraphicsMain);
}

//CDXProjectCore 静态绘制
void CDXProjectCore::DXProjectCoreDrawStatic()
{
	RECT Rect;

	GetClientRect(g_hWnd, &Rect);

	//Direct3D 绘制显卡信息
	Rect.top += 0;
	m_pDirectGraphicsMain->DirectGraphicsFontDrawTextAdapterType(&Rect, DT_TOP | DT_LEFT, D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f));

	//Direct3D 绘制屏幕分辨率
	Rect.top += 20;
	m_pDirectGraphicsMain->DirectGraphicsFontDrawTextScreen(&Rect, DT_TOP | DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 0.5f, 1.0f));

	//Direct3D 绘制缓冲模板
	Rect.top += 20;
	m_pDirectGraphicsMain->DirectGraphicsFontDrawTextFormat(&Rect, DT_TOP | DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 0.5f, 1.0f));

}

//CDXProjectCore 绘制FPS
void CDXProjectCore::DXProjectCoreDrawFPS()
{
	m_pCerasusfpsMain->CCerasusfpsGetfps();				//Direct3D绘制静态信息
	m_pCerasusfpsMain->CCerasusfpsDrawfps(g_hWnd);		//Direct3D绘制fps
}

//CDXProjectCore 初始化
BOOL CDXProjectCore::DXProjectCoreInit()
{
	HRESULT hr;
	IDirect3DDevice9* pD3D9Device = NULL;

	//DirectGraphics 初始化
	m_pDirectGraphicsMain = new DirectGraphics;
	hr = m_pDirectGraphicsMain->DirectGraphicsInit(g_hWnd, true, USER_SCREENWIDTH, USER_SCREENHEIGHT);
	if (FAILED(hr))
	{
		MessageBox(g_hWnd, _T("Direct3D初始化失败!"), _T("错误"), MB_OK | MB_ICONERROR);
		return FALSE;
	}

	hr = m_pDirectGraphicsMain->DirectGraphicsFontInit(20);
	if (FAILED(hr))
	{
		MessageBox(g_hWnd, _T("DirectFont初始化失败!"), _T("错误"), MB_OK | MB_ICONERROR);
		return FALSE;
	}

	pD3D9Device = m_pDirectGraphicsMain->DirectGraphicsGetDevice();

	//DirectGraphics3D 初始化
	m_pDirectGraphics3DMain = new DirectGraphics3D(pD3D9Device);
	hr = m_pDirectGraphics3DMain->DirectGraphics3DInitVertex3DBase(6);
	if (FAILED(hr))
	{
		MessageBox(g_hWnd, _T("DirectGraphics3D初始化失败!"), _T("错误"), MB_OK | MB_ICONERROR);
		return FALSE;
	}

	//Direct3D 资源路径
	CHAR chArr[MAX_PATH] = { 0 };
	WCHAR wcArr[MAX_PATH] = { 0 };

	Armeniaca_FilePath_GetLocalPathA(chArr, MAX_PATH);
	strcat_s(chArr, "\\Res\\title00a.png");
	Armeniaca_Convert_A2W_Safe(chArr, wcArr, MAX_PATH);

	//DirectGrpahics3D 初始化
	m_pDirectGraphics3DTitle = new DirectGraphics3D(pD3D9Device);
	hr = m_pDirectGraphics3DTitle->DirectGraphics3DInitVertex3DTexture(1, wcArr, 1024, 512);
	if (FAILED(hr))
	{
		MessageBox(g_hWnd, _T("DirectGraphics3D初始化失败!"), _T("错误"), MB_OK | MB_ICONERROR);
		return FALSE;
	}

	//DirectSurface 初始化
	/*CHAR chArr[MAX_PATH] = { 0 };
	WCHAR wcArr[MAX_PATH] = { 0 };

	Armeniaca_FilePath_GetLocalPathA(chArr, MAX_PATH);
	strcat_s(chArr, "\\Res\\title00a.png");
	Armeniaca_Convert_A2W_Safe(chArr, wcArr, MAX_PATH);
	m_pDirectSurface = new DirectSurface(pD3D9Device);
	hr = m_pDirectSurface->DirectSurfaceInit();
	if (FAILED(hr))
	{
		MessageBox(g_hWnd, _T("DirectSurface初始化失败!"), _T("错误"), MB_OK | MB_ICONERROR);
		return FALSE;
	}
	m_pDirectSurface->DirectSurfaceLoadSurface(wcArr);*/

	//Cerasusfps初始化
	m_pCerasusfpsMain = new CCerasusfps(pD3D9Device);
	hr = m_pCerasusfpsMain->CCerasusfpsInit(20);
	if (FAILED(hr))
	{
		MessageBox(g_hWnd, _T("Cerasusfps初始化失败!"), _T("错误"), MB_OK | MB_ICONERROR);
		return FALSE;
	}

	return TRUE;
}

//CDXProjectCore 释放
void CDXProjectCore::DXProjectCoreRelease()
{
	SAFE_DELETE(m_pCerasusfpsMain);
	//SAFE_DELETE(m_pDirectSurface);
	SAFE_DELETE(m_pDirectGraphics3DTitle);
	SAFE_DELETE(m_pDirectGraphics3DMain);
	SAFE_DELETE(m_pDirectGraphicsMain);
}

//CDXProjectCore 刷新
void CDXProjectCore::DXProjectCoreUpdate()
{
	HRESULT hr;
	IDirect3DSurface9* pD3D9Surface = NULL;

	hr = m_pDirectGraphicsMain->DirectGraphicsTestCooperativeLevel();
	if (hr != S_OK)
	{
		if (hr == D3DERR_DEVICELOST)
		{
			return;
		}

		if (hr == D3DERR_DEVICENOTRESET)
		{
			m_pCerasusfpsMain->CCerasusfpsReset();
			m_pDirectGraphics3DMain->DirectGraphics3DReset();
			m_pDirectGraphics3DTitle->DirectGraphics3DReset();

			//pD3D9Surface = m_pDirectSurface->DirectSurfaceGetSurface();
			//SAFE_RELEASE(pD3D9Surface);

			m_pDirectGraphicsMain->DirectGraphicsReset();

			m_pDirectGraphics3DMain->DirectGraphics3DInitVertex3DBase(6);

			CHAR chArr[MAX_PATH] = { 0 };
			WCHAR wcArr[MAX_PATH] = { 0 };

			Armeniaca_FilePath_GetLocalPathA(chArr, MAX_PATH);
			strcat_s(chArr, "\\Res\\title00a.png");
			Armeniaca_Convert_A2W_Safe(chArr, wcArr, MAX_PATH);
			m_pDirectGraphics3DTitle->DirectGraphics3DInitVertex3DTexture(1, wcArr, 1024, 512);
			//m_pDirectSurface->DirectSurfaceInit();
		}

	}

}

//CDXProjectCore 渲染
void CDXProjectCore::DXProjectCoreRender()
{
	IDirect3DDevice9* pD3D9Device = NULL;
	RECT Rect;

	GetClientRect(g_hWnd, &Rect);
	pD3D9Device = m_pDirectGraphicsMain->DirectGraphicsGetDevice();

	m_pDirectGraphicsMain->DirectGraphicsBegin();

	//m_pDirectSurface->DirectSurfaceRender(&Rect, &Rect);

	//渲染模式:Alpha混合设置
	pD3D9Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);					//Alpha混合开启

	//渲染模式:纹理混合设置
	pD3D9Device->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_DISABLE);

	DXProjectCoreDrawCube();

	m_pDirectGraphics3DMain->DirectGraphics3DRenderStateLightDisable();
	m_pDirectGraphics3DMain->DirectGraphics3DRenderStateSetting();
	DXProjectCoreDrawTitle();
	m_pDirectGraphics3DMain->DirectGraphics3DRenderStateAlphaDisable();

	DXProjectCoreDrawStatic();
	DXProjectCoreDrawFPS();

	m_pDirectGraphicsMain->DirectGraphicsEnd();
}

//CDXProjectCore 绘制标题
void CDXProjectCore::DXProjectCoreDrawTitle()
{
	//标题
	Vertex3DTexture pVertices[] =
	{
		{ 320.0f, 240.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), (640.0f / 1024.0f), 0.0f },
		{ -320.0f, 240.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, 0.0f },
		{ -320.0f, -240.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f, (480.0f / 512.0f) },
		{ 320.0f, -240.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), (640.0f / 1024.0f), (480.0f / 512.0f) },
	};

	DG3D_CoordsTransformPara sCoordsTransformPara = { 0 };

	//世界变换
	sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleX = 1.0f;
	sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleY = 1.0f;
	sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleZ = 1.0f;
	sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateX = 0.0f;
	sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateY = 0.0f;
	sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateZ = 0.0f;
	sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateX = 0.0f;
	sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateY = 0.0f;
	sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateZ = 0.0f;

	//取景变换
	sCoordsTransformPara.sViewTransformPara.vAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	sCoordsTransformPara.sViewTransformPara.vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	sCoordsTransformPara.sViewTransformPara.vEye = D3DXVECTOR3(0.0f, 0.0f, 240.0f);

	//投影变换
	sCoordsTransformPara.sPrespectiveTransformPara.fovy = D3DX_PI / 2.0f;
	sCoordsTransformPara.sPrespectiveTransformPara.fAspect = (float)(USER_SCREENWIDTH * 1.0f / USER_SCREENHEIGHT);
	sCoordsTransformPara.sPrespectiveTransformPara.fZn = 1.0f;
	sCoordsTransformPara.sPrespectiveTransformPara.fZf = 240.0f;

	//视口变换
	sCoordsTransformPara.sViewPortTransformPara.nUserWidth = USER_SCREENWIDTH;
	sCoordsTransformPara.sViewPortTransformPara.nUserHeight = USER_SCREENHEIGHT;

	//坐标变换
	m_pDirectGraphics3DTitle->DirectGraphics3DMatrixTransform(sCoordsTransformPara);

	//投射顶点
	m_pDirectGraphics3DTitle->DirectGraphics3DPaddingVertexAndIndex(pVertices, 1);

	//绘制
	m_pDirectGraphics3DTitle->DirectGraphics3DRender(Vertex3D_Type_Texture, 1, true);
}

//CDXProjectCore 绘制几何体
void CDXProjectCore::DXProjectCoreDrawCube()
{
	//初始化时间种子
	srand((unsigned int)time(NULL));

	//正方体
	Vertex3DBase Vertices[] =
	{
		{ 10.0f, 10.0f, 10.0f, D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256) },
		{ -10.0f, 10.0f, 10.0f, D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256) },
		{ -10.0f, -10.0f, 10.0f, D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256) },
		{ 10.0f, -10.0f, 10.0f, D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256) },

		{ 10.0f, 10.0f, -10.0f, D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256) },
		{ 10.0f, 10.0f, 10.0f, D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256) },
		{ 10.0f, -10.0f, 10.0f, D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256) },
		{ 10.0f, -10.0f, -10.0f, D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256) },

		{ -10.0f, 10.0f, -10.0f, D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256) },
		{ 10.0f, 10.0f, -10.0f, D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256) },
		{ 10.0f, -10.0f, -10.0f, D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256) },
		{ -10.0f, -10.0f, -10.0f, D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256) },

		{ -10.0f, 10.0f, 10.0f, D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256) },
		{ -10.0f, 10.0f, -10.0f, D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256) },
		{ -10.0f, -10.0f, -10.0f, D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256) },
		{ -10.0f, -10.0f, 10.0f, D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256) },

		{ -10.0f, 10.0f, 10.0f, D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256) },
		{ 10.0f, 10.0f, 10.0f, D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256) },
		{ 10.0f, 10.0f, -10.0f, D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256) },
		{ -10.0f, 10.0f, -10.0f, D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256) },

		{ -10.0f, -10.0f, 10.0f, D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256) },
		{ 10.0f, -10.0f, 10.0f, D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256) },
		{ 10.0f, -10.0f, -10.0f, D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256) },
		{ -10.0f, -10.0f, -10.0f, D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256) },
	};

	DG3D_CoordsTransformPara sCoordsTransformPara = { 0 };

	//世界变换
	sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleX = 1.0f;
	sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleY = 1.0f;
	sCoordsTransformPara.sWorldTransformPara.sScalePara.fScaleZ = 1.0f;
	sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateX = 0.0f;
	sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateY = D3DX_PI * timeGetTime() * 0.001f;
	sCoordsTransformPara.sWorldTransformPara.sRotatePara.fRotateZ = 0.0f;
	sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateX = 0.0f;
	sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateY = 0.0f;
	sCoordsTransformPara.sWorldTransformPara.sTranslatePara.fTranslateZ = 0.0f;

	//取景变换
	sCoordsTransformPara.sViewTransformPara.vAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	sCoordsTransformPara.sViewTransformPara.vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	sCoordsTransformPara.sViewTransformPara.vEye = D3DXVECTOR3(0.0f, 20.0f, 25.0f);

	//投影变换
	sCoordsTransformPara.sPrespectiveTransformPara.fovy = D3DX_PI / 2.0f;
	sCoordsTransformPara.sPrespectiveTransformPara.fAspect = (float)(USER_SCREENWIDTH * 1.0f / USER_SCREENHEIGHT);
	sCoordsTransformPara.sPrespectiveTransformPara.fZn = 1.0f;
	sCoordsTransformPara.sPrespectiveTransformPara.fZf = 240.0f;

	//视口变换
	sCoordsTransformPara.sViewPortTransformPara.nUserWidth = USER_SCREENWIDTH;
	sCoordsTransformPara.sViewPortTransformPara.nUserHeight = USER_SCREENHEIGHT;

	//坐标变换
	m_pDirectGraphics3DMain->DirectGraphics3DMatrixTransform(sCoordsTransformPara);

	//投射顶点
	m_pDirectGraphics3DMain->DirectGraphics3DPaddingVertexAndIndex(Vertices, 6);

	//绘制
	m_pDirectGraphics3DMain->DirectGraphics3DRender(Vertex3D_Type_Base, 6);
}
