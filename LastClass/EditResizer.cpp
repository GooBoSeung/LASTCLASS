//EditResizer.cpp

#include "EditResizer.h"
#include "EditResizerProcess.h"
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
	EditResizerProcess resizer;
	RECT rt;
	textEdit->GetClientRect(&rt);

	if (textEdit->text->MaxWidth(cdc) + 9 > textEdit->figure->GetWidth()) {				//�۳ʺ� Ŭ������ �Ѿ�µ�
		if (textEdit->GetRowHeight()*textEdit->text->GetLength() > textEdit->figure->GetHeight()) {
			resizer.ResizeEditAll(textEdit, cdc);										//�۳��̰� Ŭ������ �Ѿ�� �Ѵ�O
		}
		else {																			//�۳��̰� Ŭ������ �ȳѾ�� �ʺ�
			resizer.ResizeEditWidth(textEdit, cdc);
		}
	}
	else if (textEdit->text->MaxWidth(cdc) + 9 <= textEdit->figure->GetWidth()) {		//�۳ʺ� Ŭ������ �ȳѾ�µ�

		if (textEdit->GetRowHeight()*textEdit->text->GetLength() > textEdit->figure->GetHeight()) {
			resizer.ResizeEditHeight(textEdit, cdc);									//�۳��̰� Ŭ������ �Ѿ�� ���̸�
		}
		else {																			//�۳��̰� Ŭ������ �Ѿ�� �Ѵ�X
			resizer.RewindEdit(textEdit, cdc);
		}
	}
}

void EditResizer::ResizeClass(TextEdit *textEdit, CDC *cdc) {
	EditResizerProcess resizer;
	if (textEdit->text->MaxWidth(cdc) + 9 > textEdit->figure->GetWidth()) {
		resizer.ResizeClassWidth(textEdit,cdc);
	}
	if (textEdit->GetRowHeight()*textEdit->text->GetLength() > textEdit->figure->GetHeight()) {
		resizer.ResizeClassHeight(textEdit);
	}
}
