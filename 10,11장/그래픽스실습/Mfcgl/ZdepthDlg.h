#pragma once


// CZdepthDlg ��ȭ �����Դϴ�.

class CZdepthDlg : public CDialog
{
	DECLARE_DYNAMIC(CZdepthDlg)

public:
	CZdepthDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CZdepthDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DEPTHDLG };
	float z_depth;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};