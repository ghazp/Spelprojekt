#include "ConfigFile.h"
#include <fstream>

ConfigFile::ConfigFile()
{
	this->m_windowed = DEFAULT_WINDOWED;
	this->m_screenSize = new D3DXVECTOR2(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT);
}

ConfigFile::~ConfigFile()
{
	delete this->m_screenSize;
}

const D3DXVECTOR2* ConfigFile::getScreenSize()const
{
	return this->m_screenSize;
}

int ConfigFile::getScreenSizeX()const
{
	return int(this->m_screenSize->x);
}

int ConfigFile::getScreenSizeY()const
{
	return int(this->m_screenSize->y);
}

bool ConfigFile::getWindowed()const
{
	return this->m_windowed;
}

void ConfigFile::load()
{
	// Open and read config file
	ifstream stream;
	stream.open("config.ini");
	if(stream.is_open())
	{
		while(!stream.eof())
		{
			char buf[1024];
			char key[100];
			stream.getline(buf, 1024);
			sscanf(buf, "%s", key);
			if(strcmp(key, "windowed") == 0)
			{
				int temp;
				sscanf(buf, "windowed %d", &temp);
				this->m_windowed = temp;
			}
			else if(strcmp(key, "resolution") == 0)
			{
				int x, y;
				sscanf(buf, "resolution %d %d", &x, &y);
				this->m_screenSize->x = x;
				this->m_screenSize->y = y;
			}
		}
	}

	stream.close();
}