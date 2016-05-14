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
	void resources();	//需要加载资源都放到这个函数里了
	void loadCallBack(cocos2d::CCObject* object);//异步加载完成后回调主程序的函数
private:
	int count;//加载计数
	int total;//总资源个数
};