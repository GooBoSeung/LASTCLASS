//OnVScrollLineDown.cpp

#include "OnVScrollLineDown.h"
#include "ClassDiagramForm.h"

OnVScrollLineDown::OnVScrollLineDown() {
}
OnVScrollLineDown::OnVScrollLineDown(const OnVScrollLineDown& source) {
}
OnVScrollLineDown::~OnVScrollLineDown() {
}

void OnVScrollLineDown::Scrolling(ClassDiagramForm *classDiagramForm) {
	int minpos;
	int maxpos;
	classDiagramForm->GetScrollRange(SB_VERT, &minpos, &maxpos);
	maxpos = classDiagramForm->GetScrollLimit(SB_VERT);

	// Get the current position of scroll box.
	int curpos = classDiagramForm->GetScrollPos(SB_VERT);

	curpos += 100;
	if (curpos > maxpos) {
		curpos = maxpos;
	}

	classDiagramForm->SetScrollPos(SB_VERT, curpos);
}