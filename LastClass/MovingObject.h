//MovingObject.h

#ifndef _MOVINGOBJECT_H
#define _MOVINGOBJECT_H

#include "MouseLButtonAction.h"

class MovingObject :public MouseLButtonAction {
public:
	static MouseLButtonAction* Instance();

	virtual void MouseLButtonUp(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY);
	virtual void MouseLButtonDown(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY);
	virtual void MouseLButtonDrag(MouseLButton *mouseLButton, Diagram *diagram, Selection *selection, Long  startX, Long startY, Long currentX, Long currentY, CPaintDC *cPatinDC);

protected:
	//DrawingClass();
private:
	static MovingObject* instance;
};

#endif // !_MOVINGOBJECT_H

