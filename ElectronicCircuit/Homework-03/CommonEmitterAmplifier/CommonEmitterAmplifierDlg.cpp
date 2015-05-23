
// CommonEmitterAmplifierDlg.cpp : ��@��
//

#include "stdafx.h"
#include "CommonEmitterAmplifier.h"
#include "CommonEmitterAmplifierDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace Gdiplus;

// CCommonEmitterAmplifierDlg ��ܤ��

CButton *b_Sine, *b_Square, *bTriangle;
double current_time = 0.0;

void DrawOnPicture(Pt* data, int pt_size, HDC Target)
{
	Graphics g((HDC) Target);
	Pen BlackPen(Color(255, 0, 0, 0), 1);
	SolidBrush RedBrush(Color(255, 255, 0, 0));
	SolidBrush BkBrush(Color(255, 210, 225, 246));

	// Clear Region
	Region ClearRegion(Rect(0, 0, 128, 128));
	g.FillRegion(&BkBrush, &ClearRegion);
	g.DrawLine(&BlackPen, Point(0, 0), Point(127, 0));
	g.DrawLine(&BlackPen, Point(127, 0), Point(127, 127));
	g.DrawLine(&BlackPen, Point(0, 0), Point(0, 127));
	g.DrawLine(&BlackPen, Point(0, 127), Point(127, 127));

	// Draw Line based on data
	int i;
	for (i = 1 ; i < pt_size ; ++i)
	{
		g.DrawLine(&BlackPen, Point(data[i - 1].x, data[i - 1].y), Point(data[i].x, data[i].y));
	}
}

CCommonEmitterAmplifierDlg::CCommonEmitterAmplifierDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCommonEmitterAmplifierDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCommonEmitterAmplifierDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SCROLLBAR1, m_AmplitudeBar);
	DDX_Control(pDX, IDC_SCROLLBAR2, m_FrequencyBar);
	DDX_Control(pDX, IDC_SCROLLBAR3, m_PhaseBar);
	DDX_Control(pDX, IDC_SCROLLBAR4, m_R1Bar);
	DDX_Control(pDX, IDC_SCROLLBAR5, m_R2Bar);
	DDX_Control(pDX, IDC_SCROLLBAR6, m_RcBar);
	DDX_Control(pDX, IDC_SCROLLBAR7, m_ReBar);
	DDX_Control(pDX, IDC_SCROLLBAR8, m_BetaBar);
	DDX_Control(pDX, IDC_AMPLITUDE, m_AmplitudeValue);
	DDX_Control(pDX, IDC_FREQUENCY, m_FrequencyValue);
	DDX_Control(pDX, IDC_PHASE, m_PhaseValue);
	DDX_Control(pDX, IDC_R1, m_R1Value);
	DDX_Control(pDX, IDC_R2, m_R2Value);
	DDX_Control(pDX, IDC_RC, m_RcValue);
	DDX_Control(pDX, IDC_RE, m_ReValue);
	DDX_Control(pDX, IDC_BETA, m_BetaValue);
	DDX_Control(pDX, IDC_VI_MIN, m_Vi_Min);
	DDX_Control(pDX, IDC_VI_MAX, m_Vi_Max);
	DDX_Control(pDX, IDC_VO_MAX, m_Vo_Max);
	DDX_Control(pDX, IDC_VO_MIN, m_Vo_Min);
	DDX_Control(pDX, IDC_CURRENT_TIME, m_CurrentTime);
}

BEGIN_MESSAGE_MAP(CCommonEmitterAmplifierDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_HSCROLL()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CCommonEmitterAmplifierDlg �T���B�z�`��

BOOL CCommonEmitterAmplifierDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// �]�w����ܤ�����ϥܡC�����ε{�����D�������O��ܤ���ɡA
	// �ج[�|�۰ʱq�Ʀ��@�~
	SetIcon(m_hIcon, TRUE);			// �]�w�j�ϥ�
	SetIcon(m_hIcon, FALSE);		// �]�w�p�ϥ�

	// TODO: �b���[�J�B�~����l�]�w
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	b_Sine = (CButton*)GetDlgItem(IDC_RADIO1);
	b_Square = (CButton*)GetDlgItem(IDC_RADIO2);
	bTriangle = (CButton*)GetDlgItem(IDC_RADIO3);
	b_Sine->SetCheck(true);

	m_AmplitudeBar.SetScrollRange(1, 15);
	m_FrequencyBar.SetScrollRange(1, 10);
	m_PhaseBar.SetScrollRange(0, 628);
	m_R1Bar.SetScrollRange(1, 10);
	m_R2Bar.SetScrollRange(1, 10);
	m_RcBar.SetScrollRange(1, 10);
	m_ReBar.SetScrollRange(1, 10);
	m_BetaBar.SetScrollRange(50, 250);

	SetTimer(666, DeltaT, NULL);

	return TRUE;  // �Ǧ^ TRUE�A���D�z�ﱱ��]�w�J�I
}

// �p�G�N�̤p�ƫ��s�[�J�z����ܤ���A�z�ݭn�U�C���{���X�A
// �H�Kø�s�ϥܡC���ϥΤ��/�˵��Ҧ��� MFC ���ε{���A
// �ج[�|�۰ʧ������@�~�C

void CCommonEmitterAmplifierDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ø�s���˸m���e

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// �N�ϥܸm����Τ�ݯx��
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �yø�ϥ�
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ��ϥΪ̩즲�̤p�Ƶ����ɡA
// �t�ΩI�s�o�ӥ\����o�����ܡC
HCURSOR CCommonEmitterAmplifierDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCommonEmitterAmplifierDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: �b���[�J�z���T���B�z�`���{���X�M (��) �I�s�w�]��
	int TempPos = pScrollBar->GetScrollPos();

	switch(nSBCode)
	{
	case SB_THUMBTRACK:
	case SB_THUMBPOSITION:
		pScrollBar->SetScrollPos(nPos);
		break;
	case SB_LINELEFT:
		TempPos--;
		pScrollBar->SetScrollPos(TempPos);
		break;
	case SB_LINERIGHT:
		TempPos++;
		pScrollBar->SetScrollPos(TempPos);
		break;
	}

	CString szAmplitude, szFrequency, szPhase, szR1, szR2, szRc, szRe, szBeta;
	szAmplitude.Format(L"%d", m_AmplitudeBar.GetScrollPos());
	szFrequency.Format(L"%d k", m_FrequencyBar.GetScrollPos());
	szPhase.Format(L"%.2f", m_PhaseBar.GetScrollPos() / 100.0f);
	szR1.Format(L"%d k", m_R1Bar.GetScrollPos());
	szR2.Format(L"%d k", m_R2Bar.GetScrollPos());
	szRc.Format(L"%d k", m_RcBar.GetScrollPos());
	szRe.Format(L"%d k", m_ReBar.GetScrollPos());
	szBeta.Format(L"%d", m_BetaBar.GetScrollPos());
	m_AmplitudeValue.SetWindowText(szAmplitude);
	m_FrequencyValue.SetWindowText(szFrequency);
	m_PhaseValue.SetWindowText(szPhase);
	m_R1Value.SetWindowText(szR1);
	m_R2Value.SetWindowText(szR2);
	m_RcValue.SetWindowText(szRc);
	m_ReValue.SetWindowText(szRe);
	m_BetaValue.SetWindowText(szBeta);

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CCommonEmitterAmplifierDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �b���[�J�z���T���B�z�`���{���X�M (��) �I�s�w�]��
	int i;
	int type;
	double amplitude, frequency, phase;
	double R1, R2, Rc, Re, Beta;
	vector<double> wave;
	vector<double> output;
	Pt *input_pts, *output_pts;
	double min_value, max_value;
	CString szCurrentTime, szViMin, szViMax, szVoMin, szVoMax;
	wave.clear();
	output.clear();
	input_pts = (Pt*) malloc(sizeof(struct Pt) * SamplesToKeep);
	output_pts = (Pt*) malloc(sizeof(struct Pt) * SamplesToKeep);

	if (b_Sine->GetCheck())
	{
		type = SINE_WAVE;
	}
	else if (b_Square->GetCheck())
	{
		type = SQUARE_WAVE;
	}
	else
	{
		type = TRIANGLE_WAVE;
	}

	amplitude = (double) m_AmplitudeBar.GetScrollPos();
	frequency = (double) m_FrequencyBar.GetScrollPos() * 1000.0;
	phase = (double) m_PhaseBar.GetScrollPos() / 100.0;
	R1 = (double) m_R1Bar.GetScrollPos() * 1000.0;
	R2 = (double) m_R2Bar.GetScrollPos() * 1000.0;
	Rc = (double) m_RcBar.GetScrollPos() * 1000.0;
	Re = (double) m_ReBar.GetScrollPos() * 1000.0;
	Beta = (double) m_BetaBar.GetScrollPos();

	Calculate(type, amplitude, frequency, phase, current_time, DeltaT, SamplesToKeep, wave);
	Compute(R1, R2, Rc, Re, Beta, SamplesToKeep, wave, output);

	if (wave.size() <= 0 || output.size() <= 0)
		return;

	szCurrentTime.Format(L"t : %.0lf (ms)", current_time);

	min_value = 9999.0;
	max_value = -9999.0;
	for (i = 0 ; i < wave.size() ; ++i)
	{
		if (wave[i] < min_value)
			min_value = wave[i];
		if (wave[i] > max_value)
			max_value = wave[i];
	}
	szViMin.Format(L"%.2lf", min_value);
	szViMax.Format(L"%.2lf", max_value);
	for (i = 0 ; i < SamplesToKeep ; ++i)
	{
		input_pts[i].x = int((127.0 / SamplesToKeep) * (double) i);
		input_pts[i].y = int(127.0 * (wave[i] - min_value) / (max_value - min_value));
		input_pts[i].y = 127 - input_pts[i].y;
	}
	DrawOnPicture(input_pts, SamplesToKeep, ::GetDC(::GetDlgItem(this->m_hWnd, IDC_INPUT)));

	min_value = 9999.0;
	max_value = -9999.0;
	for (i = 0 ; i < output.size() ; ++i)
	{
		if (output[i] < min_value)
			min_value = output[i];
		if (output[i] > max_value)
			max_value = output[i];
	}
	szVoMin.Format(L"%.2lf", min_value);
	szVoMax.Format(L"%.2lf", max_value);
	for (i = 0 ; i < SamplesToKeep ; ++i)
	{
		output_pts[i].x = int((127.0 / SamplesToKeep) * (double) i);
		output_pts[i].y = int(127.0 * (output[i] - min_value) / (max_value - min_value));
		output_pts[i].y = 127 - output_pts[i].y;
	}
	DrawOnPicture(output_pts, SamplesToKeep, ::GetDC(::GetDlgItem(this->m_hWnd, IDC_OUTPUT)));

	m_CurrentTime.SetWindowText(szCurrentTime);
	m_Vi_Min.SetWindowText(szViMin);
	m_Vi_Max.SetWindowText(szViMax);
	m_Vo_Min.SetWindowText(szVoMin);
	m_Vo_Max.SetWindowText(szVoMax);

	free(input_pts);
	free(output_pts);
	current_time += DeltaT;

	CDialog::OnTimer(nIDEvent);
}
