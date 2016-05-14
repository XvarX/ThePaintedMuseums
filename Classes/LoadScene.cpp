#include "LoadScene.h"
#include "HelloWorldScene.h"

Scene* LoadingScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	auto layer = LoadingScene::create();
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool LoadingScene::init()
{
	count = 0;
	total = 3;

	this->resources();
	return true;
}
void LoadingScene::resources()
{
	CCTextureCache::sharedTextureCache()->addImageAsync("frontGround1//front(always).png", callfuncO_selector(LoadingScene::loadCallBack)); // 欢迎界面 背景图片
	CCTextureCache::sharedTextureCache()->addImageAsync("frontGround2//front(stage).png" , callfuncO_selector(LoadingScene::loadCallBack)); // 添加关于开发者背景图片
	CCTextureCache::sharedTextureCache()->addImageAsync("background5-14.png", callfuncO_selector(LoadingScene::loadCallBack)); // 添加关于开发者背景图片
	CCTextureCache::sharedTextureCache()->addImageAsync("background1_1_1in.png", callfuncO_selector(LoadingScene::loadCallBack)); // 添加关于开发者背景图片
}


void LoadingScene::loadCallBack(CCObject* object)
{
	count++;

	if (count == total)
	{
		//加载完成就切换场景
		CCScene* hello = HelloWorld::createScene();
		CCTransitionMoveInL* effect = CCTransitionMoveInL::create(2.0f, hello);
		CCDirector::sharedDirector()->replaceScene(effect);
	}
}