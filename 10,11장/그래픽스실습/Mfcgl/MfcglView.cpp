// mfcglView.cpp : implementation of the CMfcglView class
//

#include "stdafx.h"
#include "mfcgl.h"

#include "mfcglDoc.h"
#include "mfcglView.h"

#include <stdlib.h>
#include <time.h>
#include "ScaleDlg.h"
#include "ZdepthDlg.h"
#include "LightDlg.h"

#define glRGB(x, y, z)	glColor3ub((GLubyte)x, (GLubyte)y, (GLubyte)z)


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

double jkl=32154;

/////////////////////////////////////////////////////////////////////////////
// CMfcglView

IMPLEMENT_DYNCREATE(CMfcglView, CView)

BEGIN_MESSAGE_MAP(CMfcglView, CView)
	//{{AFX_MSG_MAP(CMfcglView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_QUERYNEWPALETTE()
	ON_WM_PALETTECHANGED()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_DRAW_LINE, &CMfcglView::OnDrawLine)
	ON_COMMAND(ID_DRAW_POINT, &CMfcglView::OnDrawPoint)
	ON_COMMAND(ID_DRAW_POLYGON, &CMfcglView::OnDrawPolygon)
	ON_COMMAND(ID_DRAW_CLEAR, &CMfcglView::OnDrawClear)
	ON_COMMAND(ID_BUTTON_MOVE, &CMfcglView::OnTransformTranslation)
	ON_COMMAND(ID_BUTTON_ROTA, &CMfcglView::OnTransformRotation)
	ON_COMMAND(ID_BUTTON_SCALE, &CMfcglView::OnTransformScale)
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONUP()
//	ON_WM_MOUSELEAVE()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEWHEEL()
	ON_COMMAND(ID_BUTTON_DEPTH, &CMfcglView::OnTransformDepth)
	ON_COMMAND(ID_DRAW_TRIANGLESTRIP, &CMfcglView::OnDrawTrianglestrip)
	ON_COMMAND(ID_VIEW_PERSPECTIVE, &CMfcglView::OnViewPerspective)
	ON_COMMAND(ID_VIEW_PARALLEL, &CMfcglView::OnViewParallel)
	ON_COMMAND(ID_VIEW_LIGHT, &CMfcglView::OnViewLight)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMfcglView construction/destruction

CMfcglView::CMfcglView()
{
	
	m_DrawType = 1;
	m_NumOfDots = 0;
	m_NumOfLine= 0;
	m_NumOfPoly= 0;

	m_xPos=0;
	m_yPos=0;
	m_xRot=0;
	m_yRot=0;
	b_Trans=false;
	m_yAngle=m_xAngle=0;
	b_Mmove=false;
	move_x = move_y = m_x = m_y = premove_x = premove_y =0;
	m_XScale = m_YScale = m_ZScale = 1;
	m_depth = 0;
	b_depth = false;
	b_strip=false;
	b_perspective = false;
	b_light=false;
}

CMfcglView::~CMfcglView()
{
}

BOOL CMfcglView::PreCreateWindow(CREATESTRUCT& cs)
{
	// Add Window styles required for OpenGL before window is created
	cs.style |= (WS_CLIPCHILDREN | WS_CLIPSIBLINGS | CS_OWNDC);

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMfcglView drawing

// Called when window receives WM_PAINT, render our scene
void CMfcglView::OnDraw(CDC* pDC)
{
	// Make the rendering context current
	wglMakeCurrent(m_hDC,m_hRC);

	// Call our external OpenGL code
	GLRenderScene(NULL);

	// Swap our scene to the front
	SwapBuffers(m_hDC);

	// Allow other rendering contexts to co-exist
	wglMakeCurrent(m_hDC,NULL);
}

	/////////////////////////////////////////////////////////////////////////////
	// CMfcglView diagnostics

#ifdef _DEBUG
void CMfcglView::AssertValid() const
{
	CView::AssertValid();
}

void CMfcglView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMfcglDoc* CMfcglView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMfcglDoc)));
	return (CMfcglDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMfcglView message handlers

int CMfcglView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	int nPixelFormat;					// Pixel format index
	m_hDC = ::GetDC(m_hWnd);			// Get the Device context

	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),	// Size of this structure
		1,								// Version of this structure	
		PFD_DRAW_TO_WINDOW |			// Draw to Window (not to bitmap)
		PFD_SUPPORT_OPENGL |			// Support OpenGL calls in window
		PFD_DOUBLEBUFFER,				// Double buffered mode
		PFD_TYPE_RGBA,					// RGBA Color mode
		24,								// Want 24bit color 
		0,0,0,0,0,0,					// Not used to select mode
		0,0,							// Not used to select mode
		0,0,0,0,0,						// Not used to select mode
		32,								// Size of depth buffer
		0,								// Not used to select mode
		0,								// Not used to select mode
		PFD_MAIN_PLANE,					// Draw in main plane
		0,								// Not used to select mode
		0,0,0 };						// Not used to select mode

		// Choose a pixel format that best matches that described in pfd
		nPixelFormat = ChoosePixelFormat(m_hDC, &pfd);

		// Set the pixel format for the device context
		VERIFY(SetPixelFormat(m_hDC, nPixelFormat, &pfd));

		// Create the rendering context
		m_hRC = wglCreateContext(m_hDC);

		// Make the rendering context current, perform initialization, then
		// deselect it
		VERIFY(wglMakeCurrent(m_hDC,m_hRC));
		GLSetupRC(m_hDC);
		wglMakeCurrent(NULL,NULL);

		// Create the palette if needed
		InitializePalette();

		return 0;
}


void CMfcglView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	RECT rect;
	GetClientRect(&rect);

	width = (float)(rect.right - rect.left);
	height = (float)(rect.bottom - rect.top);

	VERIFY(wglMakeCurrent(m_hDC,m_hRC));
	GLResize(cx, cy);
	VERIFY(wglMakeCurrent(NULL,NULL));
}

// The window is being destroyed, delete the rendering context,
// and release the device context
void CMfcglView::OnDestroy() 
{
	// Kill the timer
	KillTimer(101);

	// Clean up rendering context stuff
	wglDeleteContext(m_hRC);
	::ReleaseDC(m_hWnd,m_hDC);

	CView::OnDestroy();
}


// Override to keep the background from being erased everytime
// the window is repainted
BOOL CMfcglView::OnEraseBkgnd(CDC* pDC) 
{
	return FALSE;
}


// Initializes the CPalette object
void CMfcglView::InitializePalette(void)
{
	PIXELFORMATDESCRIPTOR pfd;	// Pixel Format Descriptor
	LOGPALETTE *pPal;			// Pointer to memory for logical palette
	int nPixelFormat;			// Pixel format index
	int nColors;				// Number of entries in palette
	int i;						// Counting variable
	BYTE RedRange,GreenRange,BlueRange;
	// Range for each color entry (7,7,and 3)

	// Get the pixel format index and retrieve the pixel format description
	nPixelFormat = GetPixelFormat(m_hDC);
	DescribePixelFormat(m_hDC, nPixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

	// Does this pixel format require a palette?  If not, do not create a
	// palette and just return NULL
	if(!(pfd.dwFlags & PFD_NEED_PALETTE))
		return;

	// Number of entries in palette.  8 bits yeilds 256 entries
	nColors = 1 << pfd.cColorBits;	

	// Allocate space for a logical palette structure plus all the palette entries
	pPal = (LOGPALETTE*)malloc(sizeof(LOGPALETTE) +nColors*sizeof(PALETTEENTRY));

	// Fill in palette header 
	pPal->palVersion = 0x300;		// Windows 3.0
	pPal->palNumEntries = nColors; // table size

	// Build mask of all 1's.  This creates a number represented by having
	// the low order x bits set, where x = pfd.cRedBits, pfd.cGreenBits, and
	// pfd.cBlueBits.  
	RedRange = (1 << pfd.cRedBits) -1;
	GreenRange = (1 << pfd.cGreenBits) - 1;
	BlueRange = (1 << pfd.cBlueBits) -1;

	// Loop through all the palette entries
	for(i = 0; i < nColors; i++)
	{
		// Fill in the 8-bit equivalents for each component
		pPal->palPalEntry[i].peRed = (i >> pfd.cRedShift) & RedRange;
		pPal->palPalEntry[i].peRed = (unsigned char)(
			(double) pPal->palPalEntry[i].peRed * 255.0 / RedRange);

		pPal->palPalEntry[i].peGreen = (i >> pfd.cGreenShift) & GreenRange;
		pPal->palPalEntry[i].peGreen = (unsigned char)(
			(double)pPal->palPalEntry[i].peGreen * 255.0 / GreenRange);

		pPal->palPalEntry[i].peBlue = (i >> pfd.cBlueShift) & BlueRange;
		pPal->palPalEntry[i].peBlue = (unsigned char)(
			(double)pPal->palPalEntry[i].peBlue * 255.0 / BlueRange);

		pPal->palPalEntry[i].peFlags = (unsigned char) NULL;
	}

	// Create the palette
	m_GLPalette.CreatePalette(pPal);

	// Go ahead and select and realize the palette for this device context
	SelectPalette(m_hDC,(HPALETTE)m_GLPalette,FALSE);
	RealizePalette(m_hDC);

	// Free the memory used for the logical palette structure
	free(pPal);
}

BOOL CMfcglView::OnQueryNewPalette() 
{
	// If the palette was created.
	if((HPALETTE)m_GLPalette)
	{
		int nRet;

		// Selects the palette into the current device context
		SelectPalette(m_hDC, (HPALETTE)m_GLPalette, FALSE);

		// Map entries from the currently selected palette to
		// the system palette.  The return value is the number 
		// of palette entries modified.
		nRet = RealizePalette(m_hDC);

		// Repaint, forces remap of palette in current window
		InvalidateRect(NULL,FALSE);

		return nRet;
	}

	return CView::OnQueryNewPalette();
}


void CMfcglView::OnPaletteChanged(CWnd* pFocusWnd) 
{
	if(((HPALETTE)m_GLPalette != NULL) && (pFocusWnd != this))
	{
		// Select the palette into the device context
		SelectPalette(m_hDC,(HPALETTE)m_GLPalette,FALSE);

		// Map entries to system palette
		RealizePalette(m_hDC);

		// Remap the current colors to the newly realized palette
		UpdateColors(m_hDC);
		return;
	}

	CView::OnPaletteChanged(pFocusWnd);
}


void CMfcglView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CMfcglDoc* pDoc = GetDocument();
	GLfloat x, y;

	x = point.x/width*(gl_right-gl_left)+gl_left;
	y = (height-point.y)/height*(gl_top-gl_bottom)+gl_bottom;

	if(m_NumOfDots < Pmax && m_DrawType==1)
	{
		m_LaPoint[m_NumOfDots][0]=x;
		m_LaPoint[m_NumOfDots][1]=y;
		++m_NumOfDots;
		Invalidate();
	}

	if(m_NumOfLine<Pmax && m_DrawType==2)
	{
		
		m_LbPoint[m_NumOfLine][0]=x;
		m_LbPoint[m_NumOfLine][1]=y;
		
		m_C[m_NumOfLine][0] = (GLfloat)(rand()%101)/100.0;
		m_C[m_NumOfLine][1] = (GLfloat)(rand()%101)/100.0;
		m_C[m_NumOfLine][2] = (GLfloat)(rand()%101)/100.0;
		++m_NumOfLine;
		Invalidate();
	}

	if(m_NumOfPoly<Pmax && m_DrawType==3)
	{
		m_LcPoint[m_NumOfPoly][0]=x;
		m_LcPoint[m_NumOfPoly][1]=y;
		++m_NumOfPoly;
		Invalidate();
	}

	
	if(m_DrawType==4)
	{
		m_x= x;
		m_y= y;
		b_Mmove=true;
		Invalidate();
	}

	CView::OnLButtonDown(nFlags, point);
}

////////////////////////////////////////////////////////////////

void CMfcglView::GLSetupRC(void *pData)
{
	// Black background
	glClearColor(0.52f, 0.7f, 1.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CW);
	glShadeModel(GL_SMOOTH);
	// Set drawing color to yellow
	//glColor3f(0.0f, 0.35f, 0.23f);
}



//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
// Called by Windows when it receives the WM_SIZE message.
// Put any code needed here to recalc the viewing volume and
// viewport info
void CMfcglView::GLResize(GLsizei w, GLsizei h)
{
	GLfloat nRange = 100.0f;

	// Prevent a divide by zero
	if(h == 0)
		h = 1;

	// Set Viewport to window dimensions
	glViewport(0, 0, w, h);

	// Reset coordinate system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Establish clipping volume (left, right, bottom, top, near, far)
	if (w <= h) 
	{	
		gl_left = -nRange;gl_right = nRange;gl_bottom = -nRange*h/w;gl_top = nRange*h/w;
		glOrtho (gl_left, gl_right, gl_bottom, gl_top, nRange, -nRange);		    
	}
	else
	{
		gl_left = -nRange*w/h;gl_right = nRange*w/h;gl_bottom = -nRange;gl_top = nRange;
		glOrtho (gl_left, gl_right, gl_bottom, gl_top, nRange, -nRange);		
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
// Render your OpenGL Scene here.
void CMfcglView::GLRenderScene(void *pData)
{
	CMfcglDoc* pDoc = GetDocument();
	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

	RenderSetup();
	Light();
	Trans();
	drawcenter();

	if(m_NumOfDots>0)
	{
		glPointSize(3.0f);
		glBegin(GL_POINTS);
		glColor3f(0.0f, 0.35f, 0.23f);
		for(UINT i=0; i<m_NumOfDots; i++)
		{
			glVertex3f(m_LaPoint[i][0],m_LaPoint[i][1],0.0f);
		}
		glEnd();
	}

	// for Line
	if(m_NumOfLine>0)
	{
		glLineWidth(4.0f);
		
		glBegin(GL_LINES); 
		
		for(UINT i=0; i< m_NumOfLine; i++)
		{
			if(i%2 == 0)
			{
				glColor3f(m_C[i/2][0], m_C[i/2][1], m_C[i/2][2]);
			}
			
			glVertex3f(m_LbPoint[i][0],m_LbPoint[i][1],0.0f);
			
			//glColor3f( (GLfloat)(rand()/jkl) , (GLfloat)(rand()/jkl) , (GLfloat)(rand()/jkl) );
		}
		glEnd();
	}

	//for Polygon
	if(m_NumOfPoly>0)
	{
		UINT i;
		if(b_strip)
		{
			float normal[3];

			glBegin(GL_TRIANGLE_STRIP);
			glColor3f(1.0f, 0.79f, 0.23f);
			for(UINT i=0; i<m_NumOfPoly; i++)
			{
				glNormal3f(0.0f,0.0f,-1.0f);
				glVertex3f(m_LcPoint[i][0], m_LcPoint[i][1], 0.0f);
			}
			glEnd();

			if(b_depth)
			{
				//깊이가 m_depth인 평면에 그린 그림
				glBegin(GL_TRIANGLE_STRIP);
				for(i=0; i<m_NumOfPoly; i++)
				{
					glNormal3f(0.0f, 0.0f, 1.0f);
					glVertex3f(m_LcPoint[i][0], m_LcPoint[i][1], m_depth);
				}
				glEnd();

				glBegin(GL_QUADS); // 도형의 옆면을 그리는 부분
				glColor3f(0.0f, 1.0f, 0.5f);
				for(i=0; i<m_NumOfPoly-1; i++)
				{
					unsigned int b=2;
					float v[3][3] = { {m_LcPoint[i][0], m_LcPoint[i][1],0},
									{m_LcPoint[i+1][0],m_LcPoint[i+1][1],0},
									{m_LcPoint[i+1][0],m_LcPoint[i+1][1],m_depth} };

					calcNormal(v,normal);
					glNormal3fv(normal);
					glVertex3f(m_LcPoint[i][0],m_LcPoint[i][1],0);
					glVertex3f(m_LcPoint[i+1][0],m_LcPoint[i+1][1],0);
					glVertex3f(m_LcPoint[i+1][0],m_LcPoint[i+1][1],m_depth);
					glVertex3f(m_LcPoint[i][0],m_LcPoint[i][1],m_depth);

					if(i!=m_NumOfPoly-1&& i!=m_NumOfPoly-2)
					{
						float v[3][3] = { {m_LcPoint[i][0], m_LcPoint[i][1],0},
										{m_LcPoint[i+2][0],m_LcPoint[i+2][1],0},
										{m_LcPoint[i+2][0],m_LcPoint[i+2][1],m_depth} };

						calcNormal(v,normal);
						glNormal3fv(normal);

						glVertex3f(m_LcPoint[i][0],m_LcPoint[i][1],0);
						glVertex3f(m_LcPoint[i+2][0],m_LcPoint[i+2][1],0);
						glVertex3f(m_LcPoint[i+2][0],m_LcPoint[i+2][1],m_depth);
						glVertex3f(m_LcPoint[i][0],m_LcPoint[i][1],m_depth);

					}
				}
				glEnd();
			}
		}
		else
		{
			float normal[3];

			glBegin(GL_POLYGON);
			glColor3f(1.0f, 0.79f, 0.23f);
			for(UINT i=0; i<m_NumOfPoly; i++)
			{
				glNormal3f(0.0f, 0.0f, -1.0f);
				glVertex3f(m_LcPoint[i][0],m_LcPoint[i][1],0.0f);
			}
			glEnd();

			if(b_depth)
			{
				glBegin(GL_POLYGON); // 깊이가 m_depth인 평면에 그린 그림
				for(UINT i=0; i<m_NumOfPoly; i++)
				{
					glNormal3f(0.0f,0.0f,1.0f);
					glVertex3f(m_LcPoint[i][0],m_LcPoint[i][1],m_depth);
				}
				glEnd();

				glBegin(GL_QUADS); // 도형의 옆면을 그리는 부분
				glColor3f(0.5f,0.3f,0.2f);
				for(i=0; i<m_NumOfPoly-1; i++)
				{
					float v[3][3] = { {m_LcPoint[i][0], m_LcPoint[i][1],0},
									{m_LcPoint[i+1][0],m_LcPoint[i+1][1],0},
									{m_LcPoint[i+1][0],m_LcPoint[i+1][1],m_depth} };

					calcNormal(v,normal);
					glVertex3f(m_LcPoint[i][0],m_LcPoint[i][1],0);
					glVertex3f(m_LcPoint[i+1][0],m_LcPoint[i+1][1],0);
					glVertex3f(m_LcPoint[i+1][0],m_LcPoint[i+1][1],m_depth);
					glVertex3f(m_LcPoint[i][0],m_LcPoint[i][1],m_depth);
				}
				float v[3][3] = { {m_LcPoint[0][0], m_LcPoint[0][1],m_depth},
								{m_LcPoint[i][0],m_LcPoint[i][1],m_depth},
								{m_LcPoint[i][0],m_LcPoint[i][1],0} };
				calcNormal(v,normal);
				glNormal3fv(normal);
				glVertex3f(m_LcPoint[0][0],m_LcPoint[0][1],m_depth);
				glVertex3f(m_LcPoint[i][0],m_LcPoint[i][1],m_depth);
				glVertex3f(m_LcPoint[i][0],m_LcPoint[i][1],0.0f);
				glVertex3f(m_LcPoint[0][0],m_LcPoint[0][1],0.0f);
				glEnd();
			}
		}
	}
		/*glBegin(GL_POLYGON); // 깊이가 0인 좌표평면의 도형
		for(i=0; i<m_NumOfPoly; i++)
		{
			glVertex3f(m_LcPoint[i][0],m_LcPoint[i][1],0.0f);
		}
		glEnd(); 

		if(b_depth)
		{
			glBegin(GL_POLYGON); // 깊이가 M_DEPTH인 평면에 그린 그림
			for(i=0; i<m_NumOfPoly;i++)
			{
				glVertex3f(m_LcPoint[i][0],m_LcPoint[i][1],m_depth);
			}
			glEnd();

			glBegin(GL_QUADS); // 입체도형의 옆면을 그리는 부분
			glColor3f(1.0f,0.0f,0.0f);
			for(i=0; i<m_NumOfPoly-1;i++)
			{
				glVertex3f(m_LcPoint[i][0],m_LcPoint[i][1],0);
				glVertex3f(m_LcPoint[i+1][0],m_LcPoint[i+1][1],0);
				glVertex3f(m_LcPoint[i+1][0],m_LcPoint[i+1][1],m_depth);
				glVertex3f(m_LcPoint[i][0],m_LcPoint[i][1],m_depth);
			}
			glVertex3f(m_LcPoint[0][0],m_LcPoint[0][1],m_depth);
			glVertex3f(m_LcPoint[i][0],m_LcPoint[i][1],m_depth);
			glVertex3f(m_LcPoint[i][0],m_LcPoint[i][1],0);
			glVertex3f(m_LcPoint[0][0],m_LcPoint[0][1],0);
			glEnd();
		}
	}  */ // 7과 3차원 도형

	/* {  // 기존면
		glLineWidth(3.0f);
		glBegin(GL_POLYGON);
		glColor3f(0.0f, 0.35f, 0.23f);
		for(UINT i=0; i<m_NumOfPoly;i++)
		{
			glVertex2f(m_LcPoint[i][0],m_LcPoint[i][1]);
		}
		glEnd();
	}*/ //기존 면
}




void CMfcglView::OnDrawLine()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_DrawType=2;
	/*m_xPos=0;
	m_yPos=0;
	m_xRot=0;
	m_yRot=0;
	m_xAngle=0;
	m_yAngle=0;*/
	Invalidate();
}


void CMfcglView::OnDrawPoint()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_DrawType=1;
	/*m_xPos=0;
	m_yPos=0;
	m_xRot=0;
	m_yRot=0;
	m_xAngle=0;
	m_yAngle=0;*/
	Invalidate();
}



void CMfcglView::OnDrawPolygon()
{
	m_DrawType=3;
	/*m_xPos=0;
	m_yPos=0;
	m_xRot=0;
	m_yRot=0;
	m_xAngle=0;
	m_yAngle=0;*/
	b_strip=false;
	Invalidate();
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CMfcglView::OnDrawClear()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_DrawType=0;
	m_NumOfDots=0;
	m_NumOfLine=0;
	m_NumOfPoly=0;
	m_xAngle=0;
	m_yAngle=0;
	m_xPos=0;
	m_yPos=0;
	m_xRot=0;
	m_yRot=0;
	b_depth=false;
	b_strip=false;
	Invalidate();
}


void CMfcglView::OnTransformTranslation()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_DrawType=4;
	b_Trans=true;
}



void CMfcglView::OnTransformRotation()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_DrawType=5;
	b_Trans=false;
}


void CMfcglView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
	switch(nChar)
	{
	case VK_UP: if(b_Trans)
				{		
					m_yPos +=5.0f;
				}
				else
				{
					m_xRot -=5.0f;
				}
				break;

	case VK_DOWN: if(b_Trans)
				  {
					  m_yPos -=5.0f;
				  }
				  else
				  {
					  m_xRot +=5.0f;
				  }
			      break;

	case VK_LEFT: if(b_Trans)
				  {
					  m_xPos -=5.0f;
				  }
			      else
				  {
					  m_yRot -=5.0f;
				  }
			      break;

	case VK_RIGHT: if(b_Trans)
				   {
					   m_xPos +=5.0f;
				   }
				   else
				   {
				       m_yRot +=5.0f;
				   }
				   break;

	case  VK_NUMPAD5 :  m_xPos =0.0f;
						m_yPos =0.0f;
				        m_xRot =0.0f;
						m_yRot =0.0f;
						break;
	}		
	
	CView::OnKeyDown(nChar,nRepCnt,nFlags);
	InvalidateRect(NULL,FALSE);
}


void CMfcglView::Trans(void)
{
	glLoadIdentity();

	glScalef(m_XScale, m_YScale, m_ZScale);

	if(m_DrawType==4)
	{
		glTranslatef(m_xPos, m_yPos, 0.0f);
		glTranslatef(move_x, move_y, 0.0f);
	}
	else
	{
		glRotatef(m_xRot,1.0f,0.0f,0.0f);
		glRotatef(m_yRot,0.0f,1.0f,0.0f);
	}
	glRotatef(m_xAngle, 1.0f, 0.0f, 0.0f);
	glRotatef(m_yAngle, 0.0f, 1.0f, 0.0f);
	
}


void CMfcglView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	premove_x = move_x;
	premove_y = move_y;
	b_Mmove = false;

	CView::OnLButtonUp(nFlags, point);
}


//void CMfcglView::OnMouseLeave()
//{
//	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
//
//	CView::OnMouseLeave();
//}


void CMfcglView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if(m_DrawType==4)
	{
		if(b_Mmove)
		{
			GLfloat x,y;
			x=point.x / width * (gl_right - gl_left) +gl_left;
			y=(height - point.y) / height* (gl_top - gl_bottom) +gl_bottom;
			move_x = premove_x + x -m_x;
			move_y = premove_y + y -m_y;
			Invalidate();
		}
	}

	if(m_DrawType==5)
	{
		if(GetCapture()==this)
		{
			m_xAngle +=(point.y- m_MouseDPoint.y)/3.6f;
			m_yAngle +=(point.x- m_MouseDPoint.x)/3.6f;
		
			InvalidateRect(NULL,FALSE);

			m_MouseDPoint=point;
		}
	}
	CView::OnMouseMove(nFlags, point);
}


void CMfcglView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_MouseDPoint=point;
	SetCapture();
	CView::OnRButtonDown(nFlags, point);
}


void CMfcglView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_MouseDPoint=CPoint(0,0);
	ReleaseCapture();
	CView::OnRButtonUp(nFlags, point);
}


void CMfcglView::OnTransformScale()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CScaleDlg dlg;
	if(dlg.DoModal()==IDOK)
	{
		if(dlg.x_Scale >0) m_XScale = dlg.x_Scale;
		if(dlg.y_Scale >0) m_YScale = dlg.y_Scale;
		if(dlg.z_Scale >0) m_ZScale = dlg.z_Scale;
		Invalidate();
	}
}


void CMfcglView::drawcenter(void)
{
	glBegin(GL_LINES);

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f,0.0f,0.0f);
	glVertex3f(40.0f,0.0f,0.0f);

	glColor3f(0.0f,1.0f,0.0f);
	glVertex3f(0.0f,0.0f,0.0f);
	glVertex3f(0.0f,40.0f,0.0f);

	glColor3f(0.0f,0.0f,1.0f);
	glVertex3f(0.0f,0.0f,0.0f);
	glVertex3f(0.0f,0.0f,40.0f);
	glEnd();
}


BOOL CMfcglView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if(m_DrawType == 4 || m_DrawType == 5) {
		if(zDelta>0)
		{
			m_XScale++;
			m_YScale++;
			m_ZScale++;
		}
		else
		{
			m_XScale--;
			m_YScale--;
			m_ZScale--;
		}
		limit_check(&m_XScale);
		limit_check(&m_YScale);
		limit_check(&m_ZScale);

		Invalidate();	
	}
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

void CMfcglView::limit_check(GLfloat* value){
	if(*value <= 0){
		*value = 1.0f;
	}else if(*value >= 10){
		*value = 10.0f;
	}
}

void CMfcglView::OnTransformDepth()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	b_depth = true;
	CZdepthDlg dlg;
	if(dlg.DoModal() == IDOK)
	{
		if(dlg.z_depth>0) m_depth=-dlg.z_depth;
		else m_depth=dlg.z_depth;
	}
	Invalidate();
}


void CMfcglView::OnDrawTrianglestrip()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	b_strip=true;
	m_DrawType=3;
	Invalidate();
}


void CMfcglView::OnViewPerspective()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	b_perspective = true;
	Invalidate();
}


void CMfcglView::OnViewParallel()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	b_perspective= false;
	Invalidate();
}


void CMfcglView::RenderSetup(void)
{
	GLfloat nRange = 100.0f;
	GLfloat lightPos[]= {m_xLp, m_yLp, m_zLp, 1.0f};
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if(b_perspective)
	{
		glViewport(0,0,width,height);

		GLfloat fAspect = width/height;
		gluPerspective(70.0f, fAspect,1.0f,500.0f);
		gluLookAt(0.0f, 0.0f, 143.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	}
	else
	{
		if(width <= height)
		{
			glOrtho(-nRange, nRange, -nRange*height/width, nRange*height/width, nRange, -nRange);
		}
		else
		{
			glOrtho(-nRange*width/height, nRange*width/height, -nRange, nRange, nRange, -nRange);
		}
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void CMfcglView::OnViewLight()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CLightDlg dlg;
	if(dlg.DoModal()==IDOK)
	{
		if(dlg.a_Light >=0)
		{
			m_aLight = dlg.a_Light/100.0F;
		}
		if(dlg.d_Light >=0)
		{
			m_dLight=dlg.d_Light/100.0f;
		}
		if(dlg.s_Light >=0)
		{
			m_sLight=dlg.s_Light/100.0f;
		}

		m_xLp = dlg.x_Lp;
		m_yLp = dlg.y_Lp;
		m_zLp = dlg.z_Lp;

		b_light=true;
	}
	Invalidate();
}


void CMfcglView::Light(void)
{
	//주변광 성분
	GLfloat ambientLight[] = {m_aLight, m_aLight, m_aLight, 1.0f};
	//난반사광 성분
	GLfloat diffuseLight[] = {m_dLight, m_dLight, m_dLight, 1.0f};
	//전반사광 성분
	GLfloat specular[] = {m_sLight, m_sLight, m_sLight, 1.0f};
	//전반사율
	GLfloat specref[] = {1.0f, 1.0f, 1.0f, 1.0f};


	if(b_light)
	{
		glEnable(GL_LIGHTING);

		glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight); // 주변광
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight); // 주변광
		glLightfv(GL_LIGHT0, GL_SPECULAR, specular); // 주변광

		glEnable(GL_LIGHT0); // GL_LIGHT0 광원을 사용가능하게 한다.

		//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
		glMaterialfv(GL_FRONT, GL_SPECULAR, specref); // 전면 전반사
		glMateriali(GL_FRONT, GL_SHININESS,125); // 전면 전반사 수치
	}
	else
	{
		glDisable(GL_LIGHTING);
	}
}


void CMfcglView::ReduceToUnit(float vector[3])
{
	float length;
	//벡터의 길이를 계산한다.
	length = (float)sqrt( (vector[0]*vector[0])+
						  (vector[1]*vector[1])+
						  (vector[2]*vector[2]) );

	//길이가 0에 가까운 벡터에게 적절한 값을 할당하여 프로그램이 폭주하지 않도록 한다.
	if(length == 0.0f) length =1.0f;

	//각 성분의 벡터의 길이로 나누면 단위 벡터가 된다.
	vector[0] /= length;
	vector[1] /= length;
	vector[2] /= length;
}


void CMfcglView::calcNormal(float v[3][3],float out[3])
{
	float v1[3],v2[3];
	static const int x=0;
	static const int y=1;
	static const int z=2;

	// 세 점으로부터 2개의 벡터를 구한다.
	v1[x]= v[1][x]- v[0][x];
	v1[y]= v[1][y]- v[0][y];
	v1[z]= v[1][z]- v[0][z];

	v2[x]= v[2][x]- v[0][x];
	v2[y]= v[2][y]- v[0][y];
	v2[z]= v[2][z]- v[0][z];

	//법선 벡터를 구하기 위해 두 벡터의 외적을 구한다.
	//결과는 out[]에 저장된다.
	out[x]= v1[y]*v2[z]- v1[z]*v2[y];
	out[y]= v1[z]*v2[x]- v1[x]*v2[z];
	out[z]= v1[x]*v2[y]- v1[y]*v2[x];

	//벡터를 정규화한다(길이를 1로 줄인다)
	ReduceToUnit(out);
}
