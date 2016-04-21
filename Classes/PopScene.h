/*对话框场景类的头文件*/
#ifndef _POP_SCENE_H_
#define _POP_SCENE_H_
#include "cocos2d.h"

using namespace cocos2d;

class PopScene : public CCLayer
{
public:
	static PopScene* create(const std::string backgroundImage, const std::string context, const double scale);
	bool init();
	CREATE_FUNC(PopScene);
	void setPosition(CCPoint point);
	CCPoint getPosition();
	void del();
private:
	//注册触摸事件，实现ccTouchBegan()方法
	//void registerWithTouchDispatcher();
	//bool ccTouchBegan(CCTouch * touch, CCEvent * pevent);
	//在弹出的对话框上加俩个按钮，以下的函数是对应的按钮的处理事件
	//设置对话框的title
	void setBackground();
	//设置对话框的文本内容
	void setContent();

	//void touchevent();
	//m_size代表的是对话框背景的大小
	CCSize m_size;
	//对话框的背景精灵
	CCSprite * m_bgSprite;

	std::string backgroundname;
	std::string context;
	double scale;
	
};
#endif