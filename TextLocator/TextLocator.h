#pragma once
#include "stdafx.h"
#include <functional>

#define INI_TextLocator_SECTION "TextLocator"

#define GetTextLocator TextLocator::GetInstance


class TextLocator
{
	bool m_debug;
	bool LoadConfig();

	static TextLocator* instance;	

public:
	TextLocator();
	~TextLocator();

	static TextLocator* GetInstance()
	{
		if (!instance)
			instance = new TextLocator();
		return instance;
	}

	std::function<void(int)> OnResult;
	std::function<void(std::string)> OnLog;
	void Report(const char* fmt, ...);

	std::string ReadText(std::string filePath);
};

