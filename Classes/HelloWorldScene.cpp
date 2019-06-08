/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
enum
{
	kTagSpriteManager = 1,
};
Scene* HelloWorld::createScene()
{
	auto scene = Scene::createWithPhysics();
	auto layer =HelloWorld::create();
	scene->addChild(layer);
	auto world = scene->getPhysicsWorld();
	auto gravity = Vec2(0, -98);
	world->setGravity(gravity);
	world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	return scene;
}

void HelloWorld::addNewSpriteWithCoords(Vec2 p)
{
	// //UXLOG(L"Add sprite %0.2f x %02.f",p.x,p.y);
	auto sheet = 
		static_cast<SpriteBatchNode*>(getChildByTag(kTagSpriteManager));
	//We have a 64x64 sprite sheet with 4 different 32x32 images.  The following code is
	//just randomly picking one of the images
	int idx = (CCRANDOM_0_1() > .5 ? 0 : 1);
	int idy = (CCRANDOM_0_1() > .5 ? 0 : 1);
	//    CCSprite::crea
	auto sprite = Sprite::createWithTexture(sheet->getTexture(),
		Rect(32 * idx, 32 * idy, 32, 32));
	sprite->setPosition(Vec2(p.x, p.y));
	this->addChild(sprite);
	auto spriteBody = PhysicsBody::createBox(sprite->getContentSize(),
		PhysicsMaterial(1.0f,0.0f,0.3f));
	sprite->setPhysicsBody(spriteBody);
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

	// wall
	auto wallSprite = Node::create();
	wallSprite->setPosition(visibleSize / 2);
	auto wallBody = PhysicsBody::createEdgeBox(visibleSize);
	wallSprite->setPhysicsBody(wallBody);
	this->addChild(wallSprite);

	// Sprite
	auto spriteBatch = SpriteBatchNode::create("blocks.png", 150);
	this->addChild(spriteBatch, 0, kTagSpriteManager);

	return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

void HelloWorld::onEnter()
{
	Scene::onEnter();
	
	// Sprite
	addNewSpriteWithCoords(Vec2(visibleSize.width / 2, visibleSize.height / 2));
}
