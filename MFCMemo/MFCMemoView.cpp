
// MFCMemoView.cpp: CMFCMemoView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFCMemo.h"
#endif

#include "MFCMemoDoc.h"
#include "MFCMemoView.h"

#ifdef _DEBUG
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#define new DEBUG_NEW
#endif


// CMFCMemoView

IMPLEMENT_DYNCREATE(CMFCMemoView, CView)

BEGIN_MESSAGE_MAP(CMFCMemoView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_EDIT_CUT, &CMFCMemoView::OnEditCut)
	ON_COMMAND(ID_EDIT_COPY, &CMFCMemoView::OnEditCopy)
	ON_COMMAND(ID_32771, &CMFCMemoView::OnTest)

	ON_COMMAND(ID_EDIT_PASTE, &CMFCMemoView::OnEditPaste)
//	ON_COMMAND(ID_FILE_CLOSE, &CMFCMemoView::OnFileClose)
//	ON_COMMAND(ID_FILE_OPEN, &CMFCMemoView::OnFileOpen)
//	ON_COMMAND(ID_FILE_SAVE, &CMFCMemoView::OnFileSave)
	ON_COMMAND(ID_EDIT_UNDO, &CMFCMemoView::OnEditUndo)
END_MESSAGE_MAP()

// CMFCMemoView 생성/소멸

CMFCMemoView::CMFCMemoView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	
}

CMFCMemoView::~CMFCMemoView()
{
}

BOOL CMFCMemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMFCMemoView 그리기

void CMFCMemoView::OnDraw(CDC* /*pDC*/)
{
	CMFCMemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CMFCMemoView 인쇄

BOOL CMFCMemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMFCMemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFCMemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMFCMemoView 진단

#ifdef _DEBUG
void CMFCMemoView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCMemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCMemoDoc* CMFCMemoView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCMemoDoc)));
	return (CMFCMemoDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCMemoView 메시지 처리기


int CMFCMemoView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	TRACE0("CMFCMemoView::OnCreate()\n");
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	CMFCMemoDoc* pd = GetDocument();

	CRect rect(0,0,0,0);
	pd->mEdit.Create(
		ES_AUTOHSCROLL | 
		ES_AUTOVSCROLL | 
		ES_WANTRETURN | 
		WS_VISIBLE | 
		WS_CHILD, 
		rect, 
		this, 
		1);

	return 0;
}


void CMFCMemoView::OnSize(UINT nType, int cx, int cy)
{
	TRACE2("CMFCMemoView::OnSize(),%d,%d\n",cx,cy);
	CView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CMFCMemoDoc* pd = GetDocument();
	CRect rect;
	GetClientRect(rect);
	pd->mEdit.SetWindowPos(
		&wndTop,
		0,0,
		rect.right-rect.left,
		rect.bottom-rect.top,
		SWP_SHOWWINDOW
	);
}


BOOL CMFCMemoView::OnCommand(WPARAM wParam, LPARAM lParam)
{
	TRACE2("CMFCMemoView::OnCommand(),%d,%d\n", LOWORD(wParam), HIWORD(wParam));
	//printf("CMFCMemoView::OnCommand(),%d,%d\n", LOWORD(wParam), HIWORD(wParam));
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CMFCMemoDoc* pd = GetDocument();
	switch (LOWORD(wParam))
	{
	case 1:
		switch (HIWORD(wParam))
		{
		case EN_CHANGE:
			pd->SetModifiedFlag(TRUE);
		default:
			break;
		}
	default:
		break;
	}
	return CView::OnCommand(wParam, lParam);
}


void CMFCMemoView::OnEditCut()
{
	TRACE0("CMFCMemoView::OnEditCut()\n");
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCMemoDoc* pd = GetDocument();
	pd->mEdit.Cut();
}


void CMFCMemoView::OnEditCopy()
{
	TRACE0("CMFCMemoView::OnEditCopy()\n");
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCMemoDoc* pd = GetDocument();
	pd->mEdit.Copy();
}


void CMFCMemoView::OnTest()
{
	TRACE0("CMFCMemoView::OnTest()\n");
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}




void CMFCMemoView::OnEditPaste()
{
	TRACE0("CMFCMemoView::OnEditPaste()\n");
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCMemoDoc* pd = GetDocument();
	pd->mEdit.Paste();
}


//void CMFCMemoView::OnFileClose()
//{
//	// TODO: 여기에 명령 처리기 코드를 추가합니다.
//}


//void CMFCMemoView::OnFileOpen()
//{
//	// TODO: 여기에 명령 처리기 코드를 추가합니다.
//}


//void CMFCMemoView::OnFileSave()
//{
//	// TODO: 여기에 명령 처리기 코드를 추가합니다.
//}


void CMFCMemoView::OnEditUndo()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCMemoDoc* pd = GetDocument();
	pd->mEdit.Undo();
}
