#pragma once


// CLightDlg ��ȭ �����Դϴ�.

class CLightDlg : public CDialog
{
	DECLARE_DYNAMIC(CLightDlg)
	GLfloat a_Light;
	
	GLfloat s_Light;
	GLfloat d_Light;

	GLfloat x_Lp; // ������ x��ǥ ���� �Է��ϱ� ���� ����
	GLfloat y_Lp; // ������ y��ǥ ���� �Է��ϱ� ���� ����
	GLfloat z_Lp; // ������ z��ǥ ���� �Է��ϱ� ���� ����

public:
	CLightDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CLightDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_LIGHTDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEditDLight();
};
