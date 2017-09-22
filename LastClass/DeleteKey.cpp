//DeleteKey.cpp

#include "DeleteKey.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "Caret.h"
#include "HistoryText.h"
#include "TextAreaSelected.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"

DeleteKey::DeleteKey() {
}

DeleteKey::DeleteKey(const DeleteKey& source) {
}

DeleteKey::~DeleteKey() {
}

void DeleteKey::KeyPress(TextEdit *textEdit) {
	if (textEdit->flagSelection == 1) {
		Long i = 0;
		if (textEdit->textAreaSelected->GetStartRowIndex() == textEdit->textAreaSelected->GetEndRowIndex()) {
			textEdit->historyText->PushUndo(textEdit->text, textEdit->caret);
			while (i < textEdit->textAreaSelected->GetEndCharacterIndex() - textEdit->textAreaSelected->GetStartCharacterIndex()) {
				textEdit->text->GetAt(textEdit->textAreaSelected->GetStartRowIndex())->Remove(textEdit->textAreaSelected->GetStartCharacterIndex());
				i++;
			}
		}
		else if (textEdit->textAreaSelected->GetStartRowIndex() < textEdit->textAreaSelected->GetEndRowIndex()) { // �������̸�
			textEdit->historyText->PushUndo(textEdit->text, textEdit->caret);
			while (textEdit->textAreaSelected->GetStartCharacterIndex() < textEdit->text->GetAt(textEdit->textAreaSelected->GetStartRowIndex())->GetLength()) {//ù��
				textEdit->text->GetAt(textEdit->textAreaSelected->GetStartRowIndex())->Remove(textEdit->textAreaSelected->GetStartCharacterIndex());
			}
			i = 0;
			while (i < textEdit->textAreaSelected->GetEndRowIndex() - textEdit->textAreaSelected->GetStartRowIndex() - 1) { // �߰��� ������ �߰���
				textEdit->text->Remove(textEdit->textAreaSelected->GetStartRowIndex() + 1);
				i++;
			}
			i = 0; // ���� �Ʒ���
			while (i < textEdit->textAreaSelected->GetEndCharacterIndex()) {
				textEdit->text->GetAt(textEdit->textAreaSelected->GetStartRowIndex() + 1)->Remove(0);
				i++;
			}
			// �� �Ʒ��� ������ �����شٰ� ��ŸƮ�ο쿡 �ٿ��ְ� �ؿ��� ����������
			i = 0;
			while (i < textEdit->text->GetAt(textEdit->textAreaSelected->GetStartRowIndex() + 1)->GetLength() - textEdit->textAreaSelected->GetEndCharacterIndex()) {
				if (dynamic_cast<DoubleByteCharacter*>(textEdit->text->GetAt(textEdit->textAreaSelected->GetStartRowIndex() + 1)->GetAt(i))) {
					DoubleByteCharacter *tempDouble = static_cast<DoubleByteCharacter*>(textEdit->text->GetAt(textEdit->textAreaSelected->GetStartRowIndex() + 1)->GetAt(i));
					textEdit->text->GetAt(textEdit->textAreaSelected->GetStartRowIndex())->Add(tempDouble->Clone());
					i++;
				}
				else if (dynamic_cast<SingleByteCharacter*>(textEdit->text->GetAt(textEdit->textAreaSelected->GetStartRowIndex() + 1)->GetAt(i))) {
					SingleByteCharacter *tempSingle = static_cast<SingleByteCharacter*>(textEdit->text->GetAt(textEdit->textAreaSelected->GetStartRowIndex() + 1)->GetAt(i));
					textEdit->text->GetAt(textEdit->textAreaSelected->GetStartRowIndex())->Add(tempSingle->Clone());
					i++;
				}
			}
			textEdit->text->Remove(textEdit->textAreaSelected->GetStartRowIndex() + 1);
		}
		textEdit->caret->SetRowIndex(textEdit->textAreaSelected->GetStartRowIndex());
		textEdit->caret->SetCharacterIndex(textEdit->textAreaSelected->GetStartCharacterIndex());
		textEdit->flagSelection = 0;
	}
	else {
		if (textEdit->caret->GetCharacterIndex() < textEdit->text->GetAt(textEdit->caret->GetRowIndex())->GetLength()) {
			textEdit->historyText->PushUndo(textEdit->text, textEdit->caret);
			textEdit->text->GetAt(textEdit->caret->GetRowIndex())->Remove(textEdit->caret->GetCharacterIndex());
		}
		else if (textEdit->caret->GetCharacterIndex() == textEdit->text->GetAt(textEdit->caret->GetRowIndex())->GetLength()
			&& textEdit->caret->GetRowIndex() < textEdit->text->GetLength() - 1) {
			textEdit->historyText->PushUndo(textEdit->text, textEdit->caret);
			Long i = 0;
			while (i < textEdit->text->GetAt(textEdit->caret->GetRowIndex() + 1)->GetLength()) {
				textEdit->text->GetAt(textEdit->caret->GetRowIndex())->Add(textEdit->text->GetAt(textEdit->caret->GetRowIndex() + 1)->GetAt(i));
				i++;
			}
			textEdit->text->Remove(textEdit->caret->GetRowIndex() + 1);
		}
	}
}

