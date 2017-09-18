//DrawingVisitor.cpp

#include"DrawingVisitor.h"
#include "Class.h"
#include "Line.h"
#include "Generalization.h"
#include "Realization.h"
#include "Dependency.h"
#include "Association.h"
#include "DirectedAssociation.h"
#include "Aggregation.h"
#include "Aggregations.h"
#include "Composition.h"
#include "Compositions.h"
#include "Template.h"
#include "MemoBox.h"
#include "Selection.h"
#include "MemoLine.h"
#include <iostream>
#include <afxwin.h>
using namespace std;

DrawingVisitor::DrawingVisitor() {
}

void DrawingVisitor::Visit(Class *object, CDC* cPaintDc) {

	Long x = object->GetX();
	Long y = object->GetY();
	Long width = object->GetWidth();
	Long height = object->GetHeight();



	cPaintDc->Rectangle(x, y, x + width, y + height);
}
void DrawingVisitor::Visit(Line *line, CDC* cPaintDc) {
	Long x = line->GetX();
	Long  y = line->GetY();;
	Long width = line->GetWidth();


	cPaintDc->MoveTo(x, y);
	cPaintDc->LineTo(x + width, y);
}

void DrawingVisitor::Visit(SingleByteCharacter *singleByteCharacter, CDC* cPaintDc) {
}

void DrawingVisitor::Visit(DoubleByteCharacter *doubleByteCharacter, CDC* cPaintDc) {
}
void DrawingVisitor::Visit(Row* row, CDC* cPaintDc) {
}
void DrawingVisitor::Visit(Text* text, CDC* cPaintDc) {
}

void DrawingVisitor::Visit(Generalization *generalization, CDC* cPaintDc) {
	

	Long startX = generalization->GetX();
	Long startY = generalization->GetY();
	Long endX;
	Long endY;
	Long i = 0;
	while (i < generalization->GetLength()) {
		endX = generalization->GetAt(i).x;
		endY = generalization->GetAt(i).y;
		cPaintDc->MoveTo(startX, startY);
		cPaintDc->LineTo(endX, endY);
		startX = endX;
		startY = endY;
		i++;
	}
	endX = generalization->GetWidth() + generalization->GetX();
	endY = generalization->GetHeight() + generalization->GetY();

	cPaintDc->MoveTo(startX, startY);
	cPaintDc->LineTo(endX, endY);

	CBrush white(RGB(255, 255, 255));
	CBrush myBrush;
	myBrush.CreateSolidBrush(RGB(255, 255, 255));
	CBrush *oldBrush = cPaintDc->SelectObject(&myBrush);

	double degree = atan2(endX - startX, startY - endY); // 기울기

	double distance = sqrt(pow(endX - startX, 2) + pow(startY - endY, 2));
	// 루트안에 = 루트(제곱(
	double dX = (endX)-(15 * (endX - startX) / distance); //뒤로 온 기준점 x
	double dY = (endY)+(15 * (startY - endY) / distance); //뒤로 온 기준점 y

														  // 수직 기울기

	CPoint pts[3];

	pts[0].x = (endX); //마우스 현재위치 점
	pts[0].y = (endY);

	pts[1].x = static_cast<LONG>(dX - 15 * cos(degree)); // 윗점
	pts[1].y = static_cast<LONG>(dY - 15 * sin(degree));

	pts[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // 아랫점
	pts[2].y = static_cast<LONG>(dY + 15 * sin(degree));

	cPaintDc->SelectObject(&white);
	cPaintDc->Polygon(pts, 3);
	cPaintDc->SelectObject(oldBrush);
	myBrush.DeleteObject();
}

void DrawingVisitor::Visit(Realization *realization, CDC* cPaintDc) {
	CPen pen;
	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	CPen *oldPen = cPaintDc->SelectObject(&pen);
	cPaintDc->SetBkMode(TRANSPARENT);


	Long startX = realization->GetX();
	Long startY = realization->GetY();
	Long endX;
	Long endY;
	Long i = 0;
	while (i < realization->GetLength()) {
		endX = realization->GetAt(i).x;
		endY = realization->GetAt(i).y;
		cPaintDc->MoveTo(startX, startY);
		cPaintDc->LineTo(endX, endY);
		startX = endX;
		startY = endY;
		i++;
	}
	endX = realization->GetWidth() + realization->GetX();
	endY = realization->GetHeight() + realization->GetY();

	cPaintDc->MoveTo(startX, startY);
	cPaintDc->LineTo(endX, endY);

	cPaintDc->SelectObject(oldPen);
	pen.DeleteObject();

	CBrush white(RGB(255, 255, 255));
	CBrush myBrush;
	myBrush.CreateSolidBrush(RGB(255, 255, 255));
	CBrush *oldBrush = cPaintDc->SelectObject(&myBrush);

	double degree = atan2(endX - startX, startY - endY); // 기울기

	double distance = sqrt(pow(endX - startX, 2) + pow(startY - endY, 2));
	// 루트안에 = 루트(제곱(
	double dX = (endX)-(15 * (endX - startX) / distance); //뒤로 온 기준점 x
	double dY = (endY)+(15 * (startY - endY) / distance); //뒤로 온 기준점 y

														  // 수직 기울기

	CPoint pts[3];

	pts[0].x = endX; //마우스 현재위치 점
	pts[0].y = endY;

	pts[1].x = static_cast<LONG>(dX - 15 * cos(degree)); // 윗점
	pts[1].y = static_cast<LONG>(dY - 15 * sin(degree));

	pts[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // 아랫점
	pts[2].y = static_cast<LONG>(dY + 15 * sin(degree));

	cPaintDc->SelectObject(&white);
	cPaintDc->Polygon(pts, 3);
	cPaintDc->SelectObject(oldBrush);
	myBrush.DeleteObject();
}

void DrawingVisitor::Visit(Dependency *dependency, CDC* cPaintDc) {

	CPen pen;
	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	CPen *oldPen = cPaintDc->SelectObject(&pen);
	cPaintDc->SetBkMode(TRANSPARENT);

	Long startX = dependency->GetX();
	Long startY = dependency->GetY();
	Long endX;
	Long endY;
	Long i = 0;
	while (i < dependency->GetLength()) {
		endX = dependency->GetAt(i).x;
		endY = dependency->GetAt(i).y;
		cPaintDc->MoveTo(startX, startY);
		cPaintDc->LineTo(endX, endY);
		startX = endX;
		startY = endY;
		i++;
	}
	endX = dependency->GetWidth() + dependency->GetX();
	endY = dependency->GetHeight() + dependency->GetY();

	cPaintDc->MoveTo(startX, startY);
	cPaintDc->LineTo(endX, endY);
	cPaintDc->SelectObject(oldPen);
	pen.DeleteObject();

	double degree = atan2(endX - startX, startY - endY); // 기울기

	double distance = sqrt(pow(endX - startX, 2) + pow(startY - endY, 2));
	// 루트안에 = 루트(제곱(
	double dX = (endX)-(15 * (endX - startX) / distance); //뒤로 온 기준점 x
	double dY = (endY)+(15 * (startY - endY) / distance); //뒤로 온 기준점 y

														  // 수직 기울기

	CPoint pts[3];

	pts[0].x = endX; //마우스 현재위치 점
	pts[0].y = endY;

	pts[1].x = static_cast<LONG>(dX - 15 * cos(degree)); // 윗점
	pts[1].y = static_cast<LONG>(dY - 15 * sin(degree));

	pts[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // 아랫점
	pts[2].y = static_cast<LONG>(dY + 15 * sin(degree));

	cPaintDc->MoveTo(pts[0].x, pts[0].y);
	cPaintDc->LineTo(pts[1].x, pts[1].y);

	cPaintDc->MoveTo(pts[0].x, pts[0].y);
	cPaintDc->LineTo(pts[2].x, pts[2].y);
}

void DrawingVisitor::Visit(Association *association, CDC* cPaintDc) { 

	Long startX = association->GetX();
	Long startY = association->GetY();
	Long endX;
	Long endY;
	Long i = 0;
	while (i < association->GetLength()) {
		endX = association->GetAt(i).x;
		endY = association->GetAt(i).y;
		cPaintDc->MoveTo(startX, startY);
		cPaintDc->LineTo(endX, endY);
		startX = endX;
		startY = endY;
		i++;
	}
	endX = association->GetWidth() + association->GetX();
	endY = association->GetHeight() + association->GetY();
	cPaintDc->MoveTo(startX, startY);
	cPaintDc->LineTo(endX, endY);
}

void DrawingVisitor::Visit(DirectedAssociation *directedAssociation, CDC* cPaintDc) {

	Long startX = directedAssociation->GetX();
	Long startY = directedAssociation->GetY();
	Long endX;
	Long endY;
	Long i = 0;
	while (i < directedAssociation->GetLength()) {
		endX = directedAssociation->GetAt(i).x;
		endY = directedAssociation->GetAt(i).y;
		cPaintDc->MoveTo(startX, startY);
		cPaintDc->LineTo(endX, endY);
		startX = endX;
		startY = endY;
		i++;
	}
	endX = directedAssociation->GetWidth() + directedAssociation->GetX();
	endY = directedAssociation->GetHeight() + directedAssociation->GetY();
	cPaintDc->MoveTo(startX, startY);
	cPaintDc->LineTo(endX, endY);

	double degree = atan2(endX - startX, startY - endY); // 기울기

	double distance = sqrt(pow(endX - startX, 2) + pow(startY - endY, 2));
	// 루트안에 = 루트(제곱(
	double dX = (endX)-(15 * (endX - startX) / distance); //뒤로 온 기준점 x
	double dY = (endY)+(15 * (startY - endY) / distance); //뒤로 온 기준점 y

														  // 수직 기울기

	CPoint pts[3];

	pts[0].x = endX; //마우스 현재위치 점
	pts[0].y = endY;

	pts[1].x = static_cast<LONG>(dX - 15 * cos(degree)); // 윗점
	pts[1].y = static_cast<LONG>(dY - 15 * sin(degree));

	pts[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // 아랫점
	pts[2].y = static_cast<LONG>(dY + 15 * sin(degree));

	cPaintDc->MoveTo(pts[0].x, pts[0].y);
	cPaintDc->LineTo(pts[1].x, pts[1].y);

	cPaintDc->MoveTo(pts[0].x, pts[0].y);
	cPaintDc->LineTo(pts[2].x, pts[2].y);
}

void DrawingVisitor::Visit(Aggregation *aggregation, CDC* cPaintDc) {

	Long startX = aggregation->GetX();
	Long startY = aggregation->GetY();
	Long endX;
	Long endY;
	Long i = 0;

	while (i < aggregation->GetLength()) {
		endX = aggregation->GetAt(i).x;
		endY = aggregation->GetAt(i).y;
		cPaintDc->MoveTo(startX, startY);
		cPaintDc->LineTo(endX, endY);
		startX = endX;
		startY = endY;
		i++;
	}

	endX = aggregation->GetWidth() + aggregation->GetX();
	endY = aggregation->GetHeight() + aggregation->GetY();

	cPaintDc->MoveTo(startX, startY);
	cPaintDc->LineTo(endX, endY);
	//시작지점 원위치
	startX = aggregation->GetX(); 
	startY = aggregation->GetY();

	CBrush white(RGB(255, 255, 255));
	CBrush myBrush;
	myBrush.CreateSolidBrush(RGB(255, 255, 255));
	CBrush *oldBrush = cPaintDc->SelectObject(&myBrush);

	double degree = atan2(endX - startX, startY - endY); // 기울기

	double distance = sqrt(pow(endX - startX, 2) + pow(startY - endY, 2));

	double dX = (startX)+(15 * (endX - startX) / distance); //뒤로 온 기준점 x
	double dY = (startY)-(15 * (startY - endY) / distance); //뒤로 온 기준점 y

	double dX2 = (startX)-((endX - startX) / distance);
	double dY2 = (startY)+((startY - endY) / distance);

	CPoint pts2[4];

	pts2[0].x = static_cast<LONG>(dX - 15 * cos(degree)); // 윗점
	pts2[0].y = static_cast<LONG>(dY - 15 * sin(degree));

	pts2[1].x = static_cast<LONG>(dX2); //마우스 처음 점
	pts2[1].y = static_cast<LONG>(dY2);

	pts2[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // 아랫점
	pts2[2].y = static_cast<LONG>(dY + 15 * sin(degree));

	pts2[3].x = static_cast<LONG>(dX) + static_cast<LONG>(15 * (endX - startX) / distance); // 윗점
	pts2[3].y = static_cast<LONG>(dY) - static_cast<LONG>(15 * (startY - endY) / distance);

	cPaintDc->SelectObject(&white);
	cPaintDc->Polygon(pts2, 4);
	cPaintDc->SelectObject(oldBrush);
	myBrush.DeleteObject();
}

void DrawingVisitor::Visit(Aggregations *aggregations, CDC* cPaintDc) {

	Long startX = aggregations->GetX();
	Long startY = aggregations->GetY();
	Long endX;
	Long endY;
	Long i = 0;

	while (i < aggregations->GetLength()) {
		endX = aggregations->GetAt(i).x;
		endY = aggregations->GetAt(i).y;
		cPaintDc->MoveTo(startX, startY);
		cPaintDc->LineTo(endX, endY);
		startX = endX;
		startY = endY;
		i++;
	}

	endX = aggregations->GetWidth() + aggregations->GetX();
	endY = aggregations->GetHeight() + aggregations->GetY();


	cPaintDc->MoveTo(startX, startY);
	cPaintDc->LineTo(endX, endY);

	//시작지점 원위치
	startX = aggregations->GetX();
	startY = aggregations->GetY();

	CBrush white(RGB(255, 255, 255));
	CBrush myBrush;
	myBrush.CreateSolidBrush(RGB(255, 255, 255));
	CBrush *oldBrush = cPaintDc->SelectObject(&myBrush);

	double degree = atan2(endX - startX, startY - endY); // 기울기

	double distance = sqrt(pow(endX - startX, 2) + pow(startY - endY, 2));
	// 루트안에 = 루트(제곱(
	double dX = (endX)-(15 * (endX - startX) / distance); //뒤로 온 기준점 x
	double dY = (endY)+(15 * (startY - endY) / distance); //뒤로 온 기준점 y

														  // 수직 기울기

	CPoint pts[3];

	pts[0].x = endX; //마우스 현재위치 점
	pts[0].y = endY;

	pts[1].x = static_cast<LONG>(dX - 15 * cos(degree)); // 윗점
	pts[1].y = static_cast<LONG>(dY - 15 * sin(degree));

	pts[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // 아랫점
	pts[2].y = static_cast<LONG>(dY + 15 * sin(degree));

	cPaintDc->MoveTo(pts[0].x, pts[0].y);
	cPaintDc->LineTo(pts[1].x, pts[1].y);

	cPaintDc->MoveTo(pts[0].x, pts[0].y);
	cPaintDc->LineTo(pts[2].x, pts[2].y);


	//여기까지 화살표 다음부터 마름모

	dX = (startX)+(15 * (endX - startX) / distance); //뒤로 온 기준점 x
	dY = (startY)-(15 * (startY - endY) / distance); //뒤로 온 기준점 y

	double dX2 = (startX)-((endX - startX) / distance);
	double dY2 = (startY)+((startY - endY) / distance);

	CPoint pts2[4];

	pts2[0].x = static_cast<LONG>(dX - 15 * cos(degree)); // 윗점
	pts2[0].y = static_cast<LONG>(dY - 15 * sin(degree));

	pts2[1].x = static_cast<LONG>(dX2); //마우스 처음 점
	pts2[1].y = static_cast<LONG>(dY2);

	pts2[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // 아랫점
	pts2[2].y = static_cast<LONG>(dY + 15 * sin(degree));

	pts2[3].x = static_cast<LONG>(dX) + static_cast<LONG>(15 * (endX - startX) / distance); // 윗점
	pts2[3].y = static_cast<LONG>(dY) - static_cast<LONG>(15 * (startY - endY) / distance);

	cPaintDc->SelectObject(&white);
	cPaintDc->Polygon(pts2, 4);
	cPaintDc->SelectObject(oldBrush);
	myBrush.DeleteObject();
}

void DrawingVisitor::Visit(Composition *composition, CDC* cPaintDc) {
	Long startX = composition->GetX();
	Long startY = composition->GetY();
	Long endX;
	Long endY;
	Long i = 0;

	while (i < composition->GetLength()) {
		endX = composition->GetAt(i).x;
		endY = composition->GetAt(i).y;
		cPaintDc->MoveTo(startX, startY);
		cPaintDc->LineTo(endX, endY);
		startX = endX;
		startY = endY;
		i++;
	}

	endX = composition->GetWidth() + composition->GetX();
	endY = composition->GetHeight() + composition->GetY();

	cPaintDc->MoveTo(startX, startY);
	cPaintDc->LineTo(endX, endY);

	//시작지점 원위치
	startX = composition->GetX();
	startY = composition->GetY();

	CBrush black(RGB(000, 000, 000));
	CBrush myBrush;
	myBrush.CreateSolidBrush(RGB(255, 255, 255));
	CBrush *oldBrush = cPaintDc->SelectObject(&myBrush);


	double degree = atan2(endX - startX, startY - endY); // 기울기

	double distance = sqrt(pow(endX - startX, 2) + pow(startY - endY, 2));

	double dX = (startX)+(15 * (endX - startX) / distance); //뒤로 온 기준점 x
	double dY = (startY)-(15 * (startY - endY) / distance); //뒤로 온 기준점 y

	double dX2 = (startX)-((endX - startX) / distance);
	double dY2 = (startY)+((startY - endY) / distance);

	CPoint pts2[4];

	pts2[0].x = static_cast<LONG>(dX - 15 * cos(degree)); // 윗점
	pts2[0].y = static_cast<LONG>(dY - 15 * sin(degree));

	pts2[1].x = static_cast<LONG>(dX2); //마우스 처음 점
	pts2[1].y = static_cast<LONG>(dY2);

	pts2[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // 아랫점
	pts2[2].y = static_cast<LONG>(dY + 15 * sin(degree));

	pts2[3].x = static_cast<LONG>(dX) + static_cast<LONG>(15 * (endX - startX) / distance); // 윗점
	pts2[3].y = static_cast<LONG>(dY) - static_cast<LONG>(15 * (startY - endY) / distance);

	cPaintDc->SelectObject(&black);
	cPaintDc->Polygon(pts2, 4);
	cPaintDc->SelectObject(oldBrush);
	myBrush.DeleteObject();
}

void DrawingVisitor::Visit(Compositions *compositions, CDC* cPaintDc) {

	Long startX = compositions->GetX();
	Long startY = compositions->GetY();
	Long endX;
	Long endY;
	Long i = 0;

	while (i < compositions->GetLength()) {
		endX = compositions->GetAt(i).x;
		endY = compositions->GetAt(i).y;
		cPaintDc->MoveTo(startX, startY);
		cPaintDc->LineTo(endX, endY);
		startX = endX;
		startY = endY;
		i++;
	}

	endX = compositions->GetWidth() + compositions->GetX();
	endY = compositions->GetHeight() + compositions->GetY();

	cPaintDc->MoveTo(startX, startY);
	cPaintDc->LineTo(endX, endY);

	//시작지점 원위치
	startX = compositions->GetX();
	startY = compositions->GetY();

	CBrush black(RGB(000, 000, 000));
	CBrush myBrush;
	myBrush.CreateSolidBrush(RGB(255, 255, 255));
	CBrush *oldBrush = cPaintDc->SelectObject(&myBrush);

	double degree = atan2(endX - startX, startY - endY); // 기울기


	double distance = sqrt(pow(endX - startX, 2) + pow(startY - endY, 2));
	// 루트안에 = 루트(제곱(
	double dX = (endX)-(15 * (endX - startX) / distance); //뒤로 온 기준점 x
	double dY = (endY)+(15 * (startY - endY) / distance); //뒤로 온 기준점 y

														  // 수직 기울기
	CPoint pts[3];

	pts[0].x = endX; //마우스 현재위치 점
	pts[0].y = endY;

	pts[1].x = static_cast<LONG>(dX - 15 * cos(degree)); // 윗점
	pts[1].y = static_cast<LONG>(dY - 15 * sin(degree));

	pts[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // 아랫점
	pts[2].y = static_cast<LONG>(dY + 15 * sin(degree));

	cPaintDc->MoveTo(pts[0].x, pts[0].y);
	cPaintDc->LineTo(pts[1].x, pts[1].y);

	cPaintDc->MoveTo(pts[0].x, pts[0].y);
	cPaintDc->LineTo(pts[2].x, pts[2].y);

	//여기까지 화살표 다음부터 마름모
	distance = sqrt(pow(endX - startX, 2) + pow(startY - endY, 2));

	dX = (startX)+(15 * (endX - startX) / distance); //뒤로 온 기준점 x
	dY = (startY)-(15 * (startY - endY) / distance); //뒤로 온 기준점 y

	double dX2 = (startX)-((endX - startX) / distance);
	double dY2 = (startY)+((startY - endY) / distance);

	CPoint pts2[4];

	pts2[0].x = static_cast<LONG>(dX - 15 * cos(degree)); // 윗점
	pts2[0].y = static_cast<LONG>(dY - 15 * sin(degree));

	pts2[1].x = static_cast<LONG>(dX2); //마우스 처음 점
	pts2[1].y = static_cast<LONG>(dY2);

	pts2[2].x = static_cast<LONG>(dX + 15 * cos(degree)); // 아랫점
	pts2[2].y = static_cast<LONG>(dY + 15 * sin(degree));

	pts2[3].x = static_cast<LONG>(dX) + static_cast<LONG>(16 * (endX - startX) / distance); // 윗점
	pts2[3].y = static_cast<LONG>(dY) - static_cast<LONG>(16 * (startY - endY) / distance);

	cPaintDc->SelectObject(&black);
	cPaintDc->Polygon(pts2, 4);
	cPaintDc->SelectObject(oldBrush);
	myBrush.DeleteObject();
}

DrawingVisitor::~DrawingVisitor() {
}

void DrawingVisitor::Visit(Template *object, CDC *cPaintDc) {

	Long x = object->GetX();
	Long  y = object->GetY();;
	Long width = object->GetWidth();
	Long height = object->GetHeight();

	cPaintDc->Rectangle(x, y, x + width, y + height);


}

void DrawingVisitor::Visit(MemoBox *memoBox, CDC *cPaintDc) {
	Long x = memoBox->GetX();
	Long y = memoBox->GetY();;
	Long width = memoBox->GetWidth();
	Long height = memoBox->GetHeight();



	CPoint pts2[5];
	pts2[0].x = static_cast<LONG>(x + 15); // 윗점
	pts2[0].y = static_cast<LONG>(y);

	pts2[1].x = static_cast<LONG>(x); //마우스 처음 점
	pts2[1].y = static_cast<LONG>(y + 15);

	pts2[2].x = static_cast<LONG>(x); // 아랫점
	pts2[2].y = static_cast<LONG>(y + height);

	pts2[3].x = static_cast<LONG>(x + width); // 윗점
	pts2[3].y = static_cast<LONG>(y + height);

	pts2[4].x = static_cast<LONG>(x + width); // 윗점
	pts2[4].y = static_cast<LONG>(y);

	cPaintDc->Polygon(pts2, 5);

	cPaintDc->MoveTo(pts2[0].x, pts2[0].y);
	cPaintDc->LineTo(pts2[0].x, pts2[0].y + 15);

	cPaintDc->MoveTo(pts2[1].x, pts2[1].y);
	cPaintDc->LineTo(pts2[0].x, pts2[0].y + 15);
}

void DrawingVisitor::Visit(MemoLine *memoLine, CDC *cPaintDc) {
	CPen pen;
	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	CPen *oldPen = cPaintDc->SelectObject(&pen);
	cPaintDc->SetBkMode(TRANSPARENT);

	Long startX = memoLine->GetX();
	Long startY = memoLine->GetY();
	Long endX;
	Long endY;
	Long i = 0;

	while (i < memoLine->GetLength()) {
		endX = memoLine->GetAt(i).x;
		endY = memoLine->GetAt(i).y;
		cPaintDc->MoveTo(startX, startY);
		cPaintDc->LineTo(endX, endY);
		startX = endX;
		startY = endY;
		i++;
	}

	endX = memoLine->GetWidth() + memoLine->GetX();
	endY = memoLine->GetHeight() + memoLine->GetY();


	cPaintDc->MoveTo(startX, startY);
	cPaintDc->LineTo(endX, endY);

	cPaintDc->SelectObject(oldPen);
	pen.DeleteObject();
}
void DrawingVisitor::Visit(Selection *selection, CDC *cPaintDc) {
	Long i = 0;
	while (i < selection->GetLength()) {
		if (dynamic_cast<Class*>(selection->GetAt(i))) {
			Class *object = static_cast<Class*>(selection->GetAt(i));
			if (object->GetTempletePosition() == -1) {
				cPaintDc->Rectangle(
					object->GetX() - 5,
					object->GetY() - 5,
					object->GetX() + 5,
					object->GetY() + 5);
				cPaintDc->Rectangle(
					object->GetX() + object->GetWidth() - 5,
					object->GetY() - 5,
					object->GetX() + object->GetWidth() + 5,
					object->GetY() + 5);
				cPaintDc->Rectangle(
				 object->GetX() - 5,
				object->GetY() + object->GetHeight() - 5,
					object->GetX() + 5,
					object->GetY() + object->GetHeight() + 5);
				cPaintDc->Rectangle(
					object->GetX() + object->GetWidth() - 5,
					object->GetY() + object->GetHeight() - 5,
					object->GetX() + object->GetWidth() + 5,
					object->GetY() + object->GetHeight() + 5);
				
			}
			else {
				Long j = 0;
				while (j < object->GetLength()) {
					if (dynamic_cast<Template*>(object->GetAt(j))) {
						Template *templete = static_cast<Template*>(object->GetAt(j));
						cPaintDc->Rectangle(
							object->GetX() - 5,
							templete->GetY() - 5,
							object->GetX() + 5,
							templete->GetY() + 5);
						cPaintDc->Rectangle(
							templete->GetX() + templete->GetWidth() - 5,
							templete->GetY() - 5,
							templete->GetX() + templete->GetWidth() + 5,
							templete->GetY() + 5);
						cPaintDc->Rectangle(
							object->GetX() - 5,
							object->GetY() + object->GetHeight() - 5,
							object->GetX() + 5,
							object->GetY() + object->GetHeight() + 5);
						cPaintDc->Rectangle(
							templete->GetX() + templete->GetWidth() - 5,
							object->GetY() + object->GetHeight() - 5,
							templete->GetX() + templete->GetWidth() + 5,
							object->GetY() + object->GetHeight() + 5);
						
					}
					j++;
					
				}
				
			}			
		}
		
			if (dynamic_cast<MemoBox*>(selection->GetAt(i))) {
			MemoBox *memoBox = static_cast<MemoBox*>(selection->GetAt(i));
			cPaintDc->Rectangle(
				memoBox->GetX() - 5,
				memoBox->GetY() - 5,
				memoBox->GetX() + 5,
				memoBox->GetY() + 5);
			cPaintDc->Rectangle(
				memoBox->GetX() + memoBox->GetWidth() - 5,
				memoBox->GetY() - 5,
				memoBox->GetX() + memoBox->GetWidth() + 5,
				memoBox->GetY() + 5);
			cPaintDc->Rectangle(
				memoBox->GetX() - 5,
				memoBox->GetY() + memoBox->GetHeight() - 5,
				memoBox->GetX() + 5,
				memoBox->GetY() + memoBox->GetHeight() + 5);
			cPaintDc->Rectangle(
				memoBox->GetX() + memoBox->GetWidth() - 5,
				memoBox->GetY() + memoBox->GetHeight() - 5,
				memoBox->GetX() + memoBox->GetWidth() + 5,
				memoBox->GetY() + memoBox->GetHeight() + 5);
			
				
		}
			Long j = 0;
				//상태패턴이던 뭐든 적용해야함
			if (dynamic_cast<Relation*>(selection->GetAt(i))) {
				if (static_cast<Relation*>(selection->GetAt(i))->GetLength() == 0) {
					cPaintDc->Rectangle(selection->GetAt(i)->GetX() - 5,
						selection->GetAt(i)->GetY() - 5,
						selection->GetAt(i)->GetX() + 5,
						selection->GetAt(i)->GetY() + 5);
					cPaintDc->Rectangle(selection->GetAt(i)->GetX() + (selection->GetAt(i)->GetWidth() / 2) - 5,
						selection->GetAt(i)->GetY() + (selection->GetAt(i)->GetHeight() / 2) - 5,
						selection->GetAt(i)->GetX() + (selection->GetAt(i)->GetWidth() / 2) + 5,
						selection->GetAt(i)->GetY() + (selection->GetAt(i)->GetHeight() / 2) + 5);
					cPaintDc->Rectangle(selection->GetAt(i)->GetX() + selection->GetAt(i)->GetWidth() - 5,
						selection->GetAt(i)->GetY() + selection->GetAt(i)->GetHeight() - 5,
						selection->GetAt(i)->GetX() + selection->GetAt(i)->GetWidth() + 5,
						selection->GetAt(i)->GetY() + selection->GetAt(i)->GetHeight() + 5);
				}
				else {
					cPaintDc->Rectangle(selection->GetAt(i)->GetX() - 5,
						selection->GetAt(i)->GetY() - 5,
						selection->GetAt(i)->GetX() + 5,
						selection->GetAt(i)->GetY() + 5);
					cPaintDc->Rectangle(selection->GetAt(i)->GetX() + selection->GetAt(i)->GetWidth() - 5,
						selection->GetAt(i)->GetY() + selection->GetAt(i)->GetHeight() - 5,
						selection->GetAt(i)->GetX() + selection->GetAt(i)->GetWidth() + 5,
						selection->GetAt(i)->GetY() + selection->GetAt(i)->GetHeight() + 5);
					while (j < dynamic_cast<Relation*>(selection->GetAt(i))->GetLength()) {
						CPoint cPoint = dynamic_cast<Relation*>(selection->GetAt(i))->GetAt(j);
						cPaintDc->Rectangle(cPoint.x - 5,
							cPoint.y - 5,
							cPoint.x + 5,
							cPoint.y + 5);
						j++;
					}
				}
		}
		i++;
	}	
	
}
void DrawingVisitor::Visit(ClassName *className, CDC *cPaintDc) {

}

void DrawingVisitor::Visit(Method *method, CDC *cPatinDc) {

}

void DrawingVisitor::Visit(Attribute *attribute, CDC *cPaintDc) {

}

void DrawingVisitor::Visit(Selection *selection, Long distanceX, Long distanceY) {

}