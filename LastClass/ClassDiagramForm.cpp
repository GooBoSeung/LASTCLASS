//ClassDiagramForm.cpp

#include "ClassDiagramForm.h"
#include "Diagram.h"
#include "DrawingVisitor.h"
#include "FigureFactory.h"

#include "Text.h"
#include "SingleByteCharacter.h"
#include "WritingVisitor.h"
#include "TextEdit.h"

#include <iostream>
#include <fstream> //�ε弼�̺�

using namespace std;

BEGIN_MESSAGE_MAP(ClassDiagramForm, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_CHAR()
	ON_WM_SETFOCUS()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

ClassDiagramForm::ClassDiagramForm() { // ������ �´µ�
	this->diagram = NULL;
	this->text = NULL;
	this->textEdit = NULL;
	this->startX = 0;
	this->startY = 0;
	this->currentX = 0;
	this->currentY = 0;
	this->currentClassIndex = -1;
	this->rowIndex = 0;
	this->characterIndex = 0;
}

Long ClassDiagramForm::Save() {
   Long i = 0;
   Long j;
   ofstream fClass;
   ofstream fLine; // �������� ofstream

   fClass.open("ClassSave.txt");
   fLine.open("LineSave.txt");
   if (fClass.is_open() && fLine.is_open()) {
      while (i < this->diagram->GetLength()) {
         Class object;
         object = *(this->diagram->GetAt(i));
         fClass << object.GetLength() << " " << object.GetX() << " " << object.GetY()
            << " " << object.GetWidth() << " " << object.GetHeight() << endl;
         j = 0;
         while (j < object.GetLength()) {
            Line lineObject;
			lineObject = *(object.GetAt(j));
            fLine << lineObject.GetX() << " " << lineObject.GetY() << " " <<
               lineObject.GetWidth() << " " << lineObject.GetHeight() << endl;
            j++;
         }
         i++;
      }
      fClass.close();
      fLine.close();
   }
   return this->diagram->GetLength();
}

Long ClassDiagramForm::Load() {
	Long position;
	Long i;
	Long x;
	Long y;
	Long width;
	Long height;
	Long length;
	Long lineX;
	Long lineY;
	Long lineWidth;
	Long lineHeigth;
	ifstream fClass;
	ifstream fLine;

	fClass.open("ClassSave.txt");
	fLine.open("LineSave.txt");

	if (fClass.is_open() && fLine.is_open()) {
		fClass >> length >> x >> y >> width >> height;
		while (!fClass.eof()) {
			position = this->diagram->Add(x, y, width, height);
			i = 0;
			while (i < length) {
				fLine >> lineX >> lineY >> lineWidth >> lineHeigth;
				static_cast<Class*>(this->diagram->GetAt(position))->Add(lineX, lineY, lineWidth, lineHeigth);
				i++;
			}
			fClass >> length >> x >> y >> width >> height;
		}
		fClass.close();
		fLine.close();
	}
	return this->diagram->GetLength();
}

Long ClassDiagramForm::TextSave() {
	Long i = 0;
	string s;
	ofstream fText;
	fText.open("Text.txt");
	if (fText.is_open()) {
		while (i < this->text->GetLength()) {
			s = this->text->GetAt(i)->PrintRowString();
			fText << this->text->GetAt(i)->GetX() << ' ' << this->text->GetAt(i)->GetY() << ' ' << this->text->GetAt(i)->GetRowHeight() << ' ' << s << endl;
			i++;
		}
		fText.close();
	}
	return i;
}

Long ClassDiagramForm::TextLoad() {
	FigureFactory textCreator;
	string str;
	Long i = 0;
	Long x = 0;
	Long y = 0;
	Long rowHeight = 0;
	TextComponent* Component = NULL;
	ifstream fText;

	fText.open("Text.txt");
	if (fText.is_open()) {
		while (!fText.eof()) {
			fText >> x >> y >> rowHeight >> str;
			Component = textCreator.CreateRow(x, y, rowHeight, str);
			this->text->Add(Component);
			i++;
		}
	}
	return i;
}

int ClassDiagramForm::OnCreate(LPCREATESTRUCT lpCreateStruct) {

	CFrameWnd::OnCreate(lpCreateStruct); //�ڵ����� �������̵� //��ӿ���
										 //1.1. ���̾�׷��� �غ��Ѵ�
	this->diagram = new Diagram();
	this->text = new Text;

	//1.2. �����Ѵ�
	//this->Load();
	this->TextLoad();
	//1.3. �����츦 �����Ѵ�
	Invalidate();

	return 0;
}

void ClassDiagramForm::OnPaint() {
	CPaintDC dc(this);

	DrawingVisitor drawingVisitor;
	WritingVisitor writingVisitor;
	
	CPen pen;
	pen.CreatePen(PS_DOT, 1, RGB(0, 0, 0));
	CPen *oldPen = dc.SelectObject(&pen);
	dc.SetBkMode(TRANSPARENT);
	dc.Rectangle(startX, startY, this->currentX, this->currentY);
	dc.SelectObject(oldPen);
	pen.DeleteObject();

	this->diagram->Accept(drawingVisitor,&dc);

	this->text->Accept(writingVisitor, &dc);
}

void ClassDiagramForm::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) {
	char nCharacter = nChar;

	if (this->text->GetLength() == 0) {
		Row newRow;
		this->text->Add(newRow.Clone());
	}
	SingleByteCharacter singleByteCharacter(nCharacter);
	this->startX += 10;
	this->text->GetAt(this->rowIndex)->Add(singleByteCharacter.Clone());

	//Invalidate();
}

void ClassDiagramForm::OnSetFocus(CWnd* pOldWnd) {
	
	this->Invalidate();
}

void ClassDiagramForm::OnLButtonDown(UINT nFlags, CPoint point) {
	this->startX = point.x;
	this->startY = point.y;
	this->currentX = point.x;
	this->currentY = point.y;

	this->currentClassIndex = -1;
	this->currentClassIndex = this->diagram->Find(this->startX, this->startY);
	if (this->currentClassIndex >= 0) { //Ŭ���� ��ġ�� Ŭ������ �־��ٸ�
		this->textEdit = new TextEdit(this, // �ؽ�Ʈ���� ũ��� Ŭ���� ũ��, �ϴ���
			this->diagram->GetAt(currentClassIndex)->GetX() + 5,
			this->diagram->GetAt(currentClassIndex)->GetY() + 33,
			this->diagram->GetAt(currentClassIndex)->GetWidth() - 5,
			this->diagram->GetAt(currentClassIndex)->GetHeight() - 5);

		this->textEdit->Create(NULL, "textEdit", WS_DLGFRAME, CRect(
			this->textEdit->GetFormX(),
			this->textEdit->GetFormY(),
			this->textEdit->GetFormX() + this->textEdit->GetWidth(),
			this->textEdit->GetFormY() + this->textEdit->GetHeight()), NULL, NULL, WS_EX_TOPMOST);
		this->textEdit->ShowWindow(SW_SHOW);
	}
}

void ClassDiagramForm::OnLButtonUp(UINT nFlags, CPoint point) {
	this->currentX = point.x;
	this->currentY = point.y;

	if (this->currentClassIndex >= 0) { //start ��ġ���� Ŭ������ ã�Ҿ��ٸ�
										// ���콺 �������� �� ��ġ��ŭ ���õǾ��ִ� Ŭ������ �̵��Ѵ�
	}
	else { // Ŭ�� ��ġ�� Ŭ���� �������� ������� Ŭ���� ��ȣ�� �����
		if (this->currentX != this->startX && this->currentY != this->startY) {
			if (this->currentX - this->startX < 150) {
				this->currentX = this->startX + 150;
			}
			if (this->currentY - this->startY < 200) {
				this->currentY = this->startY + 200;
			}
			Long index = this->diagram->Add(this->startX, this->startY, this->currentX - this->startX, this->currentY - this->startY);

			//÷�ڿ����� �� �ȵŴ��� Ȯ���ؾ���
			this->diagram->GetAt(index)->Add(this->startX, this->startY + 50,
				this->currentX - this->startX, this->startY + 50);
			static_cast<Class*>(this->diagram->GetAt(index))->Add(this->startX, (this->startY + 50 + this->currentY) / 2,
				this->currentX - this->startX, (this->startY + 50 + this->currentY) / 2);

			this->textEdit = new TextEdit(this, // �ؽ�Ʈ���� ũ��� Ŭ���� ũ��, �ϴ���
				this->diagram->GetAt(index)->GetX() + 5,
				this->diagram->GetAt(index)->GetY() + 33,
				this->diagram->GetAt(index)->GetWidth() - 5,
				this->diagram->GetAt(index)->GetHeight() - 5);

			this->textEdit->Create(NULL, "textEdit", WS_DLGFRAME, CRect(
				this->textEdit->GetFormX(),
				this->textEdit->GetFormY(),
				this->textEdit->GetFormX() + this->textEdit->GetWidth(),
				this->textEdit->GetFormY() + this->textEdit->GetHeight()), NULL, NULL, WS_EX_TOPMOST);
			this->textEdit->ShowWindow(SW_SHOW);

			Invalidate();
		}
	}
}	

void ClassDiagramForm::OnLButtonDoubleClicked(UINT nFlags, CPoint point) {
	//Long index = this->diagram->Find(point.x, point.y);
	//Long classWidth = this->diagram->GetAt(index)->GetWidth();
	//Long classHeight = this->diagram->GetAt(index)->GetHeight();

	//this->textEdit = new TextEdit(this, point.x, point.y, classWidth, classHeight); ///////////////////////

	//this->textEdit->Create(NULL, "TextEdit", WS_DLGFRAME, CRect(textEdit->GetStartX() + 5, textEdit->GetStartY() + 35, this->currentX, 15), NULL, NULL, WS_EX_TOPMOST);
	//this->textEdit->ShowWindow(SW_SHOW);
	//this->textEdit->UpdateWindow();
}

void ClassDiagramForm::OnMouseMove(UINT nFlags, CPoint point) {
	if (nFlags == MK_LBUTTON) {
		this->currentX = point.x;
		this->currentY = point.y;

		Invalidate();
	}
}

void ClassDiagramForm::OnClose() {
	//6.1. �����Ѵ�.
	//this->Save();
	this->TextSave();
	//6.2. ���̾�׷��� �����.
	if (this->diagram != NULL) {
		delete this->diagram;
	}
	if (this->text != NULL) {
		delete this->text;
	}
	CFrameWnd::OnClose();
}



//int main(int argc, char* argv[]) {
//
//	ClassDiagramForm classDiagramForm;
//
//	cout << " dd " << endl;
//
//	classDiagramForm.diagram = new Diagram;
//
//	classDiagramForm.Load(); //�ε�
//
//	cout << " dd " << endl;
//	//Ŭ���� ���̺�ε� Ȯ��
//	cout << classDiagramForm.diagram->GetAt(0)->GetX() << " " << classDiagramForm.diagram->GetAt(0)->GetY() << " " <<
//		classDiagramForm.diagram->GetAt(0)->GetWidth() << " " << classDiagramForm.diagram->GetAt(0)->GetHeight()
//		<< " " << classDiagramForm.diagram->GetAt(0)->GetLength() << " " << classDiagramForm.diagram->GetAt(0)->GetCapacity()
//		<< endl;
//	cout << " dd " << endl;
//	//���� ���̺�ε� Ȯ��
//	cout << classDiagramForm.diagram->GetAt(0)->GetAt(0)->GetX() << " " <<
//		classDiagramForm.diagram->GetAt(0)->GetAt(0)->GetY() << " " <<
//		classDiagramForm.diagram->GetAt(0)->GetAt(0)->GetWidth() << " " <<
//		classDiagramForm.diagram->GetAt(0)->GetAt(0)->GetHeight() << " " << endl;
//	cout << " dd " << endl;
//
//	classDiagramForm.Save(); //���̺�
//
//	return 0;
//}
// 