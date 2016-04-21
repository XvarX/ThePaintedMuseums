#include "F:\cocosfile\ThePaintedMuseums\cocos2d\external\win32-specific\icon\include\iconv.h" 
#include <iostream>
#pragma comment(lib,"libiconv.lib")

int GBKToUTF8(std::string &gbkStr, const char* toCode, const char* formCode)

{

	iconv_t iconvH;  iconvH = iconv_open(formCode, toCode);

	if (iconvH == 0)

	{

		return -1;

	}

	const char* strChar = gbkStr.c_str();

	const char** pin = &strChar;

	size_t strLength = gbkStr.length();

	char* outbuf = (char*)malloc(strLength * 4);

	char* pBuff = outbuf;

	memset(outbuf, 0, strLength * 4);

	size_t outLength = strLength * 4;

	if (-1 == iconv(iconvH, pin, &strLength, &outbuf, &outLength))

	{

		iconv_close(iconvH);

		return -1;

	}

	gbkStr = pBuff;

	iconv_close(iconvH);

	return 0;

}