#include "cocos2d.h"
USING_NS_CC;
using namespace std;
class LoadingScene : public cocos2d::CCLayer
{
public:
	static cocos2d::Scene* createScene();
	bool init();
	LoadingScene();
	~LoadingScene();
	void resources();	//��Ҫ������Դ���ŵ������������
	void loadCallBack(cocos2d::CCObject* object);//�첽������ɺ�ص�������ĺ���
private:
	int count;//���ؼ���
	int total;//����Դ����
};