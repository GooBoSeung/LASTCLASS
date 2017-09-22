//CtrlCutKey.cpp

#include "CtrlCutKey.h"
#include "TextEdit.h"
#include "TextAreaSelected.h"
//#include "HistoryText.h"
#include "Text.h"
#include "Row.h"
#include "Caret.h"
#include "SingleByteCharacter.h"
#include "DoubleByteCharacter.h"

CtrlCutKey::CtrlCutKey() {
}
CtrlCutKey::CtrlCutKey(const CtrlCutKey& source) {
}
CtrlCutKey::~CtrlCutKey() {
}

void CtrlCutKey::KeyPress(TextEdit *textEdit) {
	if (GetKeyState(VK_CONTROL) < 0 && textEdit->flagSelection == 1) {
		OpenClipboard(NULL);
		EmptyClipboard();
		size_t cbstr = (textEdit->copyBuffer.GetLength() + 1) * sizeof(TCHAR);
		HGLOBAL h = GlobalAlloc(GMEM_MOVEABLE, cbstr);
		memcpy_s(GlobalLock(h), cbstr, textEdit->copyBuffer.LockBuffer(), cbstr);
		GlobalUnlock(h);
		textEdit->copyBuffer.UnlockBuffer();
		UINT uniFormat = (sizeof(TCHAR) == sizeof(WCHAR)) ? CF_UNICODETEXT : CF_TEXT;
		if (::SetClipboardData(uniFormat, h) == NULL) {
		}
		CloseClipboard();

		Long i = 0;
		if (textEdit->textAreaSelected->GetStartRowIndex() == textEdit->textAreaSelected->GetEndRowIndex()) {
			while (i < textEdit->textAreaSelected->GetEndCharacterIndex() - textEdit->textAreaSelected->GetStartCharacterIndex()) {
				textEdit->text->GetAt(textEdit->textAreaSelected->GetStartRowIndex())->Remove(textEdit->textAreaSelected->GetStartCharacterIndex());
				i++;
			}
		}
		else if (textEdit->textAreaSelected->GetStartRowIndex() < textEdit->textAreaSelected->GetEndRowIndex()) { // �������̸�
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
}