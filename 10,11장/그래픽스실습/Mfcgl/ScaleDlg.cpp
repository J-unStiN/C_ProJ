// ScaleDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Mfcgl.h"
#include "ScaleDlg.h"
#include "afxdialogex.h"


// CScaleDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CScaleDlg, CDialog)

CScaleDlg::CScaleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CScaleDlg::IDD, pParent)
{
	x_Scale=1.0f;
	y_Scale=1.0f;
	z_Scale=1.0f;
}

CScaleDlg::~CScaleDlg()
{
}

void CScaleDlg::DoDataExchange(CDataExchange* pDX)
{ 
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_X, x_Scale);
	DDX_Text(pDX, IDC_EDIT_Y, y_Scale);
	DDX_Text(pDX, IDC_EDIT_Z, z_Scale);
}


BEGIN_MESSAGE_MAP(CScaleDlg, CDialog)
END_MESSAGE_MAP()


// CScaleDlg �޽��� ó�����Դϴ�.
