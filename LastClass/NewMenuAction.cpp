#include "NewMenuAction.h"
#include "ClassDiagramForm.h"
#include "MouseLButton.h"
#include "Diagram.h"
#include "Selection.h"
#include "HistoryGraphic.h"
#include "VerticalScrollBar.h"
#include "HorizontalScrollBar.h"
#include "KeyBoard.h"
#include <afxdlgs.h>
using namespace std;

NewMenuAction::NewMenuAction() {
}
NewMenuAction::~NewMenuAction() {
}
void NewMenuAction::MenuPress(ClassDiagramForm *classDiagramForm) {
	int messageBox = IDNO;
	if (classDiagramForm->historyGraphic->undoGraphicArray->GetLength() != 0) {
		if (classDiagramForm->fileName != "") {
			CString object;
			object = "���泻���� ";
			object.Append(classDiagramForm->fileName);
			object.Append("�� �����Ͻðڽ��ϱ�?");
			messageBox = classDiagramForm->MessageBox(object, "ClassDiagram", MB_YESNOCANCEL);
		}
		else {
			messageBox = classDiagramForm->MessageBox(_T("���� ������ ���� ������ �����Ͻðڽ��ϱ�?"), "ClassDiagram", MB_YESNOCANCEL);
			if (messageBox == IDYES) {
				CFileDialog  dlgFile(false, "txt", "*", OFN_CREATEPROMPT | OFN_OVERWRITEPROMPT, "�ؽ�Ʈ ����(*.txt)");
				if (dlgFile.DoModal() == IDOK)
				{
					classDiagramForm->fileName = dlgFile.GetPathName();
				}
			}
		}
		if (messageBox == IDYES) {
			classDiagramForm->Save();
		}
	}
	if (messageBox != IDCANCEL) {
		if (classDiagramForm->diagram != NULL) {
			delete classDiagramForm->diagram;
		}
		if (classDiagramForm->selection != NULL) {
			delete classDiagramForm->selection;
		}
		if (classDiagramForm->mouseLButton != NULL) {
			delete classDiagramForm->mouseLButton;
		}
		if (classDiagramForm->keyBoard != NULL) {
			delete classDiagramForm->keyBoard;
		}
		if (classDiagramForm->historyGraphic != NULL) {
			delete classDiagramForm->historyGraphic;
		}
		if (classDiagramForm->verticalScrollBar != NULL) {
			delete classDiagramForm->verticalScrollBar;
		}
		if (classDiagramForm->horizontalScroll != NULL) {
			delete classDiagramForm->horizontalScroll;
		}
		classDiagramForm->diagram = new Diagram();
		classDiagramForm->selection = new Selection;
		classDiagramForm->mouseLButton = new MouseLButton;
		classDiagramForm->historyGraphic = new HistoryGraphic;
		classDiagramForm->verticalScrollBar = new VerticalScrollBar(classDiagramForm);
		classDiagramForm->horizontalScroll = new HorizontalScrollBar(classDiagramForm);
		classDiagramForm->keyBoard = new KeyBoard;
		classDiagramForm->fileName = "";
	}
	classDiagramForm->Invalidate(false);
}