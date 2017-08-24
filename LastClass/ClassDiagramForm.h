//ClassDiagramForm.h

#ifndef _CLASSDIAGRAM_H
#define _CLASSDIAGRAM_H

#include <afxwin.h>
typedef signed long int Long;

class Diagram; //���漱��
class ClassDiagramForm : public CFrameWnd { //CFrameWnd �� ��Ӱ��� ǥ��
public:
	Diagram *diagram;
public:
	ClassDiagramForm(); // �̰� ������????
private:
	Long startX;
	Long startY;
	Long currentX;
	Long currentY;
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	//afx_msg void OnDrawDot();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
};

#endif // _CLASSDIAGRAM_H
