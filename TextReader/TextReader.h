#pragma once
#include "stdafx.h"
#include <functional>

#define INI_TEXTREADER_SECTION "TextReader"

#define GetTextReader TextReader::GetInstance


class TextReader
{
	bool m_debug;
	bool LoadConfig();

	static TextReader* instance;	

public:
	TextReader();
	~TextReader();

	static TextReader* GetInstance()
	{
		if (!instance)
			instance = new TextReader();
		return instance;
	}

	std::function<void(int)> OnResult;
	std::function<void(std::string)> OnLog;
	void Report(const char* fmt, ...);

	std::string ReadText(std::string filePath);
};

