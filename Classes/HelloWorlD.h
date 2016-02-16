#ifndef __HELLOWORL_D_SCENE_H__
#define __HELLOWORL_D_SCENE_H__


#include "cocos2d.h"
#include <listeneradapter.h>
#include "Gif\GifBase.h"
#include "Gif\InstantGif.h"

USING_NS_CC;
class HelloWorlD : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	CREATE_FUNC(HelloWorlD);
private:
	bool left;
	bool right;
	bool up;
	bool down;
	Sprite* player;
	Sprite* background;
	PhysicsWorld* m_world;
	unsigned char *c_data;
	bool droping;
	bool jumping;
	bool onStair;
	ccColor4B stairBlue;
	Vector<Node*> contactVector;
	Vector<Node*> eventVector;
	Vector<Node*> itemsVector;
	Vector<Node*> doorsVector;
};

#endif // __HELLOWORLD_SCENE_H__
