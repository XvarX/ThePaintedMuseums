#include "PopScene.h"
#include <iostream>

PopScene* PopScene::create(const std::string backgroundImage, const std::string context, const double scale)
{
	PopScene* layer = PopScene::create();
	layer->backgroundname = backgroundImage;
	layer->context = context;
	layer->scale = scale;
	layer->setBackground();
	layer->setContent();
	//layer->touchevent();
	return layer;
}

bool PopScene::init()
{
	bool bRet = false;
	do
	{
		CC_BREAK_IF(!CCLayer::init());
		bRet = true;
	} while (0);

	return bRet;
}



//void PopScene::touchevent() {
//	auto listener = EventListenerTouchOneByOne::create();
//	listener->onTouchBegan = [&](Touch* touch, Event* event){
//		Vec2 touch_pos = touch->getLocation(),
//			m_obj0_pos = m_bgSprite->getPosition(),
//			m_obj0_size = m_bgSprite->getContentSize();
//
//		if (touch_pos.x > m_obj0_pos.x - m_obj0_size.x / 2 && touch_pos.x < m_obj0_pos.x + m_obj0_size.x / 2 &&
//			touch_pos.y > m_obj0_pos.y - m_obj0_size.y / 2 && touch_pos.y < m_obj0_pos.y + m_obj0_size.y / 2) {
//			
//			
//			del();
//
//		}
//
//		return true;
//	};
//	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
//}

void PopScene::setBackground() {
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	//���������ı���ͼƬ������������λ��Ϊ������Ļ���е�
	CCSprite* background = CCSprite::create(backgroundname);
	m_bgSprite = background;
	background->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	background->setScale(scale);
	this->addChild(background);

	//��ñ���ͼƬ�Ĵ�С
	CCSize contentSize = background->getContentSize();
	m_size = contentSize;
}

void PopScene::setPosition(CCPoint point) {
	m_bgSprite->setPosition(point);
}

CCPoint PopScene::getPosition() {
	return m_bgSprite->getPosition();
}

void PopScene::del() {
	this->removeFromParentAndCleanup(true);
}
//�������²�


extern int GBKToUTF8(std::string &gbkStr, const char* toCode, const char* formCode);
//���ò������
void PopScene::setContent()
{
	GBKToUTF8(context, "gb2312", "utf-8");
	Label * content = Label::createWithTTF(context,"ttf//miniblack.TTF", 50);
	Color3B color;
	color.r = 120;
	color.g = 58;
	color.b = 17;
	content->setColor(color);

	if (backgroundname == "UI//A.png" || backgroundname == "UI//D.png") {
		content->setPosition(ccp(m_size.width * 0.58, m_size.height * 0.20));
	}
	else if (backgroundname == "UI//B.png" || backgroundname == "UI//C.png") {
		content->setPosition(ccp(m_size.width * 0.4, m_size.height * 0.20));
	}
	//content->setPosition(ccp(m_size.width * 0.5, m_size.height * 0.23));
	//����ttf���ı���
	content->setDimensions(this->m_size.width * 0.7, this->m_size.height / 3);
	//����ttf��ˮƽ���뷽ʽ
	content->setHorizontalAlignment(kCCTextAlignmentLeft);
	
	m_bgSprite->addChild(content);
	//m_bgSprite->setPosition(m_bgSprite->getPositionX(), m_bgSprite->getPositionX() + 50);

	//this->addChild(content);
}