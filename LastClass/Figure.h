//Figure.h

#ifndef _FIGURE_H
#define _FIGURE_H
#include "Visitor.h"

typedef signed long int Long;

class Figure {
public:
	Figure();
	Figure(Long x, Long y, Long width, Long height);
	Figure(const Figure& source);
	Figure& operator = (const Figure& source);
	virtual ~Figure() = 0;

	virtual void Accept(Visitor& visitor, CDC *cPaintDc) = 0;
	virtual Figure* Clone() const = 0;

	Long GetX() const;
	Long GetY() const;
	Long GetWidth() const;
	Long GetHeight() const;
protected:
	Long x;
	Long y;
	Long width;
	Long height;
};

inline Long Figure::GetX() const {
	return this->x;
}
inline Long Figure::GetY() const {
	return this->y;
}
inline Long Figure::GetWidth() const {
	return this->width;
}
inline Long Figure::GetHeight() const {
	return this->height;
}

#endif //_FIGURE_H
