#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GifAnimation.h"
#include "popScence.h"
USING_NS_CC;

bool PopScene::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	auto rootNode = CSLoader::createNode("MainScene.csb");
	this->addChild(rootNode);
	return true;
}
