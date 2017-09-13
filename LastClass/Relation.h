
//Relation.h
#ifndef _RELATION_H
#define _RELATION_H


#include "Figure.h"
#include "DrawingVisitor.h"

typedef signed long int Long;

//enum Type { GENERALIZATION = 1, REALIZATION = 2, DEPENDENCY = 3, ASSOCIATION = 4, DIRECTEDASSOCIATION = 5, AGGREGATION = 6, AGGREGATIONS = 7, COMPOSITION = 8, COMPOSITIONS = 9 };	// 1:�Ϲ�ȭ , 2:��üȭ ,3:���� , 4:����ȭ ,5:�������� , 6:���� ,7:���տ��� ,8:�ռ� , 9:���տ���

class Relation : public Figure {



public:
	Relation();
	Relation(const Relation& source);
	Relation(Long x, Long y, Long width, Long height);
	virtual ~Relation() = 0;
	Relation& operator = (const Relation& source);

	//void Accept(Visitor& visitor, CDC* cPaintDc);// CDC *cPaintDc
	Figure* Clone()const = 0;
};
#endif // !_RELATION_H