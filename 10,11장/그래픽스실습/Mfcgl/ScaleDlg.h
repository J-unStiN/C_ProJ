#pragma once


// CScaleDlg ��ȭ �����Դϴ�.

class CScaleDlg : public CDialog
{
	DECLARE_DYNAMIC(CScaleDlg)

public:
	CScaleDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CScaleDlg();
	float z_Scale;
	float y_Scale;
	float x_Scale;
// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SCALEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
