#include "SaveMenuAction.h"
#include "ClassDiagramForm.h"
#include <afxdlgs.h>
using namespace std;
SaveMenuAction::SaveMenuAction() {
}
SaveMenuAction::~SaveMenuAction() {
}
void SaveMenuAction::MenuPress(ClassDiagramForm *classDiagramForm) {
	if (classDiagramForm->fileName == "") {
		int messageBox = classDiagramForm->MessageBox(_T("���� ������ ���� ������ �����Ͻðڽ��ϱ�?"), "ClassDiagram", MB_YESNOCANCEL);
		if (messageBox == IDYES) {
			CFileDialog  dlgFile(false, "txt", "*", OFN_CREATEPROMPT | OFN_OVERWRITEPROMPT, "�ؽ�Ʈ ����(*.txt)");
			if (dlgFile.DoModal() == IDOK){
				classDiagramForm->fileName = dlgFile.GetPathName();
				classDiagramForm->Save();
			}
		}
	}
		

}