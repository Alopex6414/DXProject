/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		DirectSurface.h
* @brief	This File is DirectSurface DLL Project.
* @author	Alopex/Helium
* @version	v1.14a
* @date		2017-12-9	v1.00a	alopex	Create This File.
* @date		2018-01-10	v1.10a	alopex	Code Add dxerr & d3dcompiler Library and Modify Verify.
* @date		2018-01-10	v1.11a	alopex	Add Thread Safe File & Variable(DirectThreadSafe).
* @date		2018-04-12	v1.12a	alopex	Add Macro Call Mode.
* @date		2018-06-22	v1.13a	alopex	Add Version Information.
* @date		2018-06-23	v1.14a	alopex	Repair Bug.
*/
#ifndef __DIRECTSURFACE_H_
#define __DIRECTSURFACE_H_

//Include Windows Header File
#include "DirectCommon.h"

//Macro Definition
#ifdef	CERASUS_EXPORTS
#define DIRECTSURFACE_API	__declspec(dllexport)
#else
#define DIRECTSURFACE_API	__declspec(dllimport)
#endif

#define DIRECTSURFACE_CALLMODE	__stdcall

//Class Definition
class DirectSurface
{
private:
	IDirect3DDevice9*	m_pD3D9Device;										//The Direct3D 9 Device(D3D9绘制设备)
	IDirect3DSurface9*	m_pD3D9Surface;										//The Direct3D 9 Surface(D3D9绘制表面)
	IDirect3DSurface9*	m_pD3D9BackSurface;									//The Direct3D 9 Surface(D3D9后台表面)

	CRITICAL_SECTION m_cs;													//Thread Safe(CriticalSection)
	bool m_bThreadSafe;														//Thread Safe Status

public:
	DirectSurface();														//DirectSurface Constructor Function(构造函数)
	~DirectSurface();														//DirectSurface Destructor  Function(析构函数)

	//构造
	DirectSurface(IDirect3DDevice9* pD3D9Device);							//DirectSurface Constructor Function(构造函数)

	//访问
	virtual IDirect3DDevice9* DIRECTSURFACE_CALLMODE DirectSurfaceGetDevice(void) const;			//DirectSurface Get D3D9Device(获取D3D9设备)
	virtual IDirect3DSurface9* DIRECTSURFACE_CALLMODE DirectSurfaceGetSurface(void) const;			//DirectSurface Get D3D9Surface(获取D3D9表面)

	//控制
	virtual void DIRECTSURFACE_CALLMODE DirectSurfaceSetDevice(IDirect3DDevice9* pD3D9Device);		//DirectSurface Set D3D9Device(设置D3D9设备)
	virtual void DIRECTSURFACE_CALLMODE DirectSurfaceSetSurface(IDirect3DSurface9* pD3D9Surface);	//DirectSurface Set D3D9Surface(获取D3D9表面)

	//初始化
	virtual HRESULT DIRECTSURFACE_CALLMODE DirectSurfaceInit(void);							//DirectSurface Initialize(DirectSurface初始化)

	//加载表面
	virtual HRESULT DIRECTSURFACE_CALLMODE DirectSurfaceLoadSurface(LPWSTR lpszSurface, const RECT* pDestRect = NULL, const RECT* pSrcRect = NULL);										//DirectSurface Load Surface From File(DirectSurface导入纹理)(文件加载)
	virtual HRESULT DIRECTSURFACE_CALLMODE DirectSurfaceLoadSurface(IDirect3DSurface9* pSurface, const RECT* pDestRect = NULL, const RECT* pSrcRect = NULL);							//DirectSurface Load Surface From File(DirectSurface导入纹理)(表面加载)
	virtual HRESULT DIRECTSURFACE_CALLMODE DirectSurfaceLoadSurface(LPCVOID lpcszArray, UINT nArraySize, const RECT* pDestRect = NULL, const RECT* pSrcRect = NULL);					//DirectSurface Load Surface From File(DirectSurface导入纹理)(内存文件加载)
	virtual HRESULT DIRECTSURFACE_CALLMODE DirectSurfaceLoadSurface(LPCVOID lpcszArray, D3DFORMAT Format, UINT nPitch, const RECT* pDestRect = NULL, const RECT* pSrcRect = NULL);		//DirectSurface Load Surface From File(DirectSurface导入纹理)(内存加载)

	//渲染表面
	virtual void DIRECTSURFACE_CALLMODE DirectSurfaceRender(const RECT* pDestRect = NULL, const RECT* pSrcRect = NULL);																	//DirectSurface Render Surface(纹理)
	virtual void DIRECTSURFACE_CALLMODE DirectSurfaceRender(DWORD dwColor);																												//DirectSurface Render Surface(纯色)

	virtual void DIRECTSURFACE_CALLMODE DirectSurfaceRenderYUV(UCHAR* pArrayY, UCHAR* pArrayU, UCHAR* pArrayV, UINT nWidth, UINT nHeight);												//DirectSUrface Render Surface YUV
};


#endif