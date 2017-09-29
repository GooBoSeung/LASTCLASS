//HistoryGraphic.h

#ifndef _HISTORYGRAPHIC_H
#define _HISTORYGRAPHIC_H

#include "Array.h"

typedef signed long int Long;

class Diagram;

class HistoryGraphic {
public:
	HistoryGraphic();
	HistoryGraphic(const HistoryGraphic& source);
	~HistoryGraphic();

	void PushUndo(Diagram *diagram);
	Diagram* PopUndoGraphic();

	void PushRedo(Diagram *diagram);
	Diagram* PopRedoGraphic();

	Diagram* GetUndoArray() const;
	Diagram* GetRedoArray() const;
public:
	Array<Diagram*>*undoGraphicArray;
	Array<Diagram*>*redoGraphicArray;
};

inline Diagram* HistoryGraphic::GetUndoArray() const {
	// �ʿ��ϸ� �迭 ��ü ���߿�
}
inline Diagram* HistoryGraphic::GetRedoArray() const {
	// �ʿ��ϸ� �迭 ��ü ���߿�
}

#endif //!_HISTORYGRAPHIC_H
