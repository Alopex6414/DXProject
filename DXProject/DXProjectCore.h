/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2018, Team Shanghai Dream Equinox
*     All rights reserved.
*
* @file		DXProjectCore.h
* @brief	This File is DXProject Core Class.
* @author	Alopex/Helium
* @version	v1.00a
* @date		2018-06-23	v1.00a	alopex	Create This File.
*/
#pragma once

#ifndef __DXPROJECTCORE_H_
#define __DXPROJECTCORE_H_

//Include Windows Header File
#include <Windows.h>

//Include C/C++ Running Header File
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <mmreg.h>
#include <wchar.h>
#include <tchar.h>
#include <time.h>
#include <mmsystem.h>

#include <iostream>
#include <vector>
#include <map>

//Include DirectX Header File
#include "DirectCommon.h"
#include "DirectInput.h"
#include "DirectSound.h"
#include "DirectShow.h"
#include "DirectGraphics.h"
#include "DirectGraphics3D.h"
#include "DirectGraphics2D.h"
#include "DirectTexture.h"
#include "DirectSurface.h"
#include "DirectSprite.h"
#include "DirectFont.h"

#include "Cerasusfps.h"

//Include Window Basic Header File
#include "WinUtilities.h"

//Class Definition
class CDXProjectCore
{
private:
	DirectGraphics* m_pDirectGraphicsMain;

private:
	CCerasusfps* m_pCerasusfpsMain;

public:
	CDXProjectCore();		//���캯��
	~CDXProjectCore();		//��������

	void DXProjectCoreDrawStatic();
	void DXProjectCoreDrawFPS();

	BOOL DXProjectCoreInit();		//��ʼ��
	void DXProjectCoreRelease();	//�ͷ�

	void DXProjectCoreUpdate();		//ˢ��
	void DXProjectCoreRender();		//��Ⱦ

};

#endif // !__DXPROJECTCORE_H_

