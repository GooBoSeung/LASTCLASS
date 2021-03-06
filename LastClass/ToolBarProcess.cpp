//ToolBarProcess.cpp

#include "ToolBarProcess.h"
#include "LastClass.h"
#include "ClassMenuAction.h"
#include "MemoBoxMenuAction.h"
#include "GeneralizationMenuAction.h"
#include "RealizationMenuAction.h"
#include "DependencyMenuAction.h"
#include "AssociationMenuAction.h"
#include "DirectedAssociationMenuAction.h"
#include "AggregationMenuAction.h"
#include "AggregationsMenuAction.h"
#include "CompositionMenuAction.h"
#include "CompositionsMenuAction.h"
#include "MemoLineMenuAction.h"
#include "OpenMenuAction.h"
#include "SaveMenuAction.h"
#include "SaveAsMenuAction.h"
#include "NewMenuAction.h"
#include "FilePrintPreviewMenuAction.h"
#include "SupportMenuAction.h"
#include "GraphicCtrlCopyKey.h"
#include "GraphicCtrlCutKey.h"
#include "GraphicCtrlPasteKey.h"
#include "GraphicCtrlRedoMenuAction.h"
#include "GraphicCtrlUndoMenuAction.h"
#include "ClassDiagramForm.h"
#include "GraphicCtrlCutMenuAction.h"
#include "GraphicCtrlCopyMenuAction.h"
#include "GraphicCtrlPasteMenuAction.h"
#include "DeleteGraphicKeyMenuAction.h"
#include "FilePrintMenuAction.h"
#include "AboutMenuAction.h"

ToolBarProcess::ToolBarProcess() {
}
ToolBarProcess::ToolBarProcess(const ToolBarProcess& source) {
}
ToolBarProcess::~ToolBarProcess() {
}
void ToolBarProcess::OnNewFileClicked(LastClass *lastClass) {
	NewMenuAction newMenuAction;
	newMenuAction.MenuPress(lastClass);
}
void ToolBarProcess::OnOpenClicked(LastClass *lastClass) {
	OpenMenuAction openMenuAction;
	openMenuAction.MenuPress(lastClass);
}
void ToolBarProcess::OnSaveFileClicked(LastClass *lastClass) {
	SaveMenuAction saveMenuAction;
	saveMenuAction.MenuPress(lastClass);
}
void ToolBarProcess::OnRedoFileClicked(LastClass *lastClass) {
	GraphicCtrlRedoMenuAction graphicCtrlRedoMenuAction;
	graphicCtrlRedoMenuAction.MenuPress(lastClass);
}
void ToolBarProcess::OnUndoFileClicked(LastClass *lastClass) {
	GraphicCtrlUndoMenuAction graphicCtrlUndoMenuAction;
	graphicCtrlUndoMenuAction.MenuPress(lastClass);
}
void ToolBarProcess::OnCutFileClicked(LastClass *lastClass) {
	GraphicCtrlCutMenuAction graphicCtrlCutMenuAction;
	graphicCtrlCutMenuAction.MenuPress(lastClass);
}
void ToolBarProcess::OnCopyFileClicked(LastClass *lastClass) {
	GraphicCtrlCopyMenuAction graphicCtrlCopyMenuAction;
	graphicCtrlCopyMenuAction.MenuPress(lastClass);
}
void ToolBarProcess::OnPasteFileClicked(LastClass *lastClass) {
	GraphicCtrlPasteMenuAction graphicCtrlPasteMenuAction;
	graphicCtrlPasteMenuAction.MenuPress(lastClass);
}
void ToolBarProcess::OnFinishFileClicked(LastClass *lastClass) {
	DeleteGraphicKeyMenuAction deleteGraphicKeyMenuAction;
	deleteGraphicKeyMenuAction.MenuPress(lastClass);
}
void ToolBarProcess::OnPrintFileClicked(LastClass *lastClass) {
	FilePrintMenuAction filePrintMenuAction;
	filePrintMenuAction.MenuPress(lastClass);
}
void ToolBarProcess::OnPrintPreFileClicked(LastClass *lastClass) {
	FilePrintPreviewMenuAction filePrintPreviewMenuAction;
	filePrintPreviewMenuAction.MenuPress(lastClass);
}
void ToolBarProcess::OnSupportFileClicked(LastClass *lastClass) {
	SupportMenuAction supportMenuAction;
	supportMenuAction.MenuPress(lastClass);
}
void ToolBarProcess::OnAboutFileClicked(LastClass *lastClass) {
	AboutMenuAction aboutMenuAction;
	aboutMenuAction.MenuPress(lastClass);
}
