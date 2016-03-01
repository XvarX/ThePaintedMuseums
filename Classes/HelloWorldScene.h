#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__


#include "cocos2d.h"
#include <listeneradapter.h>
#include "Gif\GifBase.h"
#include "Gif\InstantGif.h"
#include <string>

USING_NS_CC;
using namespace std;
class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
	void update(float dt) override;
	void setScene();
	void setGame();
	void configPhy();
	void configSchedule();
	void configEventListener();
	bool initLayer();
	void initDialog();
	void initAnimate();
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void setPhyWorld(PhysicsWorld* world) { m_world = world; }
	void drop();
	void playerWalk();
	void updateStart(float delta);
	int wallBesideLeft();
	void playerMove(float delta);
	void conTact(float delta);
	void playerAction();
	void canMove(float delta);
	void changeLocation(float delta);
	void addNewItem(string itemName, Point ItemPos, int a, int b, int c, int d);
	void fixPosition();
	void showTalk();
	void setPlayerPositionByZone(Sprite* player, Node* zone);
	int wallBesideRight();
	ccColor4B getPixelColorByPoint(Point pos);
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
private:
	bool left;
	bool right;
	bool up;
	bool down;
	Node* rootNode;
	Sprite* player;
	Sprite* background;
	PhysicsWorld* m_world;
	unsigned char *c_data;
	bool droping;
	bool jumping;
	bool canmove;
	bool onStair;
	bool standBy;
	bool Location;
	int playerState;
	double dropspeed;
	Animation* pStand;
	Animation* pWalk;
	Animation* ptemp;
	Animation *princessStand;
	Animation *princessTemp;
	ccColor4B stairBlue;
	Vector<Node*> contactVector;
	Vector<Node*> eventVector;
	Vector<Node*> itemsVectorInMap;
	Vector<Node*> itemsVectorInPlayer;
	Vector<Node*> doorsVector;
	Vector<Node*> stairsVector;
	Vector<Node*> objectsVector;
	Vector<Node*> StandBysVector;

	Layer* m_UI_Dialog;			//�Ի���� ��߲�
	Layer* m_UI_Tool;			//�������� �θ߲�
	Layer* m_UI_Game;			//��Ϸ�� �Ͳ�
	Layer* m_UI_Background;		//������ �ײ�
};

#endif // __HELLOWORLD_SCENE_H__
