#include "DrawingDependency.h"
#include "DefaultState.h"
#include "Figure.h"
#include "Selection.h"
#include "Class.h"
#include "Finder.h"
#include "Dependency.h"
#include "SelfDependency.h"


DrawingDependency* DrawingDependency::instance = 0;

MouseLButtonAction* DrawingDependency::Instance() {
	if (instance == 0) {
		instance = new DrawingDependency;
	}
	return instance;
}

void DrawingDependency::MouseLButtonUp(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {
	Long index;
	Figure *figure = 0;

	//if (selection->GetLength() == 1 && dynamic_cast<Class*>(selection->GetAt(0))) {

	selection->SelectByPoint(diagram, currentX, currentY);

	if (selection->GetLength() == 2 && selection->GetAt(0) != selection->GetAt(1) && dynamic_cast<Class*>(selection->GetAt(1))) {

		CPoint lineStart(startX, startY);
		CPoint lineEnd(currentX, currentY);

		CRect rect(selection->GetAt(0)->GetX(), selection->GetAt(0)->GetY(),
			selection->GetAt(0)->GetX() + selection->GetAt(0)->GetWidth(),
			selection->GetAt(0)->GetY() + selection->GetAt(0)->GetHeight());

		Finder finder;
		CPoint cross1 = finder.GetCrossPoint(lineStart, lineEnd, rect);

		rect.left = selection->GetAt(1)->GetX();
		rect.top = selection->GetAt(1)->GetY();
		rect.right = selection->GetAt(1)->GetX() + selection->GetAt(1)->GetWidth();
		rect.bottom = selection->GetAt(1)->GetY() + selection->GetAt(1)->GetHeight();
		CPoint cross2 = finder.GetCrossPoint(lineStart, lineEnd, rect);

		Dependency object(cross1.x, cross1.y, cross2.x - cross1.x, cross2.y - cross1.y);
		index = static_cast<FigureComposite*>(selection->GetAt(0))->Add(object.Clone());
		figure = static_cast<FigureComposite*>(selection->GetAt(0))->GetAt(index);

	}

	if (selection->GetLength() == 2 && selection->GetAt(0) == selection->GetAt(1)) {
		Class *object = static_cast<Class*>(selection->GetAt(0));
		SelfDependency selfDependency(object->GetX() + object->GetWidth() - 30, object->GetY(), 30, 30);
		index = object->Add(selfDependency.Clone());
		figure = object->GetAt(index);
	}
	selection->DeleteAllItems();
	this->ChangeDefault(mouseLButton);
}
void DrawingDependency::MouseLButtonDown(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY) {
	selection->DeleteAllItems();
	selection->SelectByPoint(diagram, currentX, currentY);
}

void DrawingDependency::MouseLButtonDrag(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY, CDC *cPaintDC) {
	if (startX == currentX&&startY == currentY) {
		selection->DeleteAllItems();
		selection->SelectByPoint(diagram, currentX, currentY);
	}
	CPen pen;
	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	CPen *oldPen = cPaintDC->SelectObject(&pen);
	cPaintDC->SetBkMode(TRANSPARENT);
	cPaintDC->MoveTo(startX, startY);
	cPaintDC->LineTo(currentX, currentY);
	cPaintDC->SelectObject(oldPen);
	pen.DeleteObject();

	double degree = atan2(currentX - startX, startY - currentY); // ����

	double distance = sqrt(pow(currentX - startX, 2) + pow(startY - currentY, 2));
	// ��Ʈ�ȿ� = ��Ʈ(����(
	double dX = (currentX)-(10 * (currentX - startX) / distance); //�ڷ� �� ������ x
	double dY = (currentY)+(10 * (startY - currentY) / distance); //�ڷ� �� ������ y

																  // ���� ����

	CPoint pts[3];

	pts[0].x = (currentX); //���콺 ������ġ ��
	pts[0].y = (currentY);

	pts[1].x = static_cast<LONG>(dX - 10 * cos(degree)); // ����
	pts[1].y = static_cast<LONG>(dY - 10 * sin(degree));

	pts[2].x = static_cast<LONG>(dX + 10 * cos(degree)); // �Ʒ���
	pts[2].y = static_cast<LONG>(dY + 10 * sin(degree));

	cPaintDC->MoveTo(pts[0].x, pts[0].y);
	cPaintDC->LineTo(pts[1].x, pts[1].y);

	cPaintDC->MoveTo(pts[0].x, pts[0].y);
	cPaintDC->LineTo(pts[2].x, pts[2].y);

}