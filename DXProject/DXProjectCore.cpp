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

//CDXProjectCore ���캯��
CDXProjectCore::CDXProjectCore()
{
	m_pDirectGraphicsMain = NULL;
	m_pCerasusfpsMain = NULL;
}

//CDXProjectCore ��������
CDXProjectCore::~CDXProjectCore()
{
	SAFE_DELETE(m_pCerasusfpsMain);
	SAFE_DELETE(m_pDirectGraphicsMain);
}

//CDXProjectCore ��̬����
void CDXProjectCore::DXProjectCoreDrawStatic()
{
	RECT Rect;

	GetClientRect(g_hWnd, &Rect);

	//Direct3D �����Կ���Ϣ
	Rect.top += 0;
	m_pDirectGraphicsMain->DirectGraphicsFontDrawTextAdapterType(&Rect, DT_TOP | DT_LEFT, D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f));

	//Direct3D ������Ļ�ֱ���
	Rect.top += 20;
	m_pDirectGraphicsMain->DirectGraphicsFontDrawTextScreen(&Rect, DT_TOP | DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 0.5f, 1.0f));

	//Direct3D ���ƻ���ģ��
	Rect.top += 20;
	m_pDirectGraphicsMain->DirectGraphicsFontDrawTextFormat(&Rect, DT_TOP | DT_LEFT, D3DXCOLOR(1.0f, 1.0f, 0.5f, 1.0f));

}

//CDXProjectCore ����FPS
void CDXProjectCore::DXProjectCoreDrawFPS()
{
	m_pCerasusfpsMain->CCerasusfpsGetfps();				//Direct3D���ƾ�̬��Ϣ
	m_pCerasusfpsMain->CCerasusfpsDrawfps(g_hWnd);		//Direct3D����fps
}

//CDXProjectCore ��ʼ��
BOOL CDXProjectCore::DXProjectCoreInit()
{
	HRESULT hr;
	IDirect3DDevice9* pD3D9Device = NULL;

	//DirectGraphics ��ʼ��
	m_pDirectGraphicsMain = new DirectGraphics;
	hr = m_pDirectGraphicsMain->DirectGraphicsInit(g_hWnd, true, USER_SCREENWIDTH, USER_SCREENHEIGHT);
	if (FAILED(hr))
	{
		MessageBox(g_hWnd, _T("Direct3D��ʼ��ʧ��!"), _T("����"), MB_OK | MB_ICONERROR);
		return FALSE;
	}

	hr = m_pDirectGraphicsMain->DirectGraphicsFontInit(20);
	if (FAILED(hr))
	{
		MessageBox(g_hWnd, _T("DirectFont��ʼ��ʧ��!"), _T("����"), MB_OK | MB_ICONERROR);
		return FALSE;
	}

	pD3D9Device = m_pDirectGraphicsMain->DirectGraphicsGetDevice();

	//Cerasusfps��ʼ��
	m_pCerasusfpsMain = new CCerasusfps(pD3D9Device);
	hr = m_pCerasusfpsMain->CCerasusfpsInit(20);
	if (FAILED(hr))
	{
		MessageBox(g_hWnd, _T("Cerasusfps��ʼ��ʧ��!"), _T("����"), MB_OK | MB_ICONERROR);
		return FALSE;
	}

	return TRUE;
}

//CDXProjectCore �ͷ�
void CDXProjectCore::DXProjectCoreRelease()
{
	SAFE_DELETE(m_pCerasusfpsMain);
	SAFE_DELETE(m_pDirectGraphicsMain);
}

//CDXProjectCore ˢ��
void CDXProjectCore::DXProjectCoreUpdate()
{
	HRESULT hr;

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
			m_pDirectGraphicsMain->DirectGraphicsReset();
		}

	}

}

//CDXProjectCore ��Ⱦ
void CDXProjectCore::DXProjectCoreRender()
{
	m_pDirectGraphicsMain->DirectGraphicsBegin();

	DXProjectCoreDrawStatic();
	DXProjectCoreDrawFPS();

	m_pDirectGraphicsMain->DirectGraphicsEnd();
}
