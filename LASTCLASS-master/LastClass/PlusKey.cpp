//PlusKey.cpp

#include "PlusKey.h"
#include "TextEdit.h"
#include "Text.h"
#include "Row.h"
#include "Caret.h"

PlusKey::PlusKey() {
}

PlusKey::PlusKey(const PlusKey& source) {
}

PlusKey::~PlusKey() {
}

void PlusKey::KeyPress(TextEdit *textEdit) {
	textEdit->rowHeight++;
}