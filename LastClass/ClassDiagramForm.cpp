//ClassDiagramForm.cpp

#include "ClassDiagramForm.h"
#include "Diagram.h"

BEGIN_MESSAGE_MAP(ClassDiagramForm, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

ClassDiagramForm::ClassDiagramForm() { // ������ �´µ�
	this->diagram = NULL;
	this->startX = 0;
	this->startY = 0;
	this->currentX = 0;
	this->currentY = 0;
}


int ClassDiagramForm::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	
	CFrameWnd::OnCreate(lpCreateStruct); //�ڵ����� �������̵� //��ӿ���
	
	this->diagram = new Diagram;
	/*
	this->diagram->Add(100, 100, 30, 30);
	this->diagram->Add(200, 200, 50, 50);
	this->diagram->Add(500, 500, 140, 140);
	// */
	return 0;
}

void ClassDiagramForm::OnPaint() {
	CPaintDC dc(this); // �̰� ����?

	Long length = this->diagram->GetLength();
	Long i = 0;
	Long x;
	Long y;
	Long width;
	Long height;
	Class object;

	CPen pen;
	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	CPen *oldPen = dc.SelectObject(&pen);
	dc.Rectangle(startX, startY, this->currentX, this->currentY);
	dc.SelectObject(oldPen);
	pen.DeleteObject();
	while (i < length) {
		object = this->diagram->GetAt(i);
		x = object.GetX();
		y = object.GetY();
		width = object.GetWidth();
		height = object.GetHeight();
		dc.Rectangle(x, y, x + width, y + height); ////////////// �簢���� �����
		i++;
	}
}
/*void ClassDiagramForm::OnDrawDot() {
	CClientDC dc(this);
	CPen pen;
	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	CPen *oldPen = dc.SelectObject(&pen);
	dc.Rectangle(startX, startY, this->currentX, this->currentY);
	dc.SelectObject(oldPen);
	pen.DeleteObject();
}
*/

void ClassDiagramForm::OnLButtonDown(UINT nFlags, CPoint point) {
	this->startX = point.x;
	this->startY = point.y;
	this->currentX = point.x;
	this->currentY = point.y;
}

void ClassDiagramForm::OnLButtonUp(UINT nFlags, CPoint point) {
	this->currentX = point.x;
	this->currentY = point.y;
	if (this->currentX - this->startX < 120) {
		this->currentX = this->startX + 120;
	}
	if (this->currentY - this->startY< 150){
		this->currentY = this->startY + 150;	
	}
	this->diagram->Add(this->startX, this->startY, this->currentX- this->startX, this->currentY- this->startY);
	Invalidate();
}

void ClassDiagramForm::OnMouseMove(UINT nFlags, CPoint point) {
	if (nFlags == MK_LBUTTON) {
		this->currentX = point.x;
		this->currentY = point.y;
		Invalidate();
	}
}


void ClassDiagramForm::OnClose() {
	if (this->diagram != NULL) {
		delete this->diagram;
		//this->diagram = NULL;
	}
	CFrameWnd::OnClose(); // �������̵� �ڵ�����
}
