// mfcglView.h : interface of the CMfcglView class
//
/////////////////////////////////////////////////////////////////////////////
#include <math.h>
#define Pmax 1000

class CMfcglView : public CView
{
protected: // create from serialization only
	CMfcglView();
	DECLARE_DYNCREATE(CMfcglView)

	// Attributes
public:
	CMfcglDoc* GetDocument();


	// Operations
public:
	void GLResize(GLsizei w, GLsizei h);
	void GLRenderScene(void* pData);
	void GLSetupRC(void *pData);

	HGLRC m_hRC;	// Rendering Context
	HDC m_hDC;		// Device Context

	CPalette m_GLPalette;	// Logical Palette

	GLfloat gl_left, gl_right, gl_top, gl_bottom;
	GLfloat width, height;

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMfcglView)
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

	// Implementation
public:
	virtual ~CMfcglView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	void InitializePalette(void);

	// Generated message map functions
protected:
	//{{AFX_MSG(CMfcglView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL OnQueryNewPalette();
	afx_msg void OnPaletteChanged(CWnd* pFocusWnd);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDrawLine();
	afx_msg void OnDrawPoint();
	afx_msg void OnDrawPolygon();
	afx_msg void OnTransformTranslation();
	afx_msg void OnTransformRotation();
	UINT m_DrawType;
	//GL_POINTS
	UINT m_NumOfDots;
	GLfloat m_LaPoint[Pmax][2]; 
	//GL_LINE
	UINT m_NumOfLine;
	GLfloat m_LbPoint[Pmax][2];
	GLfloat m_C[Pmax/2][3];
	//GL_POLYGON
	UINT m_NumOfPoly;
	GLfloat m_LcPoint[Pmax][2];
	afx_msg void OnDrawClear();
	//for Translation
	GLfloat m_xPos;
	GLfloat m_yPos;
	//for Rotation
	GLfloat m_xRot;
	GLfloat m_yRot;
	GLfloat m_yAngle, m_xAngle;
	CPoint m_MouseDPoint;
	bool b_Trans;
	bool b_Mmove;
	GLfloat move_x, move_y, m_x, m_y, premove_x, premove_y;
	GLfloat m_XScale, m_YScale, m_ZScale;
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
//	virtual HRESULT accDoDefaultAction(VARIANT varChild);
	void Trans(void);

	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
//	afx_msg void OnMouseLeave();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTransformScale();
	void drawcenter(void);

	void limit_check(GLfloat *value);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnTransformDepth();
	GLfloat m_depth;
	bool b_depth;
	bool b_strip;

	afx_msg void OnDrawTrianglestrip();
	bool b_perspective;

	afx_msg void OnViewPerspective();
	afx_msg void OnViewParallel();
	void RenderSetup(void);
	afx_msg void OnViewLight();
	GLfloat m_aLight; // ambient Light의 값을 받기 위한 변수
	bool b_light; // light 버튼의 클릭 확인을 위해 필요하다.
	void Light(void);
	GLfloat m_dLight; // Diffuse Light 값을 설정한 변수
	GLfloat m_sLight; // Specular 값을 설정하는 변수
	GLfloat m_xLp; // 광원 X좌표 값
	GLfloat m_yLp; // 광원 Y좌표 값
	GLfloat m_zLp; // 광원 Z좌표 값
	void ReduceToUnit(float vector[3]);
	void calcNormal(float v[3][3],float out[3]);
	void ReduceToUnit(void);
	void calcNormal(void);
};


#ifndef _DEBUG  // debug version in mfcglView.cpp
inline CMfcglDoc* CMfcglView::GetDocument()
{ return (CMfcglDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
