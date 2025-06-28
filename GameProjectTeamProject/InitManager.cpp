#include "InitManager.h"

#include<windows.h>

#include "InputSystem.h"
#include "EntityManager.h"
#include "TempEnums.h"

InitManager::InitManager() :
    _pPlayer(nullptr) {
    // PhysicsManager Init

    PhysicsManager* physicsManager = PhysicsManager::GetInstance();
    physicsManager->setMaxMoveBound(100, 100);


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

    inputManager->SetUpdatePriotity(1000);


    // Enemy Init

    //char idleAnimation = 'i', moveAnimation = 'm';

    //std::string enemyDataPoolName = "ENEMY";
    //std::string e_star_name = "star";

    //EntityManager* entityManager = EntityManager::GetInstance();

    //entityManager->addEntityData(enemyDataPoolName, e_star_name, new Enemy());
    //Enemy* enemyPtr = dynamic_cast<Enemy*>(entityManager->getEntityData(enemyDataPoolName, e_star_name));
    //if (enemyPtr != nullptr) {
    //    Enemy& star = *enemyPtr;
    //    // active()를 하지않아 데이터 상으로 남아있게 함. 복사 생성으로 계속 사용이 가능하게
    //    star.init(EntityStat::makeStat(1, 5, 10, 10), L'E', false, L(Layer::ENEMY));

    //    star.setPlayer(_pPlayer);
    //    star.setSenceRange(5);

    //    star.render.addAnimation(idleAnimation, { L'⛦', L'⛧' });
    //    star.render.setCurrentAnimation(idleAnimation);

    //    star.setName("별");
    //    star.addDeadMessage("자신의 별조각을 떨어트리며 사라졌다");
    //    star.addDeadMessage("약한 폭발과 합께 사라졌다");
    //    star.addDeadMessage("온 몸이 흩어져 날라갔다");
    //    star.addDeadMessage("자신의 존재 이유를 잊고 사그라졌다");

    //    star.addAttackComment("자신의 날카로운 조각으로 찌르는 공격을 했다");
    //    star.addAttackComment("빠르게 베어지나가는 공격을 했다");
    //    star.addAttackComment("시야를 빼는 강렬한 불빛을 내뿜었다");
    //}


    //// Test

    //Entity* newEnemy = entityManager->activeRandomEntity(enemyDataPoolName);
    //newEnemy->setPosition({10, 10});
}

void InitManager::InitPlayer()
{
    // Player Init
    _pPlayer = new Player();

    char idleAnimation = 'i', moveAnimation = 'm';

    int addDamagePer = 10;
    int startDamage = 1, startMaxHP = 10, startAvoidance = 0;

    _pPlayer->init(EntityStat::makeStat(startDamage, startMaxHP, startAvoidance, addDamagePer), L'P', false, L(Layer::PLAYER));
    _pPlayer->active();

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
    _pPlayer->setPosition({ 30, 30 });
}

void InitManager::DeletePlayer()
{
    delete _pPlayer;
}
