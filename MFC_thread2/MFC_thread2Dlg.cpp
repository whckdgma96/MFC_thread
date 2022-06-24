
// MFC_thread2Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFC_thread2.h"
#include "MFC_thread2Dlg.h"
#include "afxdialogex.h"
#include "locale.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCthread2Dlg 대화 상자



CMFCthread2Dlg::CMFCthread2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFC_THREAD2_DIALOG, pParent)
	, mythread2(_T("0"))
	, mythread1(_T("0"))

{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	num1 = 0;
	num2 = 0;
	thread1 = NULL;
	thread2 = NULL;
	m_isWorkingThread1 = true;
	m_isWorkingThread2 = true;
	
}

void CMFCthread2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, mythread2);
	DDX_Text(pDX, IDC_EDIT1, mythread1);
	DDX_Control(pDX, IDC_LIST1, Thread1_list);
	DDX_Control(pDX, IDC_LIST2, Thread2_list);
}

BEGIN_MESSAGE_MAP(CMFCthread2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START, &CMFCthread2Dlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_PAUSE, &CMFCthread2Dlg::OnBnClickedButtonPause)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CMFCthread2Dlg::OnBnClickedButtonStop)
	ON_EN_CHANGE(IDC_EDIT1, &CMFCthread2Dlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &CMFCthread2Dlg::OnEnChangeEdit2)

	ON_WM_TIMER()

	ON_LBN_SELCHANGE(IDC_LIST1, &CMFCthread2Dlg::OnLbnSelchangeList1)
	ON_LBN_SELCHANGE(IDC_LIST2, &CMFCthread2Dlg::OnLbnSelchangeList2)
END_MESSAGE_MAP()


// CMFCthread2Dlg 메시지 처리기

BOOL CMFCthread2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetTimer(200, 500, NULL);

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCthread2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCthread2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCthread2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
UINT MyThread1(LPVOID Pram) {
	CStdioFile thread_1;
	CTime tm = CTime::GetCurrentTime();
	SYSTEMTIME cur_time;
	CString str_log;
	CMFCthread2Dlg* ptr = (CMFCthread2Dlg*)Pram;
	setlocale(LC_ALL, "korean");
	_wsetlocale(LC_ALL, L"korean");

	thread_1.Open(_T("thread1.txt"), CFile::modeCreate | CFile::modeWrite, NULL);
	while (ptr->m_isWorkingThread1) {
		GetLocalTime(&cur_time);
		str_log.Format(_T("[%04d.%02d.%02d %02d:%02d:%02d:%03ld] thread1: %d\n"), 
			cur_time.wYear,
			cur_time.wMonth,
			cur_time.wDay,
			cur_time.wHour,
			cur_time.wMinute,
			cur_time.wSecond,
			cur_time.wMilliseconds,
			ptr->num1);
		thread_1.WriteString(str_log);
		Sleep(1000);
		ptr->num1++;
		TRACE("thread1: %d\n", ptr->num1);
	}
	return 0;
	thread_1.Close();
}

UINT MyThread2(LPVOID Pram) {
	CStdioFile thread_2;
	CTime tm = CTime::GetCurrentTime();
	SYSTEMTIME cur_time2;
	CString str_log2;
	CMFCthread2Dlg* ptr = (CMFCthread2Dlg*)Pram;

	thread_2.Open(_T("thread2.txt"), CFile::modeCreate | CFile::modeWrite, NULL);
	while (ptr->m_isWorkingThread2) {
		GetLocalTime(&cur_time2);
		str_log2.Format(_T("[%04d.%02d.%02d %02d:%02d:%02d:%03ld] thread2: %d\n"),
			cur_time2.wYear,
			cur_time2.wMonth,
			cur_time2.wDay,
			cur_time2.wHour,
			cur_time2.wMinute,
			cur_time2.wSecond,
			cur_time2.wMilliseconds,
			ptr->num2);
		thread_2.WriteString(str_log2);
		Sleep(500);
		ptr->num2++;
		TRACE("thread2: %d\n", ptr->num2);
	}
	return 0;
	thread_2.Close();
}



void CMFCthread2Dlg::OnBnClickedButtonStart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_isWorkingThread1 = true;
	m_isWorkingThread2 = true;
	thread1 = AfxBeginThread(MyThread1, this);
	thread2 = AfxBeginThread(MyThread2, this);
	/*file.Open(_T("txt1.txt"), CFile::modeCreate | CFile::modeWrite, NULL);
	if (file) {
		file.WriteString(mythread1);
	}*/
}

void CMFCthread2Dlg::OnBnClickedButtonPause()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	thread1->SuspendThread();
	thread2->SuspendThread();
	/*DWORD dwExitCode;
	::GetExitCodeThread(thread1->m_hThread, &dwExitCode); */
}

void CMFCthread2Dlg::OnBnClickedButtonStop()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_isWorkingThread1 = false;
	m_isWorkingThread2 = false;
	WaitForSingleObject(thread1->m_hThread,INFINITE);
	WaitForSingleObject(thread2->m_hThread,INFINITE);
	num1 = 0;
	num2 = 0;
	
	Thread1_list.ResetContent();
	Thread2_list.ResetContent();
	DWORD dwExitCode;
	::GetExitCodeThread(thread1->m_hThread, &dwExitCode); //종료확인 코드
	::GetExitCodeThread(thread2->m_hThread, &dwExitCode);
}


void CMFCthread2Dlg::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMFCthread2Dlg::OnEnChangeEdit2()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}



void CMFCthread2Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (nIDEvent == 200) {
		mythread1.Format(_T("%d"), num1);//mythread1에 num1값을 저장
		mythread2.Format(_T("%d"), num2);//mythread2에 num2값을 저장
		Thread1_list.InsertString(-1, mythread1); //list에 thread값(edit control)을 저장
		Thread2_list.InsertString(-1, mythread2); 
		Thread1_list.SetCurSel(Thread1_list.GetCount() - 1); //추가될때마다 스크롤을 아래로 고정
		Thread2_list.SetCurSel(Thread2_list.GetCount() - 1); 
		UpdateData(FALSE);	//출력, True일 경우: 저장

		
	}
	CDialogEx::OnTimer(nIDEvent);
}

void CMFCthread2Dlg::OnLbnSelchangeList1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMFCthread2Dlg::OnLbnSelchangeList2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
