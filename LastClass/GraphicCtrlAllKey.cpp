//GraphicCtrlAllKey.cpp

#include "GraphicCtrlAllKey.h"
#include "ClassDiagramForm.h"
#include "Diagram.h"
#include "Selection.h"
#include "MouseLButton.h"
#include "MouseLButtonAction.h"
#include "SelectionState.h"
#include "MultipleSelectionState.h"

GraphicCtrlAllKey::GraphicCtrlAllKey() {
}

GraphicCtrlAllKey::GraphicCtrlAllKey(const GraphicCtrlAllKey& source) {
}

GraphicCtrlAllKey::~GraphicCtrlAllKey() {
}

void GraphicCtrlAllKey::KeyPress(ClassDiagramForm *classDiagramForm) {
	Long i = 0;
	classDiagramForm->selection->DeleteAllItems();
	while (i < classDiagramForm->diagram->GetLength()) {
		classDiagramForm->selection->Add(classDiagramForm->diagram->GetAt(i));
		//j = 0; // ��ü���� ������ �� ǥ�� ������ �Ϸ��� Ŭ�����϶� ���ο� �� ���� selection �迭�� �־��ִ°� �ʿ��� // �ٵ� �ʿ������
		//while (classDiagramForm->diagram->GetAt(i)->
		i++;
	}
	if (classDiagramForm->selection->GetLength() == 1) {
		classDiagramForm->mouseLButton->ChangeState(SelectionState::Instance());
	}
	if (classDiagramForm->selection->GetLength() > 1) {
		classDiagramForm->mouseLButton->ChangeState(MultipleSelectionState::Instance());
	}
}

void GraphicCtrlAllKey::KeyPress(TextEdit *textEdit) {
}