#include "TextLocator.h"
#include "TGMTcolor.h"
#include "TGMTConfig.h"
#include "TGMTdebugger.h"
#include "TGMTutil.h"
#include "TGMTcontour.h"
#include "TGMTdraw.h"
#include "TGMTblob.h"
#include "TGMTimage.h"
#include "TGMTbrightness.h"
#include "TGMTmorphology.h"
#include "TGMTfile.h"

TextLocator* TextLocator::instance = NULL;

////////////////////////////////////////////////////////////////////////////////////////////////////

TextLocator::TextLocator()
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

bool TextLocator::LoadConfig()
{
	if (!GetTGMTConfig()->LoadSettingFromFile("config.ini"))
	{
		PrintError("Can not read config.ini ");
		return false;
	}


	m_debug = GetTGMTConfig()->ReadValueBool(INI_TextLocator_SECTION, "debug");

	Report("Load config complete");

	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

TextLocator::~TextLocator()
{
	OnLog = nullptr;
	OnResult = nullptr;
}


////////////////////////////////////////////////////////////////////////////////////////////////////

void TextLocator::Report(const char* fmt, ...)
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

std::string TextLocator::ReadText(std::string filePath)
{
	return "";
}