//DrawingController.cpp

#include"DrawingController.h"
#include"ButtonState.h"
#include"Unclicked.h"

DrawingController::DrawingController() {
	this->buttonState = new Unclicked;
}

DrawingController::DrawingController(const DrawingController& source) {
	//this->buttonState = source.buttonState;
}

DrawingController::~DrawingController() {
	if (this->buttonState != 0) {
		delete this->buttonState;
	}
}

void DrawingController::ChangeState(Long key){
	this->buttonState->ChangeState(this, key);
}

void DrawingController::AddToArray(Diagram *diagram, Selection *selection, Long startX, Long startY, Long currentX, Long currentY) {
	this->buttonState->AddToArray(diagram, selection, startX, startY, currentX, currentY);
}


void DrawingController::Draw(Long startX, Long startY, Long currentX, Long currentY, CDC *cPaintDc) {
	this->buttonState->Draw(startX, startY, currentX, currentY, cPaintDc);
}

DrawingController& DrawingController::operator=(const DrawingController& source) {

	return const_cast<DrawingController&>(source);
}