
// WheatstoneBridge.h : PROJECT_NAME ���ε{�����D�n���Y��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�


// CWheatstoneBridgeApp:
// �аѾ\��@�����O�� WheatstoneBridge.cpp
//

class CWheatstoneBridgeApp : public CWinAppEx
{
public:
	CWheatstoneBridgeApp();

// �мg
	public:
	virtual BOOL InitInstance();

// �{���X��@

	DECLARE_MESSAGE_MAP()
};

extern CWheatstoneBridgeApp theApp;