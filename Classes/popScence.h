#ifndef _POP_SCENE_H_
#define _POP_SCENE_H_
#include "cocos2d.h"

using namespace cocos2d;

class PopScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	bool init();
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	CREATE_FUNC(PopScene);
	void setContent();
private:
	//m_size代表的是对话框背景的大小
	CCSize m_size;
	EventListenerKeyboard* keylistener_;
	//对话框的背景精灵
	CCSprite * m_bgSprite;
};
#endif