// ZdepthDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Mfcgl.h"
#include "ZdepthDlg.h"
#include "afxdialogex.h"


// CZdepthDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CZdepthDlg, CDialog)

CZdepthDlg::CZdepthDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CZdepthDlg::IDD, pParent)
	, z_depth(0)
{
	z_depth=0;
}

CZdepthDlg::~CZdepthDlg()
{
	z_depth=0;
}

void CZdepthDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_Z, z_depth);
}


BEGIN_MESSAGE_MAP(CZdepthDlg, CDialog)
END_MESSAGE_MAP()


// CZdepthDlg �޽��� ó�����Դϴ�.
