
//----------------------------------------------------------------------------------------------------------------------------
//	Made by Emil Rudvi - Text with spritesheet
//----------------------------------------------------------------------------------------------------------------------------

#include "MyText.h"

MyText::MyText()
{
	this->m_texture = NULL;
	this->m_VertexBuffer = NULL;
}

MyText::MyText(ID3D10Device* _device, ID3D10ShaderResourceView* _texture, float _height, float _width, D3DXCOLOR _color, D3DXVECTOR3 _pos, float _size)
{
	int maxNrOfPoints = 1000;
	this->m_height = _height;
	this->m_width =  _width;
	this->m_color = _color;
	this->m_pos = _pos;
	this->m_size = _size;
	this->m_FontSize = _size;
	m_pos.x = _pos.x -(_size/3.0f);
	m_pos.y = _pos.y;
	//Create the buffer
	D3D10_BUFFER_DESC tbd;
	tbd.Usage = D3D10_USAGE_DYNAMIC;
	tbd.ByteWidth =sizeof(writeText)* maxNrOfPoints;
	tbd.BindFlags = D3D10_BIND_VERTEX_BUFFER;
	tbd.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
	tbd.MiscFlags = 0;

	_device->CreateBuffer(&tbd, NULL, &this->m_VertexBuffer);

	//Create the texture (for the font)

	this->m_texture = _texture;
}

MyText::~MyText()
{
	if(this->m_texture)
		this->m_texture->Release();
	if(this->m_VertexBuffer)
		this->m_VertexBuffer->Release();
}

void MyText::setPos(D3DXVECTOR3 _pos)
{
	this->m_pos = _pos;
}

void MyText::DrawString(string str, float _size)
{
	//----------------------------------------------------------------------------------------------------------------------------
	//	Restets string without this you could get some troubles with the triangles
	//----------------------------------------------------------------------------------------------------------------------------
		m_str = str;
		int m_number = 0;
		m_numberOfPoints= m_str.size()*6;
		m_textS.clear();
		m_textS.resize(m_numberOfPoints);
	//----------------------------------------------------------------------------------------------------------------------------
	//	Rules for text
	//	Offset, FontSize, NewLine and also converts screenspace to pixels on the screen
	//	Offset and FontSize shall be change later on!
	//----------------------------------------------------------------------------------------------------------------------------
		//_size = (_size /1920) * m_width;
		D3DXVECTOR3 Tmppos = D3DXVECTOR3((m_pos.x/m_width)*2.0f-1.0f, ((m_pos.y/m_height)*2.0f-1.0f)*-1.0f,0.0f);
		// Base size 80.0f
		float m_FontSize = m_size;
			  m_FontSize += _size;
		float OffsetSizeX =(m_size + _size)/2;
		float OffsetSizeY = m_size;
		D3DXVECTOR2 FontSizeOnScreen = D3DXVECTOR2((m_FontSize/m_width), (m_FontSize/m_height));
		float OffsetX = (OffsetSizeX/m_width);
		float OffsetY = (OffsetSizeY/m_height);
		float OffsetXOnScreen = (m_FontSize/m_width);
		float OffsetYOnScreen = (m_FontSize/m_height);
		float NewLineOfText = (m_FontSize/m_height);
		D3DXVECTOR2 TextCurrent[4];
		float Rows=0.0f;

	//----------------------------------------------------------------------------------------------------------------------------
	// Jumping in the spritesheet to get the right letter, symbol or number
	//----------------------------------------------------------------------------------------------------------------------------

	for each(char c in str)
    {
		char tmp = toupper(c);
		if (tmp == ' ')
        {
			TextCurrent[3] = D3DXVECTOR2(27.0f/28.0f, 0.0f/2.0f);
			//X = 1 Y = 0
			TextCurrent[2] = D3DXVECTOR2(28.0f/28.0f,0.0f/2.0f);
			//X = 0 Y = 1
		    TextCurrent[1] = D3DXVECTOR2(27.0f/28.0f, 1.0f/2.0f);
			//X = 1 Y = 1
			TextCurrent[0] = D3DXVECTOR2(28.0f/28.0f, 1.0f/2.0f);
        }
		if (tmp == '_')
        {
			Rows+=1.3f;
			Tmppos = D3DXVECTOR3((m_pos.x/m_width)*2.0f-1.0f, ((m_pos.y/m_height)*2.0f-1.0f)*-1.0f,0.0f);
			float TmpOffsetY =OffsetY*Rows/1.5f;
			Tmppos.y -=TmpOffsetY;
			continue;
        }
        if (tmp == '.')
        {
			//X = 0 Y = 0
            TextCurrent[3] = D3DXVECTOR2(18.0f/28.0f, 1.0f/2.0f);
			//X = 1 Y = 0
			TextCurrent[2] = D3DXVECTOR2(19.0f/28.0f, 1.0f/2.0f);
			//X = 0 Y = 1
		    TextCurrent[1] = D3DXVECTOR2(18.0f/28.0f, 2.0f/2.0f);
			//X = 1 Y = 1
			TextCurrent[0] = D3DXVECTOR2(19.0f/28.0f, 2.0f/2.0f);
        }
        if (tmp == '-')
		{
			//X = 0 Y = 0
			TextCurrent[3] = D3DXVECTOR2(26.0f/28.0f, 0.0f/2.0f);
			//X = 1 Y = 0
			TextCurrent[2] = D3DXVECTOR2(27.0f/28.0f, 0.0f/2.0f);
			//X = 0 Y = 1
		    TextCurrent[1] = D3DXVECTOR2(26.0f/28.0f, 1.0f/2.0f);
			//X = 1 Y = 1
			TextCurrent[0] = D3DXVECTOR2(27.0f/28.0f, 1.0f/2.0f);
        }
		if (tmp == '+')
		{
			//X = 0 Y = 0
			TextCurrent[3] = D3DXVECTOR2(11.0f/28.0f, 1.0f/2.0f);
			//X = 1 Y = 0
			TextCurrent[2] = D3DXVECTOR2(12.0f/28.0f, 1.0f/2.0f);
			//X = 0 Y = 1
		    TextCurrent[1] = D3DXVECTOR2(11.0f/28.0f, 2.0f/2.0f);
			//X = 1 Y = 1
			TextCurrent[0] = D3DXVECTOR2(12.0f/28.0f, 2.0f/2.0f);
        }
        if (tmp == ':')
        {
			//X = 0 Y = 0
			TextCurrent[3] = D3DXVECTOR2(12.0f/28.0f, 1.0f/2.0f);
			//X = 1 Y = 0
			TextCurrent[2] = D3DXVECTOR2(13.0f/28.0f, 1.0f/2.0f);
			//X = 0 Y = 1
		    TextCurrent[1] = D3DXVECTOR2(12.0f/28.0f, 2.0f/2.0f);
			//X = 1 Y = 1
			TextCurrent[0] = D3DXVECTOR2(13.0f/28.0f, 2.0f/2.0f);
        }
		if (tmp == '?')
        {
			//X = 0 Y = 0
			TextCurrent[3] = D3DXVECTOR2(16.0f/28.0f, 1.0f/2.0f);
			//X = 1 Y = 0
			TextCurrent[2] = D3DXVECTOR2(15.0f/28.0f, 1.0f/2.0f);
			//X = 0 Y = 1
		    TextCurrent[1] = D3DXVECTOR2(16.0f/28.0f, 2.0f/2.0f);
			//X = 1 Y = 1
			TextCurrent[0] = D3DXVECTOR2(15.0f/28.0f, 2.0f/2.0f);
        }
		if (tmp == '!')
        {
			//X = 0 Y = 0
			TextCurrent[3] = D3DXVECTOR2(16.0f/28.0f, 1.0f/2.0f);
			//X = 1 Y = 0
			TextCurrent[2] = D3DXVECTOR2(17.0f/28.0f, 1.0f/2.0f);
			//X = 0 Y = 1
		    TextCurrent[1] = D3DXVECTOR2(16.0f/28.0f, 2.0f/2.0f);
			//X = 1 Y = 1
			TextCurrent[0] = D3DXVECTOR2(17.0f/28.0f, 2.0f/2.0f);
        }
        if (tmp == '/')
        {
			//X = 0 Y = 0
			TextCurrent[3] = D3DXVECTOR2(2.0f/28.0f, 1.0f/2.0f);
			//X = 1 Y = 0
			TextCurrent[2] = D3DXVECTOR2(21.0f/28.0f, 1.0f/2.0f);
			//X = 0 Y = 1
		    TextCurrent[1] = D3DXVECTOR2(20.0f/28.0f, 2.0f/2.0f);
			//X = 1 Y = 1
			TextCurrent[0] = D3DXVECTOR2(21.0f/28.0f, 2.0f/2.0f);
        }
        if (tmp >= 'A' && tmp <= 'Z')
        {
			//X = 0 Y = 0
            TextCurrent[3] = D3DXVECTOR2(((float)tmp - 64.0f)/28.0f, 0.0f/2.0f);
			//X = 1 Y = 0
			TextCurrent[2] = D3DXVECTOR2(((float)tmp - (64.0f+1))/28.0f, 0.0f/2.0f);
			//X = 0 Y = 1
		    TextCurrent[1] = D3DXVECTOR2(((float)tmp - 64.0f)/28.0f, 1.0f/2.0f);
			//X = 1 Y = 1
			TextCurrent[0] = D3DXVECTOR2(((float)tmp - (64.0f+1))/28.0f, 1.0f/2.0f);
        }
        else if (tmp >= '0' && tmp <= '9')
        {
			//X = 0 Y = 0
            TextCurrent[3] = D3DXVECTOR2(((float)tmp - 103.0f)/28.0f, 1.0f/2.0f);
			//X = 1 Y = 0
			TextCurrent[2] = D3DXVECTOR2(((float)tmp - (103.0f+1))/28.0f, 1.0f/2.0f);
			//X = 0 Y = 1
		    TextCurrent[1] = D3DXVECTOR2(((float)tmp - 103.0f)/28.0f, 2.0f/2.0f);
			//X = 1 Y = 1
			TextCurrent[0] = D3DXVECTOR2(((float)tmp - (103.0f+1))/28.0f, 2.0f/2.0f);
		}
			Tmppos.x +=OffsetX;
			m_textS[m_number*6].POS = D3DXVECTOR3 (Tmppos.x, Tmppos.y,0.0f);
			//X = 1 Y = 0
			m_textS[m_number*6+1].POS = D3DXVECTOR3 (Tmppos.x+OffsetXOnScreen, Tmppos.y,0.0f);
			//X = 0 Y = 1
			m_textS[m_number*6+2].POS = D3DXVECTOR3 (Tmppos.x, Tmppos.y+OffsetYOnScreen,0.0f);
			//X = 0 Y = 1
			m_textS[m_number*6+3].POS = D3DXVECTOR3 (Tmppos.x, Tmppos.y+OffsetYOnScreen,0.0f);
			//X = 1 Y = 0
			m_textS[m_number*6+4].POS = D3DXVECTOR3 (Tmppos.x+OffsetXOnScreen, Tmppos.y,0.0f);
			//X = 1 Y = 1
			m_textS[m_number*6+5].POS = D3DXVECTOR3 (Tmppos.x+OffsetXOnScreen, Tmppos.y+OffsetYOnScreen,0.0f);

		//----------------------------------------------------------------------------------------------------------------------------			
		//	Sets Color of the text
		//----------------------------------------------------------------------------------------------------------------------------

			//m_textS[m_number*6].COLOR = m_color;
			//m_textS[m_number*6+1].COLOR = m_color;
			//m_textS[m_number*6+2].COLOR = m_color;
			//m_textS[m_number*6+3].COLOR = m_color;
			//m_textS[m_number*6+4].COLOR = m_color;
			//m_textS[m_number*6+5].COLOR = m_color;

		//----------------------------------------------------------------------------------------------------------------------------
		//	Builds up TextCoordinates
		//----------------------------------------------------------------------------------------------------------------------------

			//X = 0 Y = 0
			m_textS[m_number*6].UV = D3DXVECTOR2(TextCurrent[0]);
			//X = 1 Y = 0
			m_textS[m_number*6+1].UV = D3DXVECTOR2(TextCurrent[1]);
			//X = 0 Y = 1
			m_textS[m_number*6+2].UV = D3DXVECTOR2(TextCurrent[2]);
			//X = 0 Y = 1
			m_textS[m_number*6+3].UV = D3DXVECTOR2(TextCurrent[2]);
			//X = 1 Y = 0
			m_textS[m_number*6+4].UV = D3DXVECTOR2(TextCurrent[1]);
			//X = 1 Y = 1
			m_textS[m_number*6+5].UV = D3DXVECTOR2(TextCurrent[3]);
			m_number+=1;
	}

	//map the buffer
	writeText *vertexData = NULL;
	this->m_VertexBuffer->Map( D3D10_MAP_WRITE_DISCARD, 0, reinterpret_cast< void** >((void**)&vertexData));

	for(int i = 0; i < m_numberOfPoints; i++)
	{
		vertexData[i].POS = m_textS[i].POS;
		vertexData[i].UV = m_textS[i].UV;
		//vertexData[i].COLOR = m_textS[i].COLOR;
	}

	this->m_VertexBuffer->Unmap();
}

void MyText::Render()const
{
	//Set the shader resource
	/*this->m_GraphicsHandler->getEffectText()->GetVariableByName("MyText")->AsShaderResource()->SetResource(this->m_texture);

	//Draw the points
	UINT stride = sizeof(writeText);
	UINT offset = 0;
	m_device->IASetVertexBuffers( 0, 1, &m_VertexBuffer, &stride, &offset );
	m_device->IASetInputLayout( m_GraphicsHandler->getVertexLayoutText() );
	m_device->IASetPrimitiveTopology( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_GraphicsHandler->getTechRenderTextForward()->GetPassByIndex(0)->Apply(0);
	m_device->Draw(m_numberOfPoints,0);*/
}

D3DXMATRIX MyText::getModelMatrix()
{
	D3DXMATRIX modelMatrix;
	D3DXMatrixIdentity(&modelMatrix);
	return modelMatrix;
}

UINT MyText::GetStride()
{
	return sizeof(MyText::writeText);
}

int MyText::GetVertexNumber()
{
	return m_numberOfPoints;
}

string MyText::SendString(float floatInput)
{
	//----------------------------------------------------------------------------------------------------------------------------
	//	Send in an float and convert it to a string 
	//----------------------------------------------------------------------------------------------------------------------------

	string stringName; 
	char s[500];
	sprintf(s,"%.1f",floatInput);
	stringName.assign(s);
	return stringName;
}

string MyText::SendStringINT(int intInput)
{
	//----------------------------------------------------------------------------------------------------------------------------
	//	Send in an float and convert it to a string 
	//----------------------------------------------------------------------------------------------------------------------------

	string stringName; 
	char s[500];
	sprintf(s,"%i",intInput);
	stringName.assign(s);
	return stringName;
}