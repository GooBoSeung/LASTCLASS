//Diagram.cpp

#include "Diagram.h"
#include "Class.h"
#include "MemoBox.h"
#include "SmartPointer.h"
#include "Template.h"
#include "Relation.h"
#include "SelfRelation.h"
#include "Finder.h"
#include "MemoLine.h"

Diagram::Diagram(Long capacity) {
	this->capacity = capacity;
	this->length = 0;
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;
}

Diagram::~Diagram() {
}

Diagram::Diagram(const Diagram& source) : FigureComposite(source) {
	/*this->figures = source.figures;
	Long i = 0;
	while (i < this->length) {
		this->figures.Modify(i, (const_cast<Diagram&>(source)).figures[i]->Clone());
		i++;
	}*/
}

Diagram& Diagram::operator = (const Diagram& source) {
	this->figures = source.figures;
	Long i = 0;
	while (i < this->length) {
		this->figures.Modify(i, (const_cast<Diagram&>(source)).figures[i]->Clone());
		i++;
	}
	this->capacity = source.capacity;
	this->length = source.length;
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->length = source.length;

	return *this;
}

Figure* Diagram::operator [] (Long index) {
	return this->figures[index];
}

Long  Diagram::Add(Figure *figure) {
	Long index;
	if (this->length < this->capacity) {
		index = this->figures.Store(this->length, figure);
	}
	else {
		index = this->figures.AppendFromRear(figure);
		this->capacity++;
	}
	this->length++;

	return index;
}

Long Diagram::AddClass(Long x, Long y, Long width, Long height) {
	Class object(x, y, width, height);
	Long index;

	if (this->length < this->capacity) {
		index = this->figures.Store(this->length, object.Clone());
	}
	else {
		index = this->figures.AppendFromRear(object.Clone());
		this->capacity++;
	}
	this->length++;
	return index;
}
Long Diagram::AddMemoBox(Long x, Long y, Long width, Long height) {
	MemoBox object(x, y, width, height);
	Long index;

	if (this->length < this->capacity) {
		index = this->figures.Store(this->length, object.Clone());
	}
	else {
		index = this->figures.AppendFromRear(object.Clone());
		this->capacity++;
	}
	this->length++;
	return index;
}

Figure* Diagram::FindItem(Long x, Long y) {
	SmartPointer<Figure*> smartPointer(this->CreateIterator());//다이어그램 배열 반복자
	Figure *figure = 0;
	Long endX;
	Long endY;
	Long index = -1;
	smartPointer->First();
	while (!smartPointer->IsDone() && index != 0) {
		endX = smartPointer->Current()->GetX() + smartPointer->Current()->GetWidth();
		endY = smartPointer->Current()->GetY() + smartPointer->Current()->GetHeight();
		if (smartPointer->Current()->GetX() <= x && endX >= x && smartPointer->Current()->GetY() <= y && endY >= y) {
			figure = smartPointer->Current();
			index = 0;
		}
		else if (dynamic_cast<Class*>(smartPointer->Current()) && static_cast<Class*>(smartPointer->Current())->GetTempletePosition() != -1) {
			Template* objcet = static_cast<Template*>(static_cast<Class*>(smartPointer->Current())->GetAt(static_cast<Class*>(smartPointer->Current())->GetTempletePosition()));
			if (objcet->GetX() <= x && objcet->GetX() + objcet->GetWidth() >= x &&
				objcet->GetY() <= y && objcet->GetY() + objcet->GetHeight() >= y) {
				figure = smartPointer->Current();
				index = 0;
			}
		}
		smartPointer->Next();
	}
	if (index == 0) {
		SmartPointer<Figure*> smartPointer_(static_cast<FigureComposite*>(figure)->CreateIterator()); //클래스 배열 반복자
		for (smartPointer_->First(); !smartPointer_->IsDone(); smartPointer_->Next()) {
			if (smartPointer_->Current()->GetX() <= x && smartPointer_->Current()->GetX() + smartPointer_->Current()->GetWidth() >= x
				&& smartPointer_->Current()->GetY() <= y && smartPointer_->Current()->GetY() + smartPointer_->Current()->GetHeight() >= y) {
				figure = smartPointer_->Current();
			}
		}
	}
	return figure;
}

Long Diagram::Remove(Long index) {

	this->length--;
	this->capacity--;

	return this->figures.Delete(index);
}

CRect Diagram::GetCorrectRect(Long startX, Long startY, Long currentX, Long currentY) {
	CRect rect(0,0,0,0);
	if (currentX >= startX && currentY >= startY) {
		rect.left = startX;
		rect.top = startY;
		rect.right = currentX;
		rect.bottom = currentY;
	}
	else if (currentX < startX && currentY < startY) {
		rect.left = currentX;
		rect.top = currentY;
		rect.right = startX;
		rect.bottom = startY;
	}
	else if (currentX > startX) {
		rect.left = startX;
		rect.top = currentY;
		rect.right = currentX;
		rect.bottom = startY;
	}
	else {
		rect.left = currentX;
		rect.top = startY;
		rect.right = startX;
		rect.bottom = currentY;
	}

	return rect;
}

bool Diagram::CheckOverlap(CRect object, FigureComposite *execpt) {
	bool ret = false;
	Long i = 0;

	Finder finder;
	object.left -= 9;
	object.top -= 9;
	object.right += 9;
	object.bottom += 9;
	while (i < this->length && ret == false) {
		FigureComposite *figureComposite = static_cast<FigureComposite*>(this->GetAt(i));
		if (figureComposite != execpt) {
			CRect rect(figureComposite->GetX(), figureComposite->GetY(), figureComposite->GetX() + figureComposite->GetWidth(), figureComposite->GetY() + figureComposite->GetHeight());
			ret = finder.FindRectangleByArea(rect, object);
		}
		i++;
	}
	return ret;
}

bool Diagram::CheckOverlapSelection(CRect object, FigureComposite *execpt) {
	bool ret = false;
	Long i = 0;

	Finder finder;
	object.left -= 9;
	object.top -= 9;
	object.right += 9;
	object.bottom += 9;
	while (i < this->length && ret == false) {
		FigureComposite *figureComposite = static_cast<FigureComposite*>(this->GetAt(i));
		Long j = 0;
		if (dynamic_cast<Class*>(figureComposite) || dynamic_cast<MemoBox*>(figureComposite)) {
			while (j < execpt->GetLength() && figureComposite != static_cast<FigureComposite*>(execpt->GetAt(j))) {
				j++;
			}

			if (j >= execpt->GetLength()) {
				CRect rect(figureComposite->GetX(), figureComposite->GetY(), figureComposite->GetX() + figureComposite->GetWidth(), figureComposite->GetY() + figureComposite->GetHeight());
				ret = finder.FindRectangleByArea(rect, object);
			}
		}
		i++;
	}
	return ret;
}

Figure* Diagram::GetAt(Long index) {
	return static_cast<Figure*>(this->figures.GetAt(index));
}

Figure* Diagram::Clone() const {
	return new Diagram(*this);
}

void Diagram::Accept(Visitor& visitor, CDC *pDC) {
	SmartPointer<Figure*> smartPointer(this->CreateIterator());
	while (!smartPointer->IsDone()) {
		if (dynamic_cast<Class*>(smartPointer->Current())) {
			static_cast<Class*>(smartPointer->Current())->Accept(visitor, pDC);
			Long  i = 0;
			
			while (i < static_cast<Class*>(smartPointer->Current())->GetLength()) {
				if (dynamic_cast<Relation*>(static_cast<Class*>(smartPointer->Current())->GetAt(i)) &&  !dynamic_cast<MemoLine*>(static_cast<Class*>(smartPointer->Current())->GetAt(i))) {
					static_cast<Relation*>(static_cast<Class*>(smartPointer->Current())->GetAt(i))->Accept(visitor, pDC);
				}
				if (dynamic_cast<SelfRelation*>(static_cast<Class*>(smartPointer->Current())->GetAt(i))) {
					static_cast<SelfRelation*>(static_cast<Class*>(smartPointer->Current())->GetAt(i))->Accept(visitor, pDC);
				}
					i++;
			}
		}
		if (dynamic_cast<MemoBox*>(smartPointer->Current())) {
			static_cast<MemoBox*>(smartPointer->Current())->Accept(visitor, pDC);
		}
		smartPointer->Next();
	}
}

string Diagram::FindLongString(string str) {
	int i = 0;
	int startIndex = 0;
	int endIndex = 0;
	int length = 0;
	int j;
	while (str[i] != '\0') {
		j = i;
		while (str[i] != '\n' && str[i] != '\0') {
			i++;
		}
		if (i - j>length) {
			startIndex = j;
			endIndex = i;
			length = i - j;
		}
		if (i < int(str.length())) {
			i++;
		}
	}
	char temp[100];
	int k = 0;
	while (startIndex < endIndex) {
		temp[k] = str[startIndex];
		k++;
		startIndex++;
	}
	temp[k] = '\0';
	string str_ = temp;

	return str_;
}