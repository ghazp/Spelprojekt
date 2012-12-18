#pragma once
#include <vector>
#include "GraphicsHandler.h"
#include "DataStructures.h"
#include "Model.h"
#include "Camera.h"
#include "Text.h"
#include "Sprite.h"
#include "SpriteSheet.h"

extern GraphicsHandler* g_graphicsEngine;

using namespace std;
class Button
{
private:
	//-----------------------------------------------------------------------------------------------
	// int for if button is Pressed UnPressed or Hovered
	//----------------------------------------------------------------------------------------------
		int m_ButtonReaction ;
		SpriteSheet* m_Button;
		
		int m_Delay;
		int m_DelayTime;
	//----------------------------------------------------------------------------------------------
	// Button size
	//----------------------------------------------------------------------------------------------
		INT2		m_Size;
	//----------------------------------------------------------------------------------------------
	// Button position
	//----------------------------------------------------------------------------------------------
		INT2		m_Pos;
		int			m_Max;
		int			m_Min;
		int			m_Keep;
		float		m_Value;
	//----------------------------------------------------------------------------------------------
	// Wave name
	//----------------------------------------------------------------------------------------------
		string			m_Sound;
	//----------------------------------------------------------------------------------------------
	// Textures used, text on button and active texture.
	//----------------------------------------------------------------------------------------------
		string			m_ButtonText;

		string			m_TextureName;

	//----------------------------------------------------------------------------------------------

public:
	Button();
	~Button();

	void Init(	INT2 _ScreenPos,
				INT2 _Size, 
				string _TextureName, 
				string _TextName,  
				int _min = 0, 
				int _max = 0, 
				float _textSize = 1,
				int _DelayTime = 100);
	int Clicked();
	void Update();
	int GetButtonReaction();
	float ReturnSliderValue();
};

