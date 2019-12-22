#pragma once


// CScaleDlg 대화 상자입니다.

class CScaleDlg : public CDialog
{
	DECLARE_DYNAMIC(CScaleDlg)

public:
	CScaleDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CScaleDlg();
	float z_Scale;
	float y_Scale;
	float x_Scale;
// 대화 상자 데이터입니다.
	enum { IDD = IDD_SCALEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
