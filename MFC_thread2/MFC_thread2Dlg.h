
// MFC_thread2Dlg.h: 헤더 파일
//

#pragma once

UINT MyThread1(LPVOID Pram);
UINT MyThread2(LPVOID Pram);
// CMFCthread2Dlg 대화 상자
class CMFCthread2Dlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCthread2Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_THREAD2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonPause();
	afx_msg void OnBnClickedButtonStop();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CListBox Thread1_list;
	CListBox Thread2_list;
	CString mythread1;		//Edit Control1 변수
	CString mythread2;		//Edit Control2 변수
	CWinThread* thread1;	//생성할 Thread1 객체
	CWinThread* thread2;	//생성할 Thread2 객체
	bool m_isWorkingThread1;//Thread1 생성 및 삭제 체크용 변수
	bool m_isWorkingThread2;//Thread2 생성 및 삭제 체크용 변수
	int num1;				//Thread1 counting 용 변수
	int num2;				//Thread2 counting 용 변수
	
	CStdioFile file;

	



	
	afx_msg void OnLbnSelchangeList1();
	afx_msg void OnLbnSelchangeList2();
};
