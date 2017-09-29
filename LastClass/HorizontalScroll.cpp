#include "HorizontalScroll.h"
#include "ClassDiagramForm.h"


HorizontalScroll::HorizontalScroll(ClassDiagramForm *classDiagramForm) :Scroll(classDiagramForm) {
	CRect cRect;
	SCROLLINFO  scrinfo;
	classDiagramForm->GetClientRect(&cRect);
	this->scrollBar->Create(SBS_HORZ, CRect(cRect.left , cRect.bottom -20, cRect.right - 20, cRect.bottom ), this->classDiagramForm, 1);

	scrinfo.cbSize = sizeof(scrinfo);
	scrinfo.fMask = SIF_ALL;
	scrinfo.nMin = 0;          // �ּҰ�
	scrinfo.nMax = cRect.right - 20;      // �ִ밪
	scrinfo.nPage = 150;      // ���������� ������
	scrinfo.nTrackPos = 0;  // Ʈ���ٰ� �����϶��� ��ġ��
	scrinfo.nPos = 0;        // ��ġ
	this->scrollBar->SetScrollInfo(&scrinfo);
	this->scrollBar->ShowScrollBar(SB_BOTH);
}
HorizontalScroll::HorizontalScroll(const HorizontalScroll& source) :Scroll(source) {
}
HorizontalScroll& HorizontalScroll::operator=(const HorizontalScroll& source) {
	Scroll::operator=(source);
	return *this;
}
HorizontalScroll::~HorizontalScroll() {

}