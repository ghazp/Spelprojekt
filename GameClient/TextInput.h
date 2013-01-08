#pragma once

#include "MyText.h"
#include "DataStructures.h"

class TextInput
{
private:
	string m_text;
	MyText* m_myText;
	float m_timer;
public:
	TextInput();
	TextInput(string _texture, INT2 _pos, int _size);
	~TextInput();

	void update(float _dt);
};