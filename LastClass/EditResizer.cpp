//EditResizer.cpp

#include "EditResizer.h"
#include "ClassDiagramForm.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "Figure.h"
#include "FigureComposite.h"
#include "Diagram.h"
#include "Class.h"
#include "Finder.h"
#include "Selection.h"

EditResizer::EditResizer() {

}
EditResizer::EditResizer(const EditResizer& source) {

}
EditResizer::~EditResizer() {

}
void EditResizer::ResizeEdit(TextEdit *textEdit, CDC *cdc) {

	if (textEdit->text->MaxWidth(cdc) + 9 > textEdit->figure->GetWidth()) {								//�۳ʺ� Ŭ������ �Ѿ�µ�

		if (textEdit->GetRowHeight()*textEdit->text->GetLength() > textEdit->figure->GetHeight()) {		//�۳��̰� Ŭ������ �Ѿ�� �Ѵ�O

			cdc->FillSolidRect(CRect(0, 0, textEdit->text->MaxWidth(cdc) + textEdit->rowHeight,
											textEdit->GetRowHeight()*textEdit->text->GetLength()), RGB(255, 255, 255));

			textEdit->MoveWindow(textEdit->figure->GetX(), textEdit->figure->GetY(),
									textEdit->text->MaxWidth(cdc) + 9, textEdit->GetRowHeight()*textEdit->text->GetLength() + 5);
		}
		else {																							//�۳��̰� Ŭ������ �ȳѾ�� �ʺ�
			cdc->FillSolidRect(CRect(0, 0, textEdit->text->MaxWidth(cdc) + textEdit->rowHeight,
											textEdit->figure->GetHeight()), RGB(255, 255, 255));

			textEdit->MoveWindow(textEdit->figure->GetX(), textEdit->figure->GetY(),
									textEdit->text->MaxWidth(cdc) + 9, textEdit->figure->GetHeight());
		}
	}
	else if (textEdit->text->MaxWidth(cdc) + 9 <= textEdit->figure->GetWidth())	{						//�۳ʺ� Ŭ������ �ȳѾ�µ�

		if (textEdit->GetRowHeight()*textEdit->text->GetLength() > textEdit->figure->GetHeight()) {		//�۳��̰� Ŭ������ �Ѿ�� ���̸�

			cdc->FillSolidRect(CRect(0, 0, textEdit->figure->GetWidth() + 5,
											textEdit->GetRowHeight()*textEdit->text->GetLength()), RGB(255, 255, 255));

			textEdit->MoveWindow(textEdit->figure->GetX(), textEdit->figure->GetY(),
									textEdit->figure->GetWidth(), textEdit->GetRowHeight()*textEdit->text->GetLength() + 5);
		}
		else {																							//�۳��̰� Ŭ������ �Ѿ�� �Ѵ�X
			cdc->FillSolidRect(CRect(0, 0, textEdit->figure->GetWidth() + 5,
											textEdit->figure->GetHeight()), RGB(255, 255, 255));

			textEdit->MoveWindow(textEdit->figure->GetX(), textEdit->figure->GetY(),
									textEdit->figure->GetWidth(), textEdit->figure->GetHeight());
		}
	}
}

void EditResizer::ResizeClass(TextEdit *textEdit) {
	CDC * cdc = textEdit->GetDC();
	RECT rt;
	textEdit->GetClientRect(&rt);

	textEdit->figure->SetMinimumWidth(rt.right);
	ClassDiagramForm *classDiagramForm = (ClassDiagramForm*)textEdit->GetParentFrame();
	Long width = classDiagramForm->selection->GetAt(0)->GetWidth();
	if (textEdit->figure->GetMinimumWidth() > width) {
		static_cast<FigureComposite*>(classDiagramForm->selection->GetAt(0))->
			ModifyComponetsToRightDirection(classDiagramForm->diagram, textEdit->figure->GetMinimumWidth() - width + 9);
		static_cast<Class*>(classDiagramForm->selection->GetAt(0))->SetMinimumWidth();
	}
	textEdit->ReleaseDC(cdc);
}