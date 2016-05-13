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
	ObjectMy(string ObjectNmae, int ObjectrNumber, bool back, bool damage, int time = 1);
	string getObjectName();
	int getObjectNumber();
	Animation* objectplay();
	void changeObjectAction(int i, bool back, int time);
	bool isDamage();
	void pushActionVector(int i, bool back, int time);
	int getState();
	void setState(int i);
	Animation* getActionbyindex(int i);
	void preloadVoice();
	void playVoice();
private:
	string Name;
	bool damage;
	int Number;
	Animation* actionplay;
	Vector<Animation*> actionVector;
	int state;
};
#endif