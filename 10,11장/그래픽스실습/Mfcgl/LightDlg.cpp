// LightDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Mfcgl.h"
#include "LightDlg.h"
#include "afxdialogex.h"


// CLightDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CLightDlg, CDialog)

CLightDlg::CLightDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLightDlg::IDD, pParent)
	,a_Light(0)
{
	a_Light = 20.0f;

	d_Light = 80.0f;
	s_Light = 100.0f;

	x_Lp = 50.0f;
	y_Lp = 50.0f;
	z_Lp = 100.0f;
}

CLightDlg::~CLightDlg()
{

}

void CLightDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ALight, a_Light);
	DDX_Text(pDX, IDC_EDIT_DLight, d_Light);
	DDX_Text(pDX, IDC_EDIT_SLight, s_Light);

	DDX_Text(pDX, IDC_EDIT_LpX, x_Lp);
	DDX_Text(pDX, IDC_EDIT_LpY, y_Lp);
	DDX_Text(pDX, IDC_EDIT_LpZ, z_Lp);

}


BEGIN_MESSAGE_MAP(CLightDlg, CDialog)
	ON_EN_CHANGE(IDC_EDIT_DLight, &CLightDlg::OnEnChangeEditDLight)
END_MESSAGE_MAP()


// CLightDlg 메시지 처리기입니다.


void CLightDlg::OnEnChangeEditDLight()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
