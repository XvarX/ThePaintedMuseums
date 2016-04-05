#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GifAnimation.h"
#include "popScence.h"
#include "ObjectMy.h"
#include "math\CCMath.h"
#include "Construct.h"
#include <math.h>
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
	background = Sprite::create("background03-20.jpg");
	background->setPosition(background->getContentSize() / 2);

	Image* backgroundImage = new Image();
	backgroundImage->initWithImageFile("background1_1_1in.png");
	c_data = backgroundImage->getData();

	m_UI_Background->addChild(background);
}

void HelloWorld::setGame() {
	//player set
	//player = Sprite::create("player.png", CCRectMake(35, 15, 240, 290));

	// 创建精灵播放动画
	player = Sprite::create("player1.png");
	player->setAnchorPoint(Vec2(0.514, 0.5));
	Animate* aStand = Animate::create(pStand);
	aStand->setTag(0);
	player->runAction(aStand);
	player->runAction(FlipX::create(true));
	//player->setScale(0.5);
	auto a = player->getContentSize();
	princess = Sprite::create("princess.png");
	princess->setName("princess");
	//contactor set
	auto backgroundterm = static_cast<Sprite*>(rootNode->getChildByName("background1_1out"));
	backgroundterm->removeFromParentAndCleanup(true);
	auto Contact = rootNode->getChildByName("Contact");
	contactVector = Contact->getChildren();
	auto Event = rootNode->getChildByName("Event");
	eventVector = Event->getChildren();
	for (int i = 0; i < eventVector.size(); i++) {
		Sprite *projectile = (CCSprite *)eventVector.at(i);
		Construct *newObject = new Construct(projectile->getName(), i);
		projectile->setUserData(newObject);
	}
	auto Door = rootNode->getChildByName("Door");
	doorsVector = Door->getChildren();
	auto Object = rootNode->getChildByName("Object");
	objectsVector = Object->getChildren();
	auto uselessObject = rootNode->getChildByName("UselessObject");
	uselessObjectsVector = uselessObject->getChildren();
	auto Stair = rootNode->getChildByName("Stair");
	
	stairsVector = Stair->getChildren();
	for (int i = 0; i < objectsVector.size(); i++) {
		Sprite *projectile = (CCSprite *)objectsVector.at(i);
		Construct *newObject = new Construct(projectile->getName(), i);
		projectile->setUserData(newObject);	
	}

	for (int i = 0; i < uselessObjectsVector.size(); i++) {
		Sprite *projectile = (CCSprite *)uselessObjectsVector.at(i);
		ObjectMy *newObject;
		if (projectile->getName() == "Object013") {
			newObject = new ObjectMy(projectile->getName(), i, false);
		}
		else {
			newObject = new ObjectMy(projectile->getName(), i, true);
		}
		projectile->setUserData(newObject);
	}

	for (int i = 0; i < stairsVector.size(); i++) {
		Sprite *projectile = (CCSprite *)stairsVector.at(i);
		Construct *newObject = new Construct(projectile->getName(), i);
		if (projectile->getName() == "Stair02") {
			newObject->setState(-1);
		}
		projectile->setUserData(newObject);
	}
	auto StandBy = rootNode->getChildByName("StandBy");
	StandBysVector = StandBy->getChildren();

	auto Xiepo = rootNode->getChildByName("Xiepo");
	XieposVector = Xiepo->getChildren();

	//init position
	auto zone001 = rootNode->getChildByName("Zone")->getChildByName("Zone001");
	auto zone002 = rootNode->getChildByName("Zone")->getChildByName("Zone002");
	setPlayerPositionByZone(player, zone001);
	setPlayerPositionByZone(princess, zone002);
	camera = Sprite::create("camera.jpg");
	camera->setPosition(player->getPosition() + Vec2(384, 216));
	player->setPosition(Vec2(4800, 3200));
	m_UI_Game->addChild(rootNode);
	m_UI_Game->addChild(player);
	m_UI_Game->addChild(princess);
	m_UI_Game->addChild(camera);
}

void HelloWorld::configPhy() {
	//init door
	for (int i = 0; i < doorsVector.size();i++) {
		Sprite *projectile = (CCSprite *)doorsVector.at(i);
		projectile->setVisible(false);
		auto doorBody = PhysicsBody::createBox(projectile->getContentSize());
		doorBody->setDynamic(true);
		doorBody->setGravityEnable(false);
		doorBody->setRotationEnable(false);
		doorBody->setDynamic(false);
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
	auto playerBody = PhysicsBody::createBox(Size(26,313));
	
	playerBody->setRotationEnable(false);
	playerBody->setGravityEnable(false);
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
	auto cameraBody = PhysicsBody::create();
	cameraBody->setGravityEnable(false);
	camera->setPhysicsBody(cameraBody);
}

void HelloWorld::configSchedule() {
	//fix update to avoid body pass through
	scheduleOnce(CC_SCHEDULE_SELECTOR(HelloWorld::updateStart), 2);

	//playerMove schedule
	schedule(schedule_selector(HelloWorld::playerMove), 1.0 / 60, kRepeatForever, 0);
	schedule(schedule_selector(HelloWorld::changeLocation), 1.0 / 120, kRepeatForever, 0);
	
	schedule(schedule_selector(HelloWorld::conTact), 1.0 / 60, kRepeatForever, 0);
	schedule(schedule_selector(HelloWorld::canMove), 1.0 / 60, kRepeatForever, 0);
	schedule(schedule_selector(HelloWorld::cameraMove), 1.0 / 60, kRepeatForever, 0);
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
	rotation = 0;
	playerState = 0;
	dropspeed = 0;
	droping = false;
	kailouti = false;
	cameramove = false;
	jumping = false;
	onStair = false;
	standBy = false;
	onxiepo = false;
	canmove = true;
	Location = false;
	playingAction = false;
	rootNode = CSLoader::createNode("MainScene.csb");
	initLayer();
	initAnimate();
	setScene();
	setGame();
	configPhy();
	configSchedule();
	configEventListener();

	//background follow
	auto follow = Follow::create(camera);
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
		if (keyCode == EventKeyboard::KeyCode::KEY_A) {
			left = true;
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_D) {
			right = true;
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_W) {
			if (canmove) {
				auto actionMoveDone = CallFuncN::create([&](Ref* sender) {
					jumping = false;
					stopAnimate();
				});
				if (!jumping&&!droping&&(!onStair||standBy)) {
					jumping = true;
					auto jumpBy = JumpBy::create(0.5, Vec2(0, 200), 0, 1);
					auto jumpbb = JumpBy::create(0.5, Vec2(0, 200), 0, 1);
					auto action = Sequence::create(jumpBy, actionMoveDone, NULL);
					player->runAction(action);
					//camera->runAction(jumpbb);
					Animate* ajump = Animate::create(pjump);
					stopAnimate();
					ajump->setTag(5);
					player->runAction(ajump);
					playerState = 5;
				}
				if (onStair) {
					up = true;
				}
			}
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_S) {
			if (onStair||standBy) {                                             
				down = true;
			}
		}
		if (keyCode == EventKeyboard::KeyCode::KEY_J) {
			for (int i = 0; i < itemsVectorInMap.size();i++) {
				Sprite *projectile = (CCSprite *)itemsVectorInMap.at(i);
				if (player->boundingBox().intersectsRect(projectile->boundingBox())) {
						if (itemsVectorInPlayer.find(projectile) == itemsVectorInPlayer.end()) {
							m_UI_Game->removeChild(projectile);
							player->addChild(projectile);
							itemsVectorInPlayer.pushBack(projectile);
							showItem(projectile->getName());
							playerAction(pget, 18);
						}
				}
			}
			
			for (int i = 0; i < objectsVector.size(); i++) {
				Sprite *projectile = (CCSprite *)objectsVector.at(i);
				if (player->boundingBox().intersectsRect(projectile->boundingBox())) {
					if (projectile->getName() == "Object001") {
						if (player->getChildByName("hairpin") != NULL) {
							auto object = (Construct*)projectile->getUserData();
							if (object->getState() != -1) {
								object->setState(-1);
								rootNode->getChildByName("Door")->removeChildByName("Door001");
								auto posZone4 = rootNode->getChildByName("Zone")->getChildByName("Zone004");
								auto princess = (Sprite*)m_UI_Game->getChildByName("princess");

								princess->runAction(MoveTo::create(5.0, Point(posZone4->getPosition().x, princess->getPosition().y)));

								playerAction(popenWindow, 9);
							}
						}
						else {
							auto object = (Construct*)projectile->getUserData();
							if (object->getState() != -1) {
								playerAction(pnoidea, 8);
							}
						}
					}
					if (projectile->getName() == "Object008") {
						auto object = (Construct*)projectile->getUserData();
						if (object->getState() != -1) {
							object->setState(-1);
							//addNewItem("umbrella", Point(4640, 1801), 2291, 926, 155, 155);
							playerAction(psearch, 17, "umbrella");
						}
					}
					if (projectile->getName() == "Object009") {
						auto object = (Construct*)projectile->getUserData();
						if (object->getState() != -1) {
							object->setState(-1);
							int y = 2454 - projectile->getContentSize().height / 2 + 155 / 2;
							//addNewItem("bucket", Point(5250, y), 2520, 926, 155, 155);
							playerAction(psearch, 17, "bucket");
						}
					}
					if (projectile->getName() == "Object012") {
						auto object = (Construct*)projectile->getUserData();
						if (object->getState() != -1) {
							if (player->getChildByName("umbrella") != NULL) {
								object->setState(-1);
								//play
								Sprite *stair02 = (CCSprite *)rootNode->getChildByName("Stair")->getChildByName("Stair02");
								auto eventobject = (Construct*)stair02->getUserData();
								eventobject->setState(0);
								kailouti = true;
								playerAction(patticopen, 10);
							}
							else {
								playerAction(pnoidea, 8);
							}
						}
					}
					if (projectile->getName() == "Object013") {
						auto object = (Construct*)projectile->getUserData();
						if (object->getState() != -1) {
							object->setState(-1);
							int y = 2454 - projectile->getContentSize().height / 2 + 155 / 2;
							//addNewItem("oilbucket", Point(6680, 5158), 2071, 1127, 155, 155);
							playerAction(psearch, 17, "oilbucket");
							projectile->setVisible(false);
							
						}
					}
					if (projectile->getName() == "Object015") {
						auto object = (Construct*)projectile->getUserData();
						if (object->getState() != -1) {
							if (player->getChildByName("bucket") != NULL) {
								object->setState(-1);
								rootNode->getChildByName("Door")->removeChildByName("Door002");
								playerAction(poutfire,11);
							}
							else {
								playerAction(pnoidea, 8);
							}
						}
					}
					if (projectile->getName() == "Object018") {
						auto object = (Construct*)projectile->getUserData();
						if (object->getState() != -1) {
							object->setState(-1);
							//addNewItem("roomKey", projectile->getPosition(), 2290, 1127, 155, 155);
							playerAction(psearch, 17, "roomKey");
						}
					}
					if (projectile->getName() == "Object020") {
						auto object = (Construct*)projectile->getUserData();
						if (object->getState() != -1) {
							if (player->getChildByName("roomKey") != NULL) {
								object->setState(-1);
								//play
								rootNode->getChildByName("Door")->removeChildByName("Door004");
								dad = Sprite::create("dad.png");
								dad->setName("dad");
								auto zone006 = rootNode->getChildByName("Zone")->getChildByName("Zone006");
								m_UI_Game->addChild(dad);
								setPlayerPositionByZone(dad, zone006);
								actorPlayAction(dad, dadstand, 1);
								playerAction(pdooropen, 12);
							}
							else {
								playerAction(pnoidea, 8);
							}
						} 
					}
					if (projectile->getName() == "Object022") {
						auto object = (Construct*)projectile->getUserData();
						if (object->getState() != -1) {
							object->setState(-1);
							//addNewItem("match", projectile->getPosition(), 2520, 1127, 155, 155);
							playerAction(psearch, 17, "match");
						}
					}
					if (projectile->getName() == "Object025") {
						auto object = (Construct*)projectile->getUserData();
						if (object->getState() != -1) {
							if (object->getState() == 0) {
								if (player->getChildByName("oilbucket") != NULL) {
									object->setState(1);
									//play
									playerAction(poilthrow,13);
								}
								else {
									playerAction(pnoidea, 8);
								}
							}
							else if (object->getState() == 1) {
								if (player->getChildByName("match") != NULL) {
									Sprite *event008 = (CCSprite *)rootNode->getChildByName("Event")->getChildByName("Event008");
									auto eventobject = (Construct*)event008->getUserData();
									eventobject->setState(1);
									object->setState(-1);
									//play
									auto posZone7 = rootNode->getChildByName("Zone")->getChildByName("Zone007");

									dad->stopAllActions();
									Animate* dadAction1 = Animate::create(dadstanby);
									Animate* dadAction2 = Animate::create(dadrun);
									dad->setFlippedX(true);
									dad->runAction(Sequence::create(dadAction1, dadAction2,NULL));
									auto move = MoveTo::create(5.0, Point(posZone7->getPosition().x, dad->getPosition().y));
									auto moveDone = CallFuncN::create([&](Ref* sender) {
										actorPlayAction(dad, dadoutfire, 5);
									});
									auto dadaction = Sequence::create(move, moveDone, NULL);
									dad->runAction(dadaction);
									playerAction(pfire, 14);
								}
								else {
									playerAction(pnoidea, 8);
								}
							}
						}
					}
					if (projectile->getName() == "Object026") {
						auto object = (Construct*)projectile->getUserData();
						if (object->getState() != -1) {
							object->setState(-1);
							rootNode->getChildByName("Door")->removeChildByName("Door006");
							Sprite *event010 = (CCSprite *)rootNode->getChildByName("Event")->getChildByName("Event010");
							auto eventobject = (Construct*)event010->getUserData();
							eventobject->setState(1);
							playerAction(pturn, 15);
						}
					}
				}
			}

			for (int i = 0; i < uselessObjectsVector.size(); i++) {
				Sprite *projectile = (CCSprite *)uselessObjectsVector.at(i);
				if (player->boundingBox().intersectsRect(projectile->boundingBox())) {
						auto object = (ObjectMy*)projectile->getUserData();
						projectile->stopAllActions();
						auto a = object->objectplay();
						auto action = Animate::create(a);
						projectile->runAction(action);
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
}

void HelloWorld::conTact(float delta) {
	for (int i = 0; i < eventVector.size();i++) {
		Sprite *projectile = (CCSprite *)eventVector.at(i);
		if (player->boundingBox().intersectsRect(projectile->boundingBox())) {
			if (projectile->getName() == "Event001") {
				auto object = (Construct*)projectile->getUserData();
				if (object->getState() == 0) {
					object->setState(-1);
					canmove = false;
					princesscomming();
				}
			}

			if (projectile->getName() == "Event005") {
				rootNode->getChildByName("Door")->removeChildByName("Door003");
			}

			if (projectile->getName() == "Event008") {
				auto object = (Construct*)projectile->getUserData();
				if (object->getState() == 1) {
					object->setState(-1);
					rootNode->getChildByName("Object")->removeChildByName("Object011");
					Sprite* mom = Sprite::create("mom.png");
					mom->setName("mom");
					auto zone009 = rootNode->getChildByName("Zone")->getChildByName("Zone009");
					m_UI_Game->addChild(mom);
					setPlayerPositionByZone(mom, zone009);
				}
			}
			if (projectile->getName() == "Event010") {
				auto object = (Construct*)projectile->getUserData();
				if (object->getState() == 1) {
					object->setState(-1);
					auto zone011 = rootNode->getChildByName("Zone")->getChildByName("Zone011");
					auto princess = (Sprite*)m_UI_Game->getChildByName("princess");
					setPlayerPositionByZone(princess, zone011);
				}
			}
		}
	}
	onStair = false;
	for (int i = 0; i < stairsVector.size(); i++) {
		Sprite *projectile = (CCSprite *)stairsVector.at(i);
		if (player->boundingBox().intersectsRect(projectile->boundingBox())) {
			auto object = (Construct*)projectile->getUserData();
			if (object->getState() == 0) {
				if (abs(player->getPosition().x - projectile->getPosition().x) < 30) {
					onStair = true;
				}
			}
		}
	}
	bool tempstandBy = standBy;
	standBy = false;
	for (int i = 0; i < StandBysVector.size(); i++) {
		Sprite *projectile = (CCSprite *)StandBysVector.at(i);
		if (player->boundingBox().intersectsRect(projectile->boundingBox())) {
			if (abs(player->getPosition().x - projectile->getPosition().x) < 30) {
				standBy = true;
				droping = false;
			}
		}
	}
	if (tempstandBy == true && standBy == false) {
		playerState = -1;
	}
	onxiepo = false;
	rotation = 0;
	for (int i = 0; i < XieposVector.size(); i++) {
		Sprite *projectile = (CCSprite *)XieposVector.at(i);
		if (player->boundingBox().intersectsRect(projectile->boundingBox())) {
			auto distancex = abs(player->getPosition().x - projectile->getPosition().x);
			auto xiepohalflength = projectile->getContentSize().width*projectile->getScaleX() / 2 * cos(CC_DEGREES_TO_RADIANS(projectile->getRotation()));
			auto xiepoheightbegin = projectile->getPosition().y - abs(projectile->getContentSize().width*projectile->getScaleX() / 2 * sin(CC_DEGREES_TO_RADIANS(projectile->getRotation())));
			if (distancex < xiepohalflength){
				auto sign = projectile->getRotation() > 0 ? 1 : -1;
				auto xiepoX = projectile->getPosition().x + sign*xiepohalflength;
				auto temp_x = xiepoX- player->getPosition().x;
				auto temp_y = temp_x*tan(CC_DEGREES_TO_RADIANS(projectile->getRotation()));
				
				auto fix_y = temp_y + xiepoheightbegin;
				auto footposition = player->getPosition().y - player->getContentSize().height / 2;
				if (abs(player->getPosition().y - player->getContentSize().height / 2 - fix_y) < 120) {
					onxiepo = true;
					rotation = projectile->getRotation();
				}
			}
		}
	}
}
void HelloWorld::playerMove(float delta) {
	//drop when it is not on the floor
	if (!jumping&&!onStair&&!standBy&&!kailouti) {
		drop();
	}
	playerWalk();
	if (!standBy) {
		fixPosition();
	}
}

void HelloWorld::cameraMove(float delta) {
	auto a = player->getPosition()+Vec2(384.0,216.0)+(!Location)*Vec2(-768, 0);
	auto camearPos = camera->getPosition();
	if (!cameramove) {
		camera->setPosition(a);
	}
}
void HelloWorld::playerWalk() {
	if (left == true&&canmove) {
		Location = false;
		if ((playerState == 0 || playerState == -1 || playerState == 3 ||playerState == 4)&&!onxiepo) {
			stopAnimate();
			Animate* aWalk = Animate::create(pWalk);
			aWalk->setTag(1);
			player->runAction(aWalk);
			playerState = 1;
		}
		if (onxiepo) {
			if (playerState == 0 || playerState == -1 || playerState == 1||playerState == 3|| playerState == 4) {
				if (rotation > 0&&playerState != 4) {
					stopAnimate();
					Animate* aupStair = Animate::create(pupStair);
					aupStair->setTag(4);
					player->runAction(aupStair);
					playerState = 4;
				}
				else if (rotation< 0&&playerState != 3){
					stopAnimate();
					Animate* adownStair = Animate::create(pdownStair);
					adownStair->setTag(3);
					player->runAction(adownStair);
					playerState = 3; 
				}
			}
		}
		Vec2 speed = player->getPhysicsBody()->getVelocity();
		if (speed.x >= 0) {
			speed.x = -200*1.3;

		}
		int haha = wallBesideLeft();
		if (haha == 1) {
			speed.x = 0;
		}

		player->getPhysicsBody()->setVelocity(Vec2(speed.x, speed.y));
		//camera->getPhysicsBody()->setVelocity(Vec2(speed.x, speed.y));
	}
	else if (right == true&&canmove) {
		Location = true;
		if ((playerState == 0 || playerState == -1 || playerState == 4 || playerState == 3) && !onxiepo) {
			stopAnimate();
			Animate* aWalk = Animate::create(pWalk);
			aWalk->setTag(1);
			player->runAction(aWalk);
			playerState = 1;
		}
		if (onxiepo) {
			if (playerState == 0 || playerState == -1 || playerState == 1|| playerState == 4||playerState == 3) {
				if (rotation > 0 && playerState != 3) {
					stopAnimate();
					Animate* adownStair = Animate::create(pdownStair);
					adownStair->setTag(3);
					player->runAction(adownStair);
					playerState = 3;
				}
				else if (rotation < 0&&playerState != 4) {
					stopAnimate();
					Animate* aupStair = Animate::create(pupStair);
					aupStair->setTag(4);
					player->runAction(aupStair);
					playerState = 4;
				}
			}
		}
		Vec2 speed = player->getPhysicsBody()->getVelocity();
		if (speed.x <= 0) {
			speed.x = 200*1.3;
		}
		int haha = wallBesideRight();
		if (haha == 1) {
			speed.x = 0;
		}
		player->getPhysicsBody()->setVelocity(Vec2(speed.x, speed.y));
		//camera->getPhysicsBody()->setVelocity(Vec2(speed.x, speed.y));
	}
	if (right == left && canmove) {
		Vec2 speed = player->getPhysicsBody()->getVelocity();
		speed.x = 0;
		player->getPhysicsBody()->setVelocity(Vec2(speed.x, speed.y));
		//camera->getPhysicsBody()->setVelocity(Vec2(speed.x, speed.y));
		if (playerState == 1|| playerState == -1 ||playerState == 3||playerState == 4) {
			stopAnimate();
			Animate* aStand = Animate::create(pStand);
			aStand->setTag(0);
			player->runAction(aStand);
			playerState = 0;
		}
	}
	if (onStair) {
		if (up == true) {
			Vec2 speed = player->getPhysicsBody()->getVelocity();
			//speed.x = 0;
			speed.y = 200*1.3;
			player->getPhysicsBody()->setVelocity(Vec2(speed.x, speed.y));
			if (playerState != 16) {
				stopAnimate();
				Animate* aclimb = Animate::create(pclimb);
				aclimb->setTag(16);
				player->runAction(aclimb);
				playerState = 16;
			}
			//camera->getPhysicsBody()->setVelocity(Vec2(speed.x, speed.y));
		}
		if (down == true) {
			Vec2 speed = player->getPhysicsBody()->getVelocity();
			//speed.x = 0;
			speed.y = -200*1.3;
			player->getPhysicsBody()->setVelocity(Vec2(speed.x, speed.y));
			if (playerState != 16) {
				stopAnimate();
				Animate* aclimb = Animate::create(pclimb);
				aclimb->setTag(16);
				player->runAction(aclimb);
				playerState = 16;
			}
			//camera->getPhysicsBody()->setVelocity(Vec2(speed.x, speed.y));
		}
		if (up == down&&!standBy) {
			Vec2 speed = player->getPhysicsBody()->getVelocity();
			player->getPhysicsBody()->setVelocity(Vec2(speed.x, 0));
			
			//camera->getPhysicsBody()->setVelocity(Vec2(speed.x, 0));
		}
	}
	if (standBy) {
		if (down == true) {
			Vec2 speed = player->getPhysicsBody()->getVelocity();
			speed.x = 0;
			speed.y = -200*1.3;
			player->getPhysicsBody()->setVelocity(Vec2(speed.x, speed.y));
			//camera->getPhysicsBody()->setVelocity(Vec2(speed.x, speed.y));
		}
		else if (up != true) {
			Vec2 speed = player->getPhysicsBody()->getVelocity();
			speed.y = 0;
			player->getPhysicsBody()->setVelocity(Vec2(speed.x, speed.y));
			//camera->getPhysicsBody()->setVelocity(Vec2(speed.x, speed.y));
			if (playerState == 6) {
				playerState = -1;
			}
		}

	}
	if (!canmove) {
		Vec2 speed = player->getPhysicsBody()->getVelocity();
		speed.x = 0;
		player->getPhysicsBody()->setVelocity(Vec2(speed.x, speed.y));
		//camera->getPhysicsBody()->setVelocity(Vec2(speed.x, speed.y));
	}
}
void HelloWorld::update(float dt)
{
	for (int i = 0; i < 6; ++i)
	{
		m_world->step(1 / 360.0f);
	}
}
void HelloWorld::changeLocation(float dt) {
	if (Location != player->isFlippedX()) {
		if (Location) {
			auto actionDone = CallFuncN::create([&](Ref* sender) {
				cameramove = false;
				canmove = true;
			});
			auto a = player->getPosition() + Vec2(384.0, 216.0) + (!Location)*Vec2(-768, 0);
			auto moveto = MoveTo::create(0.5, a);
			
			auto action = Sequence::create(moveto, actionDone, NULL);
			if (!jumping&&!droping) {
				cameramove = true;
				canmove = false;
				camera->runAction(action);
			}

		}
		else {
			auto actionDone = CallFuncN::create([&](Ref* sender) {
				cameramove = false;
				canmove = true;
			});
			auto moveby = MoveBy::create(0.5, Vec2(-768, 0));
			auto action = Sequence::create(moveby, actionDone, NULL);
			if (!jumping&&!droping) {
				cameramove = true;
				canmove = false;
				camera->runAction(action);
			}
		}
	}
	player->setFlippedX(Location);
}
void HelloWorld::drop() {
	Point playerPosition = player->getPosition();
	unsigned int image_front_x = player->getPosition().x;
	auto a = player->getContentSize();
	unsigned int image_front_y = background->getContentSize().height - (player->getPosition().y - player->getContentSize().height/2)+5;
	unsigned int image_after_x = image_front_x + 40;
	unsigned int image_after_y = image_front_y;
	ccColor4B c_front = getPixelColorByPoint(Point(image_front_x, image_front_y));
	ccColor4B c_after = getPixelColorByPoint(Point(image_after_x, image_after_y));
	if (c_front.a == 0) {
		droping = true;
		Vec2 speed = player->getPhysicsBody()->getVelocity();
		speed.y = -250*1.3;
		player->getPhysicsBody()->setVelocity(Vec2(speed.x, speed.y));
		//camera->getPhysicsBody()->setVelocity(Vec2(speed.x, speed.y));
		if (playerState != 6&&!onxiepo) {
			Animate* afall = Animate::create(pfall);
			stopAnimate();
			afall->setTag(6);
			player->runAction(afall);
			playerState = 6;
		}
	}
	else {
		Vec2 speed = player->getPhysicsBody()->getVelocity();
		speed.y = 0;
		player->getPhysicsBody()->setVelocity(Vec2(speed.x, speed.y));
		//camera->getPhysicsBody()->setVelocity(Vec2(speed.x, speed.y));
		if (droping == true) {
			droping = false;
			auto actionMoveDone = CallFuncN::create([&](Ref* sender) {
				stopAnimate();
				playerState = -1;
				playingAction = false;
			});
			if (playerState != 7&&(playerState == 6||playerState == 5)) {
				Animate* arecovery = Animate::create(precovery);
				auto action = Sequence::create(arecovery, actionMoveDone, NULL);
				action->setTag(7);
				player->runAction(action);
				playingAction = true;
				playerState = 7;
			}
		}
	}
}
//To fix position when player is in floor or wall
void HelloWorld::fixPosition() {
	if (!onStair&&!jumping&&!droping) {
		Point playerPosition = player->getPosition();
		unsigned int image_x = player->getPosition().x;
		unsigned int image_y = background->getContentSize().height -
			(player->getPosition().y - player->getContentSize().height / 2);
		ccColor4B leftBottom = getPixelColorByPoint(Point(image_x, image_y));
		Vec2 speed = player->getPhysicsBody()->getVelocity();
		if (leftBottom.a == 255&&leftBottom.g < 100) {
			speed.y = 200*1.3;
			player->getPhysicsBody()->setVelocity(Vec2(speed.x, speed.y));
			//camera->getPhysicsBody()->setVelocity(Vec2(speed.x, speed.y));
			if (playerState == 5) {
				playerState = -1;
			}
		}
	}
	Point playerPosition = player->getPosition();
	unsigned int image_x = player->getPosition().x;
	unsigned int image_y = background->getContentSize().height -
		(player->getPosition().y - player->getContentSize().height / 2);
	ccColor4B leftBottom = getPixelColorByPoint(Point(image_x, image_y));
	leftBottom = getPixelColorByPoint(Point(image_x, image_y+20));
}
int HelloWorld::wallBesideLeft() {
	Point playerPosition = player->getPosition();
	unsigned int image_x = player->getPosition().x-10;
	unsigned int image_y = background->getContentSize().height -
		(player->getPosition().y - player->getContentSize().height / 2) - 10;
	ccColor4B leftBottom = getPixelColorByPoint(Point(image_x, image_y));
	image_y -= 20;
	ccColor4B leftTop = getPixelColorByPoint(Point(image_x, image_y));
	if (leftBottom.a >= 225) {
		if (leftTop.a >= 225) {
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
		(player->getPosition().y - player->getContentSize().height / 2) - 10;
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
void HelloWorld::addNewItem(string itemName, Point pos, int a, int b, int c, int d) {
	bool findit = false;
	for (int j = 0; j < itemsVectorInMap.size(); j++) {
		Sprite *itemile = (CCSprite *)itemsVectorInMap.at(j);
		if (itemile->getName() == itemName) {
			findit = true;
			break;
		}
	}
	if (!findit) {
		string path = "item//" + itemName + ".png";
		Sprite* item = Sprite::create(path);
		item->setName(itemName);
		item->setPosition(pos);
		m_UI_Game->addChild(item);
		itemsVectorInMap.pushBack(item);
	}
}
//move finish
void HelloWorld::setPlayerPositionByZone(Sprite* player, Node* zone) {
	Point pos = zone->getPosition();
	pos.y = pos.y - zone->getContentSize().height / 2 + player->getContentSize().height / 2;
	player->setPosition(pos);
}

void HelloWorld::initAnimate() {
	ptemp = loadAnimate("playertemp.gif", 1, false);
	princessStand = loadAnimate("pricness.gif", -1, false);
	princessTemp = loadAnimate("temp.gif", 1, false);
	pStand = loadAnimate("gif//000-stand.gif", -1, false);
	pWalk = loadAnimate("gif//001-walk.gif", -1, false);
	pjump = loadAnimate("gif//005-jump.gif", 1, false);
	pfall = loadAnimate("gif//006-fall.gif", 1, false);
	precovery = loadAnimate("gif//007-recovery.gif", 1, false);
	pdownStair = loadAnimate("gif//003-down-stair.gif", -1, false);
	pupStair = loadAnimate("gif//004-up-stair.gif", -1, false);
	popenWindow = loadAnimate("gif//009-window-open.gif", 1, false);
	pnoidea = loadAnimate("gif//008-no-idea.gif", 1, false);
	patticopen = loadAnimate("gif//010-attic-open.gif", 1, false);
	poutfire = loadAnimate("gif//011-outfire.gif", 1, false);
	pdooropen = loadAnimate("gif//012-door-open.gif", 1, false);
	poilthrow = loadAnimate("gif//013-oil-throw.gif", 1, false);
	pfire = loadAnimate("gif//014-fire.gif", 1, false);
	pturn = loadAnimate("gif//015-turn.gif", 1, false);
	pclimb = loadAnimate("gif//016-climb.gif", -1, false);
	pget = loadAnimate("gif//018-get.gif", 1, false);
	psearch = loadAnimate("gif//017-search.gif", 1, false);

	prstand = loadAnimate("gifByPricness//000-stand.gif", -1, false);
	prkao = loadAnimate("gifByPricness//001-kao.gif", 1, false);
	prtalk = loadAnimate("gifByPricness//002-talk.gif", 1, false);
	prthrow = loadAnimate("gifByPricness//003-throw.gif", 1, false);

	dadstand = loadAnimate("gifByDad//001-stand.gif", -1, false);
	dadtalk  = loadAnimate("gifByDad//002-talk.gif", 1, false);
	dadrun = loadAnimate("gifByDad//003-run.gif", -1, false);
	dadstanby = loadAnimate("gifByDad//004-standby.gif", 1, false);
	dadoutfire = loadAnimate("gifByDad//005-outfire.gif", -1, false);
	//fall
}
void HelloWorld::playerAction() {
	auto actionDone = CallFuncN::create([&](Ref* sender) {
		canmove = true;
		stopAnimate();
		Animate* aStand = Animate::create(pStand);
		aStand->setTag(0);
		player->runAction(aStand);
		playerState = 0;
	});
	canmove = false;
	Animate* playerTempAction = Animate::create(ptemp);
	stopAnimate();
	auto action = Sequence::create(playerTempAction, actionDone, NULL);
	action->setTag(66);
	player->runAction(action);
}

Animation* HelloWorld::loadAnimate(string path, int times, bool back) {
	GifAnimationDef* def = new GifAnimationDef;
	def->loops = times;						// 循环次数
	def->filePath = path;				// 文件路径
	def->delayPerUnit = 1.0/30;			// 每帧间隔
	def->restoreOriginalFrame = back;	// 还原初始状态

										// 创建动画
	auto result = GifAnimation::getInstance()->createAnimation(*def);
	return result;
}
void HelloWorld::stopAnimate() {
	for (int i = 0; i <= 18; i++) {
		player->stopActionByTag(i);
	}
}
void HelloWorld::playerAction(Animation* paction, int i) {
	auto actionDone = CallFuncN::create([&](Ref* sender) {
		canmove = true;
		stopAnimate();
		kailouti = false;
		playerState = -1;
	});
	canmove = false;
	Animate* playerTempAction = Animate::create(paction);
	stopAnimate();
	auto action = Sequence::create(playerTempAction, actionDone, NULL);
	action->setTag(i);
	player->runAction(action);
}
void HelloWorld::showItem(string Name) {
	string path = "item//" + Name + ".png";
	Sprite* item = Sprite::create(path);
	tempitem = item;
	item->setName(Name);
	auto pos = player->getPosition() + Vec2(0,player->getContentSize().height / 2);
	item->setPosition(pos);
	m_UI_Game->addChild(item);
	auto actionDone = CallFuncN::create([&](Ref* sender) {
		if (itemsVectorInPlayer.find(tempitem) == itemsVectorInPlayer.end()) {
			m_UI_Game->removeChild(tempitem);
			player->addChild(tempitem);
			itemsVectorInPlayer.pushBack(tempitem);
		}
	});
	auto delay = DelayTime::create(0.5);
	auto action = Sequence::create(delay, actionDone, NULL);
	item->runAction(action);
}
void HelloWorld::playerAction(Animation* paction, int i, string Name) {
	auto actionDone = CallFuncN::create([&](Ref* sender) {
		stopAnimate();
		auto getactionDone = CallFuncN::create([&](Ref* sender) {
			canmove = true;
			stopAnimate();
			playerState = -1;
		});
		Animate* getAction = Animate::create(pget);
		auto allaction = Sequence::create(getAction, getactionDone, NULL);
		player->runAction(allaction);
		showItem(itemName);

	});
	canmove = false;
	Animate* playerTempAction = Animate::create(paction);
	stopAnimate();
	auto action = Sequence::create(playerTempAction, actionDone, NULL);
	action->setTag(i);
	itemName = Name;
	player->runAction(action);
	playerState = i;
}
void HelloWorld::princesscomming() {
	auto cameraMoveDone = CallFuncN::create([&](Ref* sender) {
		auto actionDone = CallFuncN::create([&](Ref* sender) {
			addNewItem("hairpin", Vec2(2734, 3947), 1, 2, 3, 4);
			Animate* princessStand = Animate::create(prstand);
			princess->stopAllActions();
			princess->runAction(princessStand);
			cameramove = false;
			canmove = true;
		});
		canmove = false;
		Animate* princessKao = Animate::create(prkao);
		Animate* princessTalk = Animate::create(prtalk);
		Animate* princessThrow = Animate::create(prthrow);
		auto action = Sequence::create(princessKao, princessTalk, princessThrow, actionDone, NULL);
		princess->runAction(action);
	});
	auto pos = (player->getPosition() + princess->getPosition()) / 2;
	auto cameraaction = MoveTo::create(0.5, pos);
	auto caction = Sequence::create(cameraaction, cameraMoveDone, NULL);
	cameramove = true;
	camera->runAction(caction);
}
void HelloWorld::actorPlayAction(Sprite* actor, Animation* paction, int actionnum) {
	actor->stopAllActions();
	Animate* playerTempAction = Animate::create(paction);
	playerTempAction->setTag(actionnum);
	actor->runAction(playerTempAction);
}