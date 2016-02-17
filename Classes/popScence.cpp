#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GifAnimation.h"
#include "popScence.h"
USING_NS_CC;
Scene * PopScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	auto layer = PopScene::create();
	// 'layer' is an autorelease object
	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}


bool PopScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		auto background = Sprite::create("duihuakuang.png");
		auto a = background->getContentSize();
		m_bgSprite = background;
		auto winposition = getPosition();
		background->setPosition(ccp(0,0));
		addChild(background,3);
		//获得背景图片的大小
		CCSize contentSize = background->getContentSize();
		m_size = contentSize;

		keylistener_ = EventListenerKeyboard::create();
		keylistener_->setEnabled(true);
		keylistener_->onKeyPressed = CC_CALLBACK_2(PopScene::onKeyPressed, this);
		_eventDispatcher->addEventListenerWithFixedPriority(keylistener_, -200);
		CCDirector* pDirector = CCDirector::sharedDirector();
		//设置题目和文本内容
	return true;
}

//点击菜单按钮的时候调用的事件处理函数

//设置这个层的题目

//设置层的内容
void PopScene::setContent()
{
	CCLabelTTF * content = CCLabelTTF::create("hello! everyone,welcome to www.jb51.net",
		"", 24);
	content->setPosition(ccp(m_size.width / 2, m_size.height / 2));
	//设置ttf的文本域
	content->setDimensions(CCSize(this->m_size.width - 60, this->m_size.height - 100));
	//设置ttf的水平对齐方式
	content->setHorizontalAlignment(kCCTextAlignmentLeft);

	m_bgSprite->addChild(content);
}

void PopScene::onKeyPressed(EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
	int* a = (int*)this->getParent()->getUserData();
	int b = *a;
	keylistener_->setEnabled(false);
	Layer::onExit();
	this->getParent()->removeFromParentAndCleanup(true);
}