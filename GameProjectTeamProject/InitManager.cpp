#include "InitManager.h"

#include<windows.h>

#include "InputSystem.h"
#include "EntityManager.h"
#include "InventoryManager.h"
#include "TempEnums.h"
#include "Item.h"
#include "Constants.h"

InitManager::InitManager() :
    _pPlayer(nullptr) {
    // Input Init

    // UI키 우선함.
    // 으뜸은 커멘드 입력
    InputManager* inputManager = InputManager::GetInstance();
    inputManager->addInputKeyPair({ VK_SPACE, Key::READYINPUT });
    inputManager->addInputKeyPair({ VK_RETURN, Key::ENDINPUT });

    inputManager->addInputKeyPair({ 'I', Key::OPENINVEN });
    inputManager->addInputKeyPair({ 'B', Key::OPENINVEN });

    inputManager->addInputKeyPair({ 'F', Key::INTERACT });

    inputManager->addInputKeyPair({ 'W', Key::UP });
    inputManager->addInputKeyPair({ VK_UP, Key::UP });
    inputManager->addInputKeyPair({ 'S', Key::DOWN });
    inputManager->addInputKeyPair({ VK_DOWN, Key::DOWN });
    inputManager->addInputKeyPair({ 'A', Key::LEFT });
    inputManager->addInputKeyPair({ VK_LEFT, Key::LEFT });
    inputManager->addInputKeyPair({ 'D', Key::RIGHT });
    inputManager->addInputKeyPair({ VK_RIGHT, Key::RIGHT });

    inputManager->addInputKeyPair({ VK_ESCAPE, Key::ESC });

    for (int i = 1; i <= 9; ++i)
        // 0x31이 키보드 1
        inputManager->addInputKeyPair({ 0x30 + i, (Key)((int)Key::ONE + (i - 1)) });

    // 항상 먼저 값을 입력 받게
    inputManager->SetUpdatePriotity(2147483647);


    // PhysicsManager Init

    PhysicsManager* physicsManager = PhysicsManager::GetInstance();
    physicsManager->setMaxMoveBound(MAP_WIDTH, MAP_HEIGHT);


    // Inventory Init

    InventoryManager* inventoryManager = InventoryManager::GetInstance();
    inventoryManager->init(3);
}

void InitManager::InitPlayer() {
    _pPlayer = new Player();

    char idleAnimation = 'i', moveAnimation = 'm';

    int addDamagePer = 10;
    int startDamage = 30, startMaxHP = 150, startAvoidance = 0;

    _pPlayer->init(EntityStat::makeStat(startDamage, startMaxHP, startAvoidance, addDamagePer), L'P', false, L(Layer::PLAYER));
    _pPlayer->active();

    std::string name;
    system("cls");
    MoveCursor(0, 0);
    std::cout << "새로운 희생자의 이름은?";
    std::cin >> name;
    _pPlayer->setName(name);

    _pPlayer->render.addAnimation(idleAnimation, { L'⛭', L'⛯' });
    _pPlayer->render.addAnimation(moveAnimation, { L'⛮', L'⛭' });
    _pPlayer->render.setCurrentAnimation(idleAnimation);

    _pPlayer->setWhatIsEnemyLayer(L(Layer::ENEMY));
    _pPlayer->setWhatIsItemLayer(L(Layer::ITEM));
    _pPlayer->setWhatIsWallLayer(L(Layer::WALL));

    // 무겁게
    _pPlayer->addAttackComment("칼날을 적의 피부 깊숙이 박아 끔찍한 고통을 선사했다");
    _pPlayer->addAttackComment("적의 살점을 찢어내며 잔혹하게 공격했다");
    _pPlayer->addAttackComment("붉은 피가 튀는 소리와 함께 맹공을 퍼부었다");
    _pPlayer->addAttackComment("공포가 무엇인지 알려줬다");
    _pPlayer->addAttackComment("적의 살갗을 찢어 피를 흐르게 했다");
    _pPlayer->addAttackComment("결의 찬 회심의 일격을 가했다");
    _pPlayer->addAttackComment("배에 칼을 박고 돌려 내장이 쏟아지게끔 했다");

    // 가볍게
    _pPlayer->addAttackComment("너무 약한 공격을 하여 이를 도발로 받아드린 적은 혈압이 올랐다");
    _pPlayer->addAttackComment("차마 입에 담기 꺼려지는 인신공격을 가했다");
    _pPlayer->addAttackComment("공격을 했지만 실패했다... 실패한 공격이 적의 새끼발톱을 쳐 끔찍한 고통을 가했다");
    _pPlayer->addAttackComment("균형을 잃어 적어게 넘어져 적에게 로멘틱한 자세를 취했다. 적의 심장이 빠르게 뛴다");
    _pPlayer->addAttackComment("음심에 가득한 신체접촉을 했다. 적이 기겁하면 정신적 충격을 받았다");

    // 테스트
    _pPlayer->SetRenderPriotity(100);
    _pPlayer->SetUpdatePriotity(100);

    InitItems();
}

void InitManager::InitEnemies() {
    char idleAnimation = 'i', moveAnimation = 'm';

    EntityManager* entityManager = EntityManager::GetInstance();

    // 극히 무식하다..
    // 아니 생긴게 흉측해서 그런가?

    std::string tempEnemyName = "star";
    entityManager->addObjectData(ENEMY_DATA_POOL, tempEnemyName, new Enemy());
    Enemy* enemyPtr = dynamic_cast<Enemy*>(entityManager->getObjectData(ENEMY_DATA_POOL, tempEnemyName));
    if (enemyPtr != nullptr) {
        Enemy& star = *enemyPtr;
        // active()를 하지않아 데이터 상으로 남아있게 함. 복사 생성으로 계속 사용이 가능하게
        star.init(EntityStat::makeStat(5, 20, 100, 10), L'E', false, L(Layer::ENEMY));

        star.setPlayer(_pPlayer);
        star.setSenceRange(3);
        star.setWallLayer(L(Layer::WALL));

        star.render.addAnimation(idleAnimation, { L'⛦', L'⛧' });
        star.render.setCurrentAnimation(idleAnimation);

        star.setName("별");
        star.addDeadMessage("자신의 별조각을 떨어트리며 사라졌다");
        star.addDeadMessage("약한 폭발과 합께 사라졌다");
        star.addDeadMessage("온 몸이 흩어져 날라갔다");
        star.addDeadMessage("자신의 존재 이유를 잊고 사그라졌다");

        star.addAttackComment("자신의 날카로운 조각으로 찌르는 공격을 했다");
        star.addAttackComment("빠르게 베어지나가는 공격을 했다");
        star.addAttackComment("시야를 빼앗는 강렬한 불빛을 내뿜었다");
    }
    

    tempEnemyName = "SovietUnion";
    entityManager->addObjectData(ENEMY_DATA_POOL, tempEnemyName, new Enemy());
    enemyPtr = dynamic_cast<Enemy*>(entityManager->getObjectData(ENEMY_DATA_POOL, tempEnemyName));
    if (enemyPtr != nullptr) {
        Enemy& star = *enemyPtr;
        // active()를 하지않아 데이터 상으로 남아있게 함. 복사 생성으로 계속 사용이 가능하게
        star.init(EntityStat::makeStat(7, 15, 100, 15), L'E', false, L(Layer::ENEMY));

        star.setPlayer(_pPlayer);
        star.setSenceRange(5);

        star.render.addAnimation(idleAnimation, { L'☭', L'⚸', L'⚒' });
        star.render.setCurrentAnimation(idleAnimation);

        star.setName("붉은 녀석");
        star.addDeadMessage("혁명의 아쉬움을 말하며 사라졌다");
        star.addDeadMessage("\"노동자 단결..\"이라 말하며 죽었다");

        star.addAttackComment("사상을 전파 했다");
        star.addAttackComment("수상한 책을 건내줬다");
        star.addAttackComment("신기할 정도로 설득력 있는 연설을 했다");
    }


    tempEnemyName = "Dice";
    entityManager->addObjectData(ENEMY_DATA_POOL, tempEnemyName, new Enemy());
    enemyPtr = dynamic_cast<Enemy*>(entityManager->getObjectData(ENEMY_DATA_POOL, tempEnemyName));
    if (enemyPtr != nullptr) {
        Enemy& star = *enemyPtr;
        // active()를 하지않아 데이터 상으로 남아있게 함. 복사 생성으로 계속 사용이 가능하게
        star.init(EntityStat::makeStat(3, 7, 200, 50), L'E', false, L(Layer::ENEMY));

        star.setPlayer(_pPlayer);
        star.setSenceRange(7);

        star.render.addAnimation(idleAnimation, { L'⚀', L'⚁', L'⚂', L'⚃', L'⚄', L'⚅', L'⚄', L'⚃', L'⚂', L'⚁' });
        star.render.setCurrentAnimation(idleAnimation);

        star.setName("도박꾼");
        star.addDeadMessage("빚을 갚지 않아도 되게 되어 웃었다");
        star.addDeadMessage("그의 손에서 주사위가 굴러떨어졌다... 숫자는 1이다");

        star.addAttackComment("카드를 날렸다");
        star.addAttackComment("돈을 빌렸다.. 갚진 않았다");
    }


    tempEnemyName = "Nu";
    entityManager->addObjectData(ENEMY_DATA_POOL, tempEnemyName, new Enemy());
    enemyPtr = dynamic_cast<Enemy*>(entityManager->getObjectData(ENEMY_DATA_POOL, tempEnemyName));
    if (enemyPtr != nullptr) {
        Enemy& star = *enemyPtr;
        // active()를 하지않아 데이터 상으로 남아있게 함. 복사 생성으로 계속 사용이 가능하게
        star.init(EntityStat::makeStat(15, 5, 0, 0), L'E', false, L(Layer::ENEMY));

        star.setPlayer(_pPlayer);
        star.setSenceRange(7);

        star.render.addAnimation(idleAnimation, { L'☢' });
        star.render.setCurrentAnimation(idleAnimation);

        star.setName("방사능");
        star.addDeadMessage("빛이 바랬다");

        star.addAttackComment("닿았다");
    }


    tempEnemyName = "snow";
    entityManager->addObjectData(ENEMY_DATA_POOL, tempEnemyName, new Enemy());
    enemyPtr = dynamic_cast<Enemy*>(entityManager->getObjectData(ENEMY_DATA_POOL, tempEnemyName));
    if (enemyPtr != nullptr) {
        Enemy& star = *enemyPtr;
        // active()를 하지않아 데이터 상으로 남아있게 함. 복사 생성으로 계속 사용이 가능하게
        star.init(EntityStat::makeStat(2, 25, 0, 10), L'E', false, L(Layer::ENEMY));

        star.setPlayer(_pPlayer);
        star.setSenceRange(7);

        star.render.addAnimation(idleAnimation, { L'☃' });
        star.render.setCurrentAnimation(idleAnimation);

        star.setName("눈사람");
        star.addDeadMessage("녹았다");
        star.addDeadMessage("코를 잃어버렸다");

        star.addAttackComment("안았다");
        star.addAttackComment("당신에세 발로 차라고 부탁했다. 몸에 돌이 들어있었다");
    }


    tempEnemyName = "te";
    entityManager->addObjectData(ENEMY_DATA_POOL, tempEnemyName, new Enemy());
    enemyPtr = dynamic_cast<Enemy*>(entityManager->getObjectData(ENEMY_DATA_POOL, tempEnemyName));
    if (enemyPtr != nullptr) {
        Enemy& star = *enemyPtr;
        // active()를 하지않아 데이터 상으로 남아있게 함. 복사 생성으로 계속 사용이 가능하게
        star.init(EntityStat::makeStat(8, 15, 15, 15), L'E', false, L(Layer::ENEMY));

        star.setPlayer(_pPlayer);
        star.setSenceRange(7);

        star.render.addAnimation(idleAnimation, { L'☠' });
        star.render.setCurrentAnimation(idleAnimation);

        star.setName("테러리스트");
        star.addDeadMessage("제압당했다");
        star.addDeadMessage("거짓 인질 협상에 넘어갔다");
        star.addDeadMessage("저격당했다");
        star.addDeadMessage("인질을 놓쳤다");

        star.addAttackComment("인질을 공격하겠다 협박한다");
        star.addAttackComment("다음 거짓된 테러 장소를 예고한다");
    }
}

void InitManager::InitItems() {
    EntityManager* entityManager = EntityManager::GetInstance();

    std::string statItemName = "potionN";
    entityManager->addObjectData(ITEM_DATA_POOL, statItemName, new StatItem());
    StatItem* statItemPtr = dynamic_cast<StatItem*>(entityManager->getObjectData(ITEM_DATA_POOL, statItemName));
    if (statItemPtr != nullptr) {
        StatItem& potion = *statItemPtr;
        potion.init(L'♙', true, L(Layer::ITEM));

        potion.setName("회복포션");
        potion.setUpStat(EntityStat::makeStat(0, 0, 0, 0, 25));
    }

    std::string statItemName = "potionR";
    entityManager->addObjectData(ITEM_DATA_POOL, statItemName, new StatItem());
    StatItem* statItemPtr = dynamic_cast<StatItem*>(entityManager->getObjectData(ITEM_DATA_POOL, statItemName));
    if (statItemPtr != nullptr) {
        StatItem& potion = *statItemPtr;
        potion.init(L'♟', true, L(Layer::ITEM));

        potion.setName("고급포션");
        potion.setUpStat(EntityStat::makeStat(0, 0, 0, 0, 50));
    }

    statItemName = "potionAtk";
    entityManager->addObjectData(ITEM_DATA_POOL, statItemName, new StatItem());
    statItemPtr = dynamic_cast<StatItem*>(entityManager->getObjectData(ITEM_DATA_POOL, statItemName));
    if (statItemPtr != nullptr) {
        StatItem& potion = *statItemPtr;
        potion.init(L'♗', true, L(Layer::ITEM));

        potion.setName("공격물약");
        potion.setUpStat(EntityStat::makeStat(4, 0, 0, 0, 0));
    }

    statItemName = "potion";
    entityManager->addObjectData(ITEM_DATA_POOL, statItemName, new StatItem());
    statItemPtr = dynamic_cast<StatItem*>(entityManager->getObjectData(ITEM_DATA_POOL, statItemName));
    if (statItemPtr != nullptr) {
        StatItem& potion = *statItemPtr;
        potion.init(L'♕', true, L(Layer::ITEM));

        potion.setName("활력물약");
        potion.setUpStat(EntityStat::makeStat(0, 7, 0, 0, 0));
    }

    statItemName = "potionAd";
    entityManager->addObjectData(ITEM_DATA_POOL, statItemName, new StatItem());
    statItemPtr = dynamic_cast<StatItem*>(entityManager->getObjectData(ITEM_DATA_POOL, statItemName));
    if (statItemPtr != nullptr) {
        StatItem& potion = *statItemPtr;
        potion.init(L'♕', true, L(Layer::ITEM));

        potion.setName("회피물약");
        potion.setUpStat(EntityStat::makeStat(0, 0, 3, 0, 0));
    }

    statItemName = "potionAll";
    entityManager->addObjectData(ITEM_DATA_POOL, statItemName, new StatItem());
    statItemPtr = dynamic_cast<StatItem*>(entityManager->getObjectData(ITEM_DATA_POOL, statItemName));
    if (statItemPtr != nullptr) {
        StatItem& potion = *statItemPtr;
        potion.init(L'♔', true, L(Layer::ITEM));

        potion.setName("만능물약");
        potion.setUpStat(EntityStat::makeStat(2, 4, 3, 0, 10));
    }

    statItemName = "potionLuck";
    entityManager->addObjectData(ITEM_DATA_POOL, statItemName, new StatItem());
    statItemPtr = dynamic_cast<StatItem*>(entityManager->getObjectData(ITEM_DATA_POOL, statItemName));
    if (statItemPtr != nullptr) {
        StatItem& potion = *statItemPtr;
        potion.init(L'♔', true, L(Layer::ITEM));

        potion.setName("도박사의약");
        potion.setUpStat(EntityStat::makeStat(0, 0, 0, 5, 0));
    }
}

void InitManager::DeletePlayer() {
    delete _pPlayer;
}
