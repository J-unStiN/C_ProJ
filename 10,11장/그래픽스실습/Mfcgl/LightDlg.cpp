// LightDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Mfcgl.h"
#include "LightDlg.h"
#include "afxdialogex.h"


// CLightDlg ��ȭ �����Դϴ�.

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


// CLightDlg �޽��� ó�����Դϴ�.


void CLightDlg::OnEnChangeEditDLight()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
