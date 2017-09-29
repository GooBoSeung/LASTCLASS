//Figure.cpp

#include "Figure.h"
#include "Relation.h"

Figure::Figure() {
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;
	this->content = "";
	this->stringHeight = 18; // ���� ���� ũ�⿡ ���� ���� ����ϳ�
	this->stringWidth = 0;
	this->fontSize = 25;
}

Figure::Figure(Long x, Long y, Long width, Long height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->content = "";
	this->stringHeight = 18;
	this->stringWidth = 0;
	this->fontSize = 25;
}

Figure::Figure(Long x, Long y, Long width, Long height, string content) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->content = content;
	this->stringHeight = 18; // �Է¹��� ���ڿ��� �°� �� ����ϴµ�
	this->stringWidth = 0;
	this->fontSize = 25;
}

Figure::Figure(const Figure& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	this->stringHeight = source.stringHeight;
	this->stringWidth = source.stringWidth;
	this->fontSize = source.fontSize;
}
Figure* Figure::Move(Long distanceX , Long distanceY) {
	this->x = this->x + distanceX;
	this->y = this->y + distanceY;
	if (dynamic_cast<Relation*>(this)) {
		this->width = this->width - distanceX;
		this->height = this->height - distanceY;
	}
	return this;
}
Long Figure::GetRowCount(string object) {
	Long count = 0;
	Long i = 0;
	while (object[i] != '\0') {
		if (object[i] == '\n') {
			count++;
		}
		i++;
	}
	count++; // ������ �����Ǳ⶧���� ��������.
	return count;
}
Figure *Figure::EndPointMove(Long distanceX, Long distanceY) {
	this->width = this->width + distanceX;
	this->height = this->height + distanceY;
	return this;
}

Figure* Figure::Modify(Long x, Long y, Long width, Long height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;

	return this;
}

Figure& Figure::operator = (const Figure& source) {
	this->x = source.x;
	this->y = source.y;
	this->width = source.width;
	this->height = source.height;
	this->stringHeight = source.stringHeight;
	this->fontSize = source.fontSize;
	return *this;
}

Figure::~Figure() {
}


void Figure::ReplaceString(string content , Long fontSize) {
	this->content = content;
	this->fontSize = fontSize;
}

void Figure::SetX(Long x) {
	this->x = x;
}

void Figure::SetY(Long y) {
	this->y = y;
}

void Figure::SetWidth(Long width) {
	this->width = width;
}

void Figure::SetHeight(Long height) {
	this->height = height;
}