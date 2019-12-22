#pragma once


// CLightDlg 대화 상자입니다.

class CLightDlg : public CDialog
{
	DECLARE_DYNAMIC(CLightDlg)
	GLfloat a_Light;
	
	GLfloat s_Light;
	GLfloat d_Light;

	GLfloat x_Lp; // 광원의 x좌표 값을 입력하기 위한 변수
	GLfloat y_Lp; // 광원의 y좌표 값을 입력하기 위한 변수
	GLfloat z_Lp; // 광원의 z좌표 값을 입력하기 위한 변수

public:
	CLightDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CLightDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_LIGHTDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEditDLight();
};
