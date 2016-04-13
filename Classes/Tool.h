#ifndef __TOOL_H__
#define __TOOL_H__

#include "cocos2d.h"
#include "Gif\GifBase.h"
#include "Gif\InstantGif.h"
#include "GifAnimation.h"
#include <string>
USING_NS_CC;
using namespace std;
class Tool {
public:
	Tool(int toolNum, string toolName);
	string getToolName();
	int getToolNum();
private:
	string toolName;
	int toolNum;
};
#pragma once
#endif