#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GifAnimation.h"
#include "popScence.h"
#include "HelloWorlD.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

	auto layer = HelloWorld::create();
	layer->setPhyWorld(scene->getPhysicsWorld());
	// 'layer' is an autorelease object
	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

void HelloWorld::setScene() {
	background = Sprite::create("bacground_out.jpg");
	background->setPosition(background->getContentSize() / 2);

	Image* backgroundImage = new Image();
	backgroundImage->initWithImageFile("background1_1in.png");
	c_data = backgroundImage->getData();

	m_UI_Background->addChild(background);
}

void HelloWorld::setGame() {
	//player set
	//player = Sprite::create("player.png", CCRectMake(35, 15, 240, 290));

	GifAnimationDef* def = new GifAnimationDef;
	def->loops = -1;						// 循环次数
	def->filePath = "g1.gif";				// 文件路径
	def->delayPerUnit = 1.0/60.0;			// 每帧间隔
	def->restoreOriginalFrame = false;	// 还原初始状态

	// 创建动画
	pStand = GifAnimation::getInstance()->createAnimation(*def);

	GifAnimationDef* def_ = new GifAnimationDef;
	def_->loops = -1;						// 循环次数
	def_->filePath = "g2.gif";				// 文件路径
	def_->delayPerUnit = 1.0 / 60.0;			// 每帧间隔
	def_->restoreOriginalFrame = false;	// 还原初始状态

										// 创建动画
	pWalk = GifAnimation::getInstance()->createAnimation(*def_);

	// 创建精灵播放动画
	player = Sprite::create("player.png", CCRectMake(35, 15, 240, 290));
	player->setAnchorPoint(Vec2(0.3125, 0.5));
	player->runAction(Animate::create(pStand));
	player->runAction(FlipX::create(true));
	player->setScale(0.5);
	auto a = player->getContentSize();
	Sprite* princess = Sprite::create("player.png", CCRectMake(1484, 17, 164, 281));
	//init position
	Point playerInitPosition;
	playerInitPosition.x = 732;
	playerInitPosition.y = background->getContentSize().height - 3248;
	player->setPosition(playerInitPosition);
	princess->setPosition(Point(3728, 3847 + princess->getContentSize().height / 2));

	//contactor set
	auto backgroundterm = static_cast<Sprite*>(rootNode->getChildByName("background1_1out"));
	backgroundterm->removeFromParentAndCleanup(true);
	auto Contact = rootNode->getChildByName("Contact");
	contactVector = Contact->getChildren();
	auto Event = rootNode->getChildByName("Event");
	eventVector = Event->getChildren();
	auto Door = rootNode->getChildByName("Door");
	doorsVector = Door->getChildren();

	m_UI_Game->addChild(rootNode);
	m_UI_Game->addChild(player);
	m_UI_Game->addChild(princess);
}

void HelloWorld::configPhy() {
	//init door
	for (int i = 0; i < doorsVector.size();i++) {
		Sprite *projectile = (CCSprite *)doorsVector.at(i);
		auto doorBody = PhysicsBody::createBox(projectile->getContentSize());
		doorBody->setDynamic(true);
		doorBody->setGravityEnable(false);
		projectile->setPhysicsBody(doorBody);
	}

	//physics edge init
	auto body = PhysicsBody::createEdgeBox(background->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT, 3);
	auto edgeNode = Node::create();
	body->setGravityEnable(true);
	edgeNode->setPosition(background->getContentSize() / 2);
	edgeNode->setPhysicsBody(body);
	this->addChild(edgeNode);

	//physics player init
	PhysicsMaterial material;
	auto playerBody = PhysicsBody::createBox(Size(135, player->getContentSize().height), PhysicsMaterial::PhysicsMaterial(0, 0, 0));
	playerBody->setRotationEnable(false);
	playerBody->setGravityEnable(false);
	playerBody->setPositionOffset(Vec2(-48, 0));
	player->setPhysicsBody(playerBody);

	//physics background init
	auto backgroundBody = PhysicsBody::createBox(Size(0, 0), PhysicsMaterial::PhysicsMaterial(0, 0, 0));
	backgroundBody->setGravityEnable(false);
	backgroundBody->setDynamic(false);

	//plist
	const char* testPlistPath = "museum2.plist";
	CCDictionary* plistDic = CCDictionary::createWithContentsOfFile(testPlistPath);
	CCDictionary* bodyDic = dynamic_cast<CCDictionary*>(plistDic->objectForKey("bodies"));
	CCDictionary* backgroundDic = dynamic_cast<CCDictionary*>(bodyDic->objectForKey("background1_1in"));
	CCArray* fixturesArr = dynamic_cast<CCArray*>(backgroundDic->objectForKey("fixtures"));

	for (int fixtureNum = 0;fixtureNum < fixturesArr->count();fixtureNum++) {
		CCDictionary* eachDic = dynamic_cast<CCDictionary*>(fixturesArr->getObjectAtIndex(fixtureNum));
		CCArray* polygonsArr = dynamic_cast<CCArray*>(eachDic->objectForKey("polygons"));
		for (int polygonsNum = 0; polygonsNum < polygonsArr->count(); polygonsNum++) {
			CCArray* pointArr = dynamic_cast<CCArray*>(polygonsArr->getObjectAtIndex(polygonsNum));
			int num = pointArr->count();
			Point *points = new Point[num];
			for (int pointNum = 0; pointNum < pointArr->count(); pointNum++) {
				CCString* point_string = (CCString*)pointArr->objectAtIndex(pointNum);
				Point point = PointFromString(point_string->getCString());
				points[pointNum] = point;
			}
			backgroundBody->addShape(PhysicsShapePolygon::create(points, num));
		}
	}
}

void HelloWorld::configSchedule() {
	//fix update to avoid body pass through
	scheduleOnce(CC_SCHEDULE_SELECTOR(HelloWorld::updateStart), 2);

	//playerMove schedule
	schedule(schedule_selector(HelloWorld::playerMove), 1.0 / 60, kRepeatForever, 0);
	schedule(schedule_selector(HelloWorld::conTact), 1.0 / 60, kRepeatForever, 0);
	schedule(schedule_selector(HelloWorld::canMove), 1.0 / 60, kRepeatForever, 0);
	schedule(schedule_selector(HelloWorld::changeLocation), 1.0 / 60, kRepeatForever, 0);
}

void HelloWorld::configEventListener() {
	auto keylistener = EventListenerKeyboard::create();
	keylistener->setEnabled(true);
	keylistener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	keylistener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithFixedPriority(keylistener, -100);
	stairBlue = getPixelColorByPoint(Point(7512, 3892));
}
// on "init" you need to initialize your instance
bool HelloWorld::initLayer() {
	auto origin = Director::getInstance()->getVisibleOrigin();
	m_UI_Dialog = Layer::create();
	m_UI_Dialog->setPosition(origin);
	this->addChild(m_UI_Dialog, 40);

	m_UI_Tool = Layer::create();
	m_UI_Tool->setPosition(origin);
	this->addChild(m_UI_Tool, 30);

	m_UI_Game = Layer::create();
	m_UI_Game->setPosition(origin);
	this->addChild(m_UI_Game, 20);

	m_UI_Background = Layer::create();
	m_UI_Background->setPosition(origin);
	this->addChild(m_UI_Background, 10);

	return true;
}

void HelloWorld::initDialog() {

}
bool HelloWorld::init()
{
	if (!Layer::init())
	{
		return false;
	}
	playerState = 0;
	droping = false;
	jumping = false;
	onStair = false;
	canmove = true;
	Location = true;
	rootNode = CSLoader::createNode("MainScene.csb");
	initLayer();
	setScene();
	setGame();
	configPhy();
	configSchedule();
	configEventListener();
	//background follow
	auto follow = Follow::create(player);
	this->runAction(follow);

	//event listener
	return true;
}
void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
	if (keyCode == EventKeyboard::KeyCode::KEY_A) {
		left = false;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_D) {
		right = false;
	}
	if (keyCode == EventKeyboard::KeyCode::KEY_W) {
		up = false;
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_S) {
		down = false;
	}
}
void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
	if (canmove) {
		if (keyCode == EventKeyboard::KeyCode::KEY_A) {
			left = true;
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_D) {
			right = true;
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_W) {
			auto actionMoveDone = CallFuncN::create([&](Ref* sender) {
				jumping = false;
			});
			if (!jumping&&!droping&&!onStair) {
				jumping = true;
				auto jumpBy = JumpBy::create(0.5, Vec2(0, 130), 0, 1);
				auto action = Sequence::create(jumpBy, actionMoveDone, NULL);
				player->runAction(action);
			}
			if (onStair) {
				up = true;
			}
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_S) {
			if (onStair) {
				down = true;
			}
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_J) {
			for (int i = 0; i < itemsVector.size();i++) {
				Sprite *projectile = (CCSprite *)itemsVector.at(i);
				if (player->boundingBox().intersectsRect(projectile->boundingBox())) {
					m_UI_Game->removeChildByName("hairpin");
					player->addChild(projectile);
				}
			}
		}
	}
}

void HelloWorld::updateStart(float delta)
{
	m_world->setAutoStep(false);
	scheduleUpdate();
}

void HelloWorld::canMove(float delta) {
	canmove = true;
	if (this->getChildByName("duihuakuang") != NULL) {
		canmove = false;
	}
}

void HelloWorld::conTact(float delta) {
	for (int i = 0; i < contactVector.size();i++) {
		Sprite *projectile = (CCSprite *)contactVector.at(i);
		if (player->boundingBox().intersectsRect(projectile->boundingBox())) {
			if (projectile->getName() == "Contact001") {
				if (player->getChildByName("hairpin") != NULL) {
					rootNode->getChildByName("Door")->removeChildByName("Door001");
				}
			}
		}
	}
	for (int i = 0; i < eventVector.size();i++) {
		Sprite *projectile = (CCSprite *)eventVector.at(i);
		if (player->boundingBox().intersectsRect(projectile->boundingBox())) {
			if (projectile->getName() == "Event001") {
				bool findit = false;
				for (int j = 0; j < itemsVector.size(); j++) {
					Sprite *itemile = (CCSprite *)itemsVector.at(i);
					if (itemile->getName() == "hairpin") {
						findit = true;
						break;
					}
				}
				if (!findit) {
					auto pop = PopScene::createScene();
					pop->setName("pop");
					int *a = new int;
					*a = 5;
					pop->setUserData(a);
					m_UI_Dialog->addChild(pop);

					auto pos = this->getPosition();
					Size visibleSize = Director::getInstance()->getVisibleSize();
					Vec2 origin = Director::getInstance()->getVisibleOrigin();
					Sprite* hairpin = Sprite::create("player.png", CCRectMake(2069, 926, 155, 155));
					hairpin->setName("hairpin");
					hairpin->setPosition(Vec2(2734, 3947));
					m_UI_Game->addChild(hairpin);
					itemsVector.pushBack(hairpin);
				}
			}
		}
	}
}
void HelloWorld::playerMove(float delta) {
	//drop when it is not on the floor
	if (!jumping&&!onStair) {
		drop();
	}
	playerWalk();
	fixPosition();
}
void HelloWorld::playerWalk() {
	if (!onStair) {
		if (left == true) {
			Location = false;
			if (playerState == 0) {
				player->stopAllActions();
				player->runAction(Animate::create(pWalk));
				playerState = 1;
			}
			Vec2 speed = player->getPhysicsBody()->getVelocity();
			if (speed.x >= 0) {
				speed.x = -200;
			}
			int haha = wallBesideLeft();
			if (haha == 1) {
				speed.x = 0;
			}
			player->getPhysicsBody()->setVelocity(Vec2(speed.x, speed.y));
		}
		else if (right == true) {
			Location = true;
			if (playerState == 0) {
				player->stopAllActions();
				player->runAction(Animate::create(pWalk));
				playerState = 1;
			}
			Vec2 speed = player->getPhysicsBody()->getVelocity();
			if (speed.x <= 0) {
				speed.x = 200;
			}
			int haha = wallBesideRight();
			if (haha == 1) {
				speed.x = 0;
			}
			player->getPhysicsBody()->setVelocity(Vec2(speed.x, speed.y));
		}
		if (right == left) {
			Vec2 speed = player->getPhysicsBody()->getVelocity();
			speed.x = 0;
			player->getPhysicsBody()->setVelocity(Vec2(speed.x, speed.y));
			if (playerState == 1) {
				player->stopAllActions();
				player->runAction(Animate::create(pStand));
				playerState = 0;
			}
		}
	}
	else {
		if (up == true) {
			Vec2 speed = player->getPhysicsBody()->getVelocity();
			speed.x = 0;
			speed.y = 200;
			player->getPhysicsBody()->setVelocity(Vec2(speed.x, speed.y));
		}
		if (down == true) {
			Vec2 speed = player->getPhysicsBody()->getVelocity();
			speed.x = 0;
			speed.y = -200;
			player->getPhysicsBody()->setVelocity(Vec2(speed.x, speed.y));
		}
		if (up == down) {
			player->getPhysicsBody()->setVelocity(Vec2(0, 0));
		}
	}
}
void HelloWorld::update(float dt)
{
	for (int i = 0; i < 3; ++i)
	{
		m_world->step(1 / 180.0f);
	}
}
void HelloWorld::changeLocation(float dt) {
	player->setFlippedX(Location);
}
void HelloWorld::drop() {
	Point playerPosition = player->getPosition();
	unsigned int image_front_x = player->getPosition().x;
	auto a = player->getContentSize();
	unsigned int image_front_y = background->getContentSize().height - (player->getPosition().y - player->getContentSize().height/4);
	unsigned int image_after_x = image_front_x + 40;
	unsigned int image_after_y = image_front_y;
	ccColor4B c_front = getPixelColorByPoint(Point(image_front_x, image_front_y));
	ccColor4B c_after = getPixelColorByPoint(Point(image_after_x, image_after_y));
	if (c_front.a == 0 && c_after.a == 0) {
		if (player->getPhysicsBody()->getVelocity().y == 0) {
			player->getPhysicsBody()->setVelocity(player->getPhysicsBody()->getVelocity() + Vec2(0, -300));
		}
		droping = true;
	}
	else {
		Vec2 speed = player->getPhysicsBody()->getVelocity();
		speed.y = 0;
		player->getPhysicsBody()->setVelocity(Vec2(speed.x, speed.y));
		droping = false;
	}
}
//To fix position when player is in floor or wall
void HelloWorld::fixPosition() {
	if (!onStair) {
		Point playerPosition = player->getPosition();
		unsigned int image_x = player->getPosition().x;
		unsigned int image_y = background->getContentSize().height -
			(player->getPosition().y - player->getContentSize().height / 4);
		ccColor4B leftBottom = getPixelColorByPoint(Point(image_x, image_y));
		Vec2 speed = player->getPhysicsBody()->getVelocity();
		if (leftBottom.a == 255&&leftBottom.g < 100) {
			speed.y = 200;
			player->getPhysicsBody()->setVelocity(Vec2(speed.x, speed.y));
		}
		else if (leftBottom.g < 100){
			if (speed.y > 0) {
				speed.y = 0;
				player->getPhysicsBody()->setVelocity(Vec2(speed.x, speed.y));
			}
		}
	}
	Point playerPosition = player->getPosition();
	unsigned int image_x = player->getPosition().x;
	unsigned int image_y = background->getContentSize().height -
		(player->getPosition().y - player->getContentSize().height / 4);
	ccColor4B leftBottom = getPixelColorByPoint(Point(image_x, image_y));
	leftBottom = getPixelColorByPoint(Point(image_x, image_y+20));
	if (leftBottom == stairBlue) {
		onStair = true;
	}
	else {
		leftBottom = getPixelColorByPoint(Point(image_x, image_y + 50));
		if (leftBottom == stairBlue) {
			onStair = true;
		}
		else {
			onStair = false;
		}
	}
}
int HelloWorld::wallBesideLeft() {
	Point playerPosition = player->getPosition();
	unsigned int image_x = player->getPosition().x-10;
	unsigned int image_y = background->getContentSize().height -
		(player->getPosition().y - player->getContentSize().height / 4) - 10;
	ccColor4B leftBottom = getPixelColorByPoint(Point(image_x, image_y));
	image_y -= 20;
	ccColor4B leftTop = getPixelColorByPoint(Point(image_x, image_y));
	if (leftBottom.a == 255) {
		if (leftTop.a == 255) {
			return 1;
		}
		else {
			return 2;
		}
	}
	return 3;
}

int HelloWorld::wallBesideRight() {
	Point playerPosition = player->getPosition();
	unsigned int image_x = player->getPosition().x + 10;
	unsigned int image_y = background->getContentSize().height -
		(player->getPosition().y - player->getContentSize().height / 4) - 10;
	ccColor4B leftBottom = getPixelColorByPoint(Point(image_x, image_y));
	image_y -= 20;
	ccColor4B leftTop = getPixelColorByPoint(Point(image_x, image_y));
	if (leftBottom.a == 255) {
		if (leftTop.a == 255) {
			return 1;
		}
		else {
			return 2;
		}
	}
	return 3;
}
ccColor4B HelloWorld::getPixelColorByPoint(Point pos) {
	unsigned int image_x = pos.x;
	unsigned int image_y = pos.y;
	ccColor4B c = { 0, 0, 0 ,0 };
	unsigned int *pixel = (unsigned int *)c_data;
	pixel = pixel + (image_y * (int)background->getContentSize().width) * 1 + image_x * 1;
	c.r = *pixel & 0xff;
	c.g = (*pixel >> 8) & 0xff;
	c.b = (*pixel >> 16) & 0xff;
	c.a = (*pixel >> 24) & 0xff;
	return c;
}

//move finish
