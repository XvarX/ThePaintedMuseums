#ifndef __OBB_H__
#define __OBB_H__

#include "cocos2d.h"
#include "Gif\GifBase.h"
#include "Gif\InstantGif.h"
#include "GifAnimation.h"
#include <string>
USING_NS_CC;
using namespace std;
class ObjectMy {
public:
	ObjectMy();
	ObjectMy(string ObjectNmae, int ObjectrNumber,bool back);
	string getObjectName();
	int getObjectNumber();
	Animation* objectplay();
private:
	string Name;
	int Number;
	Animation* actionplay;
};
#endif