// ScaleDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Mfcgl.h"
#include "ScaleDlg.h"
#include "afxdialogex.h"


// CScaleDlg 대화 상자입니다.

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


// CScaleDlg 메시지 처리기입니다.
