
#include "Diagram.h"
#include "Class.h"
#include "DrawingClass.h"
#include "DefaultState.h"
#include "Selection.h"
#include "Finder.h"
#include "ClassDiagramForm.h" //�ӽ�


DrawingClass* DrawingClass::instance = 0;

MouseLButtonAction* DrawingClass::Instance() {
	if (instance == 0) {
		instance = new DrawingClass;
	}
	return instance;
}
void DrawingClass::MouseLButtonUp(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY){

		
	if (currentX - startX < 120) {
		currentX = startX + 120;
	}
	if (currentY - startY < 150) {
		currentY = startY + 150;
	}

	//Ŭ������ �Ȱ�ġ�� �ҷ��� ���⿡ ����
	Long i = 0;
	Finder finder;
	bool ret = false;
	while (i < diagram->GetLength() && ret == false) {
		FigureComposite *figures =static_cast<FigureComposite*>(diagram->GetAt(i));
		CRect cRect(startX, startY, currentX, currentY);
		CRect cRect1(figures->GetX(), figures->GetY(),figures->GetWidth() + figures->GetX(),figures->GetY() + figures->GetHeight());
		ret = finder.FindRectangleByArea(cRect, cRect1); 
		i++;
	}

	if (ret == false) {
		Long index = diagram->AddClass(startX, startY, currentX - startX, currentY - startY);
		Class *object = static_cast<Class*>(diagram->GetAt(index));
		object->Initialize();
	}
		this->ChangeDefault(mouseLButton);
}
void DrawingClass::MouseLButtonDown(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY){

	
}
void DrawingClass::MouseLButtonDrag(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY, CPaintDC *cPaintDC) {

	ClassDiagramForm *classDiagramForm = (ClassDiagramForm*)(CFrameWnd::FindWindow(NULL, "classDiagram"));

	CRect rect;
	classDiagramForm->GetClientRect(&rect);
	CDC *cDc = classDiagramForm->GetDC();
	CDC memDc;
	CBitmap *pOldBitmap;
	CBitmap bmp;

	memDc.CreateCompatibleDC(cDc);
	bmp.CreateCompatibleBitmap(cDc, rect.Width(), rect.Height());
	pOldBitmap = memDc.SelectObject(&bmp);
	memDc.PatBlt(0, 0, rect.Width(), rect.Height(), WHITENESS);
	
	//LoadImage
	memDc.Rectangle(startX, startY, currentX, currentY);
	cDc->BitBlt(0, 0, rect.Width(), rect.Height(), &memDc, 0, 0, SRCCOPY);

	memDc.SelectObject(pOldBitmap);
	memDc.DeleteDC();

/*
	CPen pen;
	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	CPen *oldPen = cPaintDC->SelectObject(&pen);
	cPaintDC->SetBkMode(TRANSPARENT);
	cPaintDC->Rectangle(startX, startY, currentX, currentY);
	cPaintDC->SelectObject(oldPen);
	pen.DeleteObject();*/
}