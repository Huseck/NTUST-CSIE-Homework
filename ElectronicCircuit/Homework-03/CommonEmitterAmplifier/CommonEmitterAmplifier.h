
// CommonEmitterAmplifier.h : PROJECT_NAME ���ε{�����D�n���Y��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�


// CCommonEmitterAmplifierApp:
// �аѾ\��@�����O�� CommonEmitterAmplifier.cpp
//

class CCommonEmitterAmplifierApp : public CWinAppEx
{
public:
	CCommonEmitterAmplifierApp();

// �мg
	public:
	virtual BOOL InitInstance();

// �{���X��@

	DECLARE_MESSAGE_MAP()
};

extern CCommonEmitterAmplifierApp theApp;