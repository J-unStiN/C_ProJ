#pragma once


// CZdepthDlg 대화 상자입니다.

class CZdepthDlg : public CDialog
{
	DECLARE_DYNAMIC(CZdepthDlg)

public:
	CZdepthDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CZdepthDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DEPTHDLG };
	float z_depth;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};