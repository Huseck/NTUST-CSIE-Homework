
// WheatstoneBridge.cpp : �w�q���ε{�������O�欰�C
//

#include "stdafx.h"
#include "WheatstoneBridge.h"
#include "WheatstoneBridgeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWheatstoneBridgeApp

BEGIN_MESSAGE_MAP(CWheatstoneBridgeApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CWheatstoneBridgeApp �غc

CWheatstoneBridgeApp::CWheatstoneBridgeApp()
{
	// �N�Ҧ����n����l�]�w�[�J InitInstance ��
}


// �Ȧ����@�� CWheatstoneBridgeApp ����

CWheatstoneBridgeApp theApp;


// CWheatstoneBridgeApp ��l�]�w
typedef VOID (CALLBACK* VALIDATION_FUNC)(int R1, int R2, int R3, int R4, int Vin,
										 double* V1, double* V2, double* V3, double* V4, double* Vo,
										 double* I1, double* I2, double* I3, double* I4);
VALIDATION_FUNC ValidationFunction;
double V1, V2, V3, V4, Vo, I1, I2, I3, I4;
double V1_, V2_, V3_, V4_, Vo_, I1_, I2_, I3_, I4_;
BOOL CWheatstoneBridgeApp::InitInstance()
{
	// ���p���ε{����T�M����w�ϥ� ComCtl32.dll 6 (�t) �H�᪩���A
	// �ӱҰʵ�ı�Ƽ˦��A�b Windows XP �W�A�h�ݭn InitCommonControls()�C
	// �_�h����������إ߳��N���ѡC
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// �]�w�n�]�t�Ҧ��z�Q�n�Ω����ε{������
	// �q�α�����O�C
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	AfxEnableControlContainer();

	// �зǪ�l�]�w
	// �p�G�z���ϥγo�ǥ\��åB�Q���
	// �̫᧹�����i�����ɤj�p�A�z�i�H
	// �q�U�C�{���X�������ݭn����l�Ʊ`���A
	// �ܧ��x�s�]�w�Ȫ��n�����X
	// TODO: �z���ӾA�׭ק惡�r��
	// (�Ҧp�A���q�W�٩β�´�W��)
	SetRegistryKey(_T("���� AppWizard �Ҳ��ͪ����ε{��"));

	HMODULE Validator = LoadLibrary(L"BridgeValidator.exp");

	if (Validator && (ValidationFunction = (VALIDATION_FUNC) GetProcAddress(Validator, "?Validation@@YAXHHHHHPAN00000000@Z")))
	{
		ValidationFunction(1800, 1200, 150, 100, 100, &V1, &V2, &V3, &V4, &Vo, &I1, &I2, &I3, &I4);
		Calculate(1800, 1200, 150, 100, 100, V1_, V2_, V3_, V4_, Vo_, I1_, I2_, I3_, I4_);

		if ((V1 != V1_) || (V2 != V2_) || (V3 != V3_) || (V4 != V4_) || (Vo != Vo_) || (I1 != I1_) || (I2 != I2_) || (I3 != I3_) || (I4 != I4_))
		{
			AfxMessageBox(L"Failed");
			exit(0);
		}
		else
		{
			AfxMessageBox(L"Pass");
			exit(0);
		}
	}

	CWheatstoneBridgeDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// �b����m��ϥ� [�T�w] �Ӱ���ϥι�ܤ����
		// �B�z���{���X
	}
	else if (nResponse == IDCANCEL)
	{
		// �b����m��ϥ� [����] �Ӱ���ϥι�ܤ����
		// �B�z���{���X
	}

	// �]���w�g������ܤ���A�Ǧ^ FALSE�A�ҥH�ڭ̷|�������ε{���A
	// �ӫD���ܶ}�l���ε{�����T���C
	return FALSE;
}
