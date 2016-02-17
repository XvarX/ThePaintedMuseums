#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__


#include "cocos2d.h"
#include <listeneradapter.h>
#include "Gif\GifBase.h"
#include "Gif\InstantGif.h"

USING_NS_CC;
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
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void setPhyWorld(PhysicsWorld* world) { m_world = world; }
	void drop();
	void playerWalk();
	void updateStart(float delta);
	int wallBesideLeft();
	void playerMove(float delta);
	void conTact(float delta);
	void canMove(float delta);
	void changeLocation(float delta);
	void fixPosition();
	void showTalk();
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
	bool Location;
	int playerState;

	Animation* pStand;
	Animation* pWalk;
	ccColor4B stairBlue;
	Vector<Node*> contactVector;
	Vector<Node*> eventVector;
	Vector<Node*> itemsVector;
	Vector<Node*> doorsVector;

	Layer* m_UI_Dialog;			//¶Ô»°¿ò²ã ×î¸ß²ã
	Layer* m_UI_Tool;			//¹¤¾ßÀ¸²ã ´Î¸ß²ã
	Layer* m_UI_Game;			//ÓÎÏ·²ã µÍ²ã
	Layer* m_UI_Background;		//±³¾°²ã µ×²ã
};

#endif // __HELLOWORLD_SCENE_H__
