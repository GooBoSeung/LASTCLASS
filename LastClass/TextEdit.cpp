//TextEdit.cpp

#pragma comment(lib,"imm32")

#include "TextEdit.h"
#include "ClassDiagramForm.h"
#include "Text.h"
#include "Row.h"
#include "Character.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"
#include "Figure.h"
#include "Caret.h"
#include "KeyBoard.h"
#include "KeyAction.h"
#include "TextAreaSelected.h"
#include "WritingVisitor.h"   
#include <iostream>

BEGIN_MESSAGE_MAP(TextEdit, CWnd)
	ON_WM_CREATE()
	ON_WM_PAINT()
	ON_WM_CHAR()
	ON_MESSAGE(WM_IME_COMPOSITION, OnComposition)
	ON_WM_KILLFOCUS()

	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDBLCLK()

	ON_WM_KEYDOWN()
	ON_MESSAGE(WM_IME_NOTIFY, OnIMENotify)
	//ON_WM_CLOSE()
END_MESSAGE_MAP()

TextEdit::TextEdit(Figure *figure) {
	this->text = NULL;
	this->caret = NULL;
	this->keyBoard = NULL;
	this->figure = figure;
	this->rowHeight = 18; // ��Ʈ ������
	this->koreanEnglish = 0;
	this->flagBuffer = 0;
	this->flagInsert = 0;
	this->flagSelection = 0;
	this->currentX = 0;
	this->copyBuffer = "";
}

int TextEdit::OnCreate(LPCREATESTRUCT lpCreateStruct) {
	CWnd::OnCreate(lpCreateStruct); //override
	CWnd::SetFocus();

	this->text = new Text;
	this->caret = new Caret;
	this->keyBoard = new KeyBoard;

	ModifyStyle(WS_CAPTION, 0);
	//ModifyStyle(0, 0, SetWindowPos(&CWnd::wndTop, this->selectedY + 5, this->selectedY + 33, this->width - 5, this->height * 33, 0));

	this->text->SprayString(this->figure->GetContent()); // �Ѱܹ޾ƿ°� �ڷᱸ���� �ѷ��� ����������

	CWnd::HideCaret();
	::DestroyCaret();
	Invalidate();
	return 0;
}

void TextEdit::OnPaint() {
	CPaintDC dc(this);
	
	WritingVisitor writingVisitor;

	CFont cFont;
	cFont.CreateFont(this->rowHeight, 0, 0, 0, FW_LIGHT, FALSE, FALSE, 0, DEFAULT_CHARSET,// �۲� ����
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,"����ü");
	SetFont(&cFont, TRUE);
	CFont *oldFont = dc.SelectObject(&cFont); // ��Ʈ ����
	
	this->text->Accept(writingVisitor, &dc);//�޾Ҵ��� ���
	this->caret->MoveToIndex(this, &dc);

	dc.SetTextColor(RGB(255, 255, 255));
	dc.SetBkColor(RGB(0, 100, 255));
	dc.SetBkMode(OPAQUE);//�ؽ�Ʈ ����� SetBkColor ���

	if (this->flagSelection == 1) { // flagSelection�� ����������
		TextAreaSelected *selectArea = new TextAreaSelected();
		selectArea->SelectTextArea(this, &dc);
		if (selectArea != 0) {
			delete selectArea;
		}
	}
	dc.SelectObject(oldFont);
	cFont.DeleteObject(); // ��Ʈ
}

void TextEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) {
	if (this->koreanEnglish == 0 && nChar != VK_BACK && nChar != VK_ESCAPE && nChar != VK_RETURN &&
		nChar != VK_SPACE && nChar != VK_TAB && nChar != 10 &&  GetKeyState(VK_CONTROL) >= 0) {//GetKeyState(VK_RSHIFT) >= 0 &&
		char nCharacter = nChar;

		SingleByteCharacter singleByteCharacter(nCharacter);

		if (this->caret->GetCharacterIndex() == this->text->GetAt(this->caret->GetRowIndex())->GetLength()) {
			this->text->GetAt(this->caret->GetRowIndex())->Add(singleByteCharacter.Clone());
		}
		else if (this->caret->GetCharacterIndex() < this->text->GetAt(this->caret->GetRowIndex())->GetLength() && this->flagInsert == 0) {
			this->text->GetAt(this->caret->GetRowIndex())->Insert(this->caret->GetCharacterIndex(), singleByteCharacter.Clone());
		}
		else if (this->caret->GetCharacterIndex() < this->text->GetAt(this->caret->GetRowIndex())->GetLength() && this->flagInsert == 1) {
			this->text->GetAt(this->caret->GetRowIndex())->Modify(this->caret->GetCharacterIndex(), singleByteCharacter.Clone());
		}
		this->caret->MoveForwardCharacterIndex();
	}

	CWnd::HideCaret();
	::DestroyCaret();
	Invalidate();
}

Long TextEdit::OnComposition(WPARAM wParam, LPARAM lParam) {
	HIMC hIMC = ImmGetContext(GetSafeHwnd());
	Long bufferLength;
	char buffer[8];
	Long i = 0;

	if (lParam & GCS_RESULTSTR) {
		bufferLength = ImmGetCompositionString(hIMC, GCS_RESULTSTR, NULL, 0);
		ImmGetCompositionString(hIMC, GCS_RESULTSTR, buffer, bufferLength);
		char(*tempChar) = new char[bufferLength];
		while (i < bufferLength) {
			tempChar[i] = buffer[i];
			i++;
		}
		DoubleByteCharacter doubleByteCharacter(tempChar);
		delete[] tempChar;

		this->text->GetAt(this->caret->GetRowIndex())->Modify(this->caret->GetCharacterIndex() - 1, doubleByteCharacter.Clone());
		this->flagBuffer = 0;
	}
	else if (lParam & GCS_COMPSTR) {
		bufferLength = ImmGetCompositionString(hIMC, GCS_COMPSTR, NULL, 0);
		ImmGetCompositionString(hIMC, GCS_COMPSTR, buffer, bufferLength);
		if (this->flagBuffer == 0) { // �����߿��� �����ϋ�
			char(*tempChar) = new char[bufferLength];
			while (i < bufferLength) {
				tempChar[i] = buffer[i];
				i++;
			}
			DoubleByteCharacter doubleByteCharacter(tempChar);
			delete[] tempChar;

			if (this->caret->GetCharacterIndex() == this->text->GetAt(this->caret->GetRowIndex())->GetLength()) {
				this->text->GetAt(this->caret->GetRowIndex())->Add(doubleByteCharacter.Clone());
			}
			else if (this->caret->GetCharacterIndex() < this->text->GetAt(this->caret->GetRowIndex())->GetLength() && this->flagInsert == 0) {
				this->text->GetAt(this->caret->GetRowIndex())->Insert(this->caret->GetCharacterIndex(), doubleByteCharacter.Clone());
			}
			else if (this->caret->GetCharacterIndex() < this->text->GetAt(this->caret->GetRowIndex())->GetLength() && this->flagInsert == 1) {
				this->text->GetAt(this->caret->GetRowIndex())->Modify(this->caret->GetCharacterIndex(), doubleByteCharacter.Clone());
			}	
			this->caret->MoveForwardCharacterIndex();
			this->flagBuffer = 1;
		}
		else { // �����߿��� �������϶�
			if (bufferLength > 0) {
				char(*tempChar) = new char[bufferLength];
				while (i < bufferLength) {
					tempChar[i] = buffer[i];
					i++;
				}
				DoubleByteCharacter doubleByteCharacter(tempChar);
				this->text->GetAt(this->caret->GetRowIndex())->Modify(this->caret->GetCharacterIndex() - 1, doubleByteCharacter.Clone());
				delete[] tempChar;
			}
			else if (bufferLength == 0) {
				this->text->GetAt(this->caret->GetRowIndex())->Remove(this->caret->GetCharacterIndex() - 1);
				this->caret->MoveBackwardCharacterIndex();
				this->flagBuffer = 0;
			}
		}
	}
	ImmReleaseContext(GetSafeHwnd(), hIMC);

	CWnd::HideCaret();
	::DestroyCaret();
	Invalidate();

	return 0;
}

void TextEdit::OnKillFocus(CWnd *pNewWnd) {
	CWnd::OnKillFocus(pNewWnd);

	CWnd::HideCaret();
	::DestroyCaret();

	string content(this->text->MakeText());
	this->figure->ReplaceString(content);

	if (this->caret != NULL) {
		delete this->caret;
	}
	if (this->keyBoard != NULL) {
		delete this->keyBoard;
	}
	if (this->text != NULL) {
		delete this->text;
	}
	CWnd::DestroyWindow();
}

void TextEdit::OnLButtonDown(UINT nFlags, CPoint point) {
		CPaintDC dc(this);

		CFont cFont;
		cFont.CreateFont(this->rowHeight, 0, 0, 0, FW_LIGHT, FALSE, FALSE, 0, DEFAULT_CHARSET,      // �۲� ����
			OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "����ü");
		SetFont(&cFont, TRUE);
		CFont *oldFont = dc.SelectObject(&cFont); // ��Ʈ ����

		if (GetKeyState(VK_SHIFT) < 0) { // Ŭ���ߴµ� ����Ʈ�� �������� ��
			if (this->flagSelection == 0) { // flag �� �ȴ���������
				this->flagSelection = 1; // flag �� �����ش�
				this->selectedX = this->caret->GetCharacterIndex(); // selectedX, Y �� ���� ��ġ ĳ�� ��� ��ǥ�� �����Ѵ�
				this->selectedY = this->caret->GetRowIndex();
			}
		}
		else {
			if (this->flagSelection == 1) { // ����Ʈ �ȴ����ִµ� flag �� ���������� flag ������ش�
				this->flagSelection = 0;
			}
		}
		this->caret->MoveToPoint(this, &dc, point); // �ű� ��ġ�� ĳ���� �̵������ش�

		dc.SelectObject(oldFont);
		cFont.DeleteObject(); // ��Ʈ ��

		CWnd::HideCaret();
		::DestroyCaret();
		Invalidate();
	
}

void TextEdit::OnLButtonUp(UINT nFlags, CPoint point) {

	CWnd::HideCaret();
	::DestroyCaret();
	Invalidate();
}

void TextEdit::OnMouseMove(UINT nFlags, CPoint point) {
	if (nFlags == MK_LBUTTON) {

		CFont cFont;
		CPaintDC dc(this);
		cFont.CreateFont(this->GetRowHeight(), 0, 0, 0, FW_LIGHT, FALSE, FALSE, 0, DEFAULT_CHARSET,      // �۲� ����
			OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, "����ü");
		this->SetFont(&cFont, TRUE);
		CFont *oldFont = dc.SelectObject(&cFont);// ��Ʈ ����

		if (this->flagSelection == 0 && this->currentX != 0) {// && this->) { // �޸��콺 �����ִµ� �̵��ÿ� flag ���������� Ȯ���ؼ�
			this->flagSelection = 1; // flag ������ �ƴϸ� ���������� �ٲٰ�
			this->selectedX = this->caret->GetCharacterIndex(); // ���� �ѹ� selectedX, Y ��
			this->selectedY = this->caret->GetRowIndex();
		}
		this->caret->MoveToPoint(this, &dc, point); // ���ο� ��ġ�� ĳ�� �̵��Ѵ�

		dc.SelectObject(oldFont);
		cFont.DeleteObject(); // ��Ʈ ��

		::DestroyCaret();
		Invalidate();
	}
	this->currentX = point.x;
}

void TextEdit::OnLButtonDoubleClicked(UINT nFlags, CPoint point) {
	
}

void TextEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) {
	/*if (textEdit->flagSelection == 1) {
	textEdit->flagSelection = 0;
	}*/
	this->koreanEnglish = 1;

	KeyAction *keyAction = this->keyBoard->KeyDown(this, nChar, nRepCnt, nFlags);
	if (keyAction != 0) {
		keyAction->KeyPress(this);
	}
	this->koreanEnglish = 0;

	CWnd::HideCaret();
	::DestroyCaret();
	CWnd::Invalidate();
}

LRESULT TextEdit::OnIMENotify(WPARAM wParam, LPARAM lParam) {
	if (wParam == IMN_SETCONVERSIONMODE) {
		if (this->koreanEnglish == 0) {
			this->koreanEnglish = 1;
		}
		else {
			this->koreanEnglish = 0;
		}
	}
	return 0;
}

//void TextEdit::OnClose() {
//	string content(this->text->MakeText());
//	this->figure->ReplaceString(content);
//
//	if (this->caret != NULL) {
//		delete this->caret;
//	}
//	if (this->keyBoard != NULL) {
//		delete this->keyBoard;
//	}
//	if (this->text != NULL) {
//		delete this->text;
//	}
//	DestroyCaret();
//	CWnd::OnClose();
//}