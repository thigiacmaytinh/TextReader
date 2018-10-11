#include "TextReader.h"
#include "TGMTcolor.h"
#include "TGMTConfig.h"
#include "TGMTdebugger.h"
#include "TGMTutil.h"
#include "TGMTimage.h"
#include "TGMTfile.h"
#include "TGMTtesseract.h"

TextReader* TextReader::instance = NULL;

////////////////////////////////////////////////////////////////////////////////////////////////////

TextReader::TextReader()
{
	WriteLog("--------------------Starting program-------------------");
	DeleteLog(7);
	if (m_debug)
	{
		TGMTfile::CreateDir("image");
	}

	LoadConfig();
}

////////////////////////////////////////////////////////////////////////////////////////////////////

bool TextReader::LoadConfig()
{
	if (!GetTGMTConfig()->LoadSettingFromFile("config.ini"))
	{
		PrintError("Can not read config.ini ");
		return false;
	}

	GetTGMTtesseract()->LoadConfig();

	m_debug = GetTGMTConfig()->ReadValueBool(INI_TEXTREADER_SECTION, "debug");

	Report("Load config complete");

	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

TextReader::~TextReader()
{
	OnLog = nullptr;
	OnResult = nullptr;
}


////////////////////////////////////////////////////////////////////////////////////////////////////

void TextReader::Report(const char* fmt, ...)
{
	return;
#ifdef LIB_CS
	ASSERT(OnLog != nullptr, "OnLog event is null");
#endif
	va_list arg_list;
	char str[DEBUG_OUT_BUFFER_SIZE];
	va_start(arg_list, fmt);
	vsnprintf(str, DEBUG_OUT_BUFFER_SIZE - 1, fmt, arg_list);

#ifdef LIB_CS
	OnLog(std::string(str) + "\n");
#endif
	WriteLog(str);
}

////////////////////////////////////////////////////////////////////////////////////////////////////

std::string TextReader::ReadText(std::string filePath)
{
	return GetTGMTtesseract()->ReadText(filePath);
}