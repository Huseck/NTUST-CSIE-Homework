
// RLC_Circuit.h : PROJECT_NAME ���ε{�����D�n���Y��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�


// CRLC_CircuitApp:
// �аѾ\��@�����O�� RLC_Circuit.cpp
//

class CRLC_CircuitApp : public CWinAppEx
{
public:
	CRLC_CircuitApp();

// �мg
	public:
	virtual BOOL InitInstance();

// �{���X��@

	DECLARE_MESSAGE_MAP()
};

extern CRLC_CircuitApp theApp;