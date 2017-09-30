//MouseLButton.h

#ifndef _MOUSELUTTON_H
#define _MOUSELUTTON_H

#include <afxwin.h>
using namespace std;


class MouseLButtonAction;
class Diagram;
class Selection;
typedef signed long int Long;

class MouseLButton {
public:
	MouseLButton();
	//~MouseLButton();

	void MouseLButtonUp(MouseLButton *mouseLButton,Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY);
	void MouseLButtonDown(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY);
	void MouseLButtonDrag(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY,CDC *pDC);
	void ChangeState(UINT nChar);
	void ChangeDefault();
	UINT GetButtonState()const;
private:
	friend class  MouseLButtonAction;
	
	void ChangeState(MouseLButtonAction *mouseLButtonAction, UINT nChar = 0);

private:
	MouseLButtonAction *state;
	UINT buttonState;
};
inline UINT MouseLButton::GetButtonState()const {
	return this->buttonState;
}
#endif
