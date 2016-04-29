/*�Ի��򳡾����ͷ�ļ�*/
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
	//ע�ᴥ���¼���ʵ��ccTouchBegan()����
	//void registerWithTouchDispatcher();
	//bool ccTouchBegan(CCTouch * touch, CCEvent * pevent);
	//�ڵ����ĶԻ����ϼ�������ť�����µĺ����Ƕ�Ӧ�İ�ť�Ĵ����¼�
	//���öԻ����title
	void setBackground();
	//���öԻ�����ı�����
	void setContent();

	//void touchevent();
	//m_size�������ǶԻ��򱳾��Ĵ�С
	CCSize m_size;
	//�Ի���ı�������
	CCSprite * m_bgSprite;

	std::string backgroundname;
	std::string context;
	double scale;
	
};
#endif