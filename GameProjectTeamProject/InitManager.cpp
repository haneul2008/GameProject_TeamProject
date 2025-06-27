#include "InitManager.h"

#include<windows.h>

#include "InputSystem.h"
#include "EntityManager.h"
#include "TempEnums.h"

InitManager::InitManager() :
    _player(Player()) {
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


    // Player Init

    int addDamagePer = 10;

    // 레이어 설정 필요
    char idleAnimation = 'i', moveAnimation = 'm';

    int startDamage = 1, startMaxHP = 10, startAvoidance = 0;

    _player.init(EntityStat::makeStat(startDamage, startMaxHP, startAvoidance, addDamagePer), L'P', false, L(Layer::PLAYER));
    _player.active();

    _player.render.addAnimation(idleAnimation, { L'⛭', L'⛯' });
    _player.render.addAnimation(moveAnimation, { L'⛮', L'⛭' });
    _player.render.setCurrentAnimation(idleAnimation);

    _player.setWhatIsEnemyLayer(L(Layer::ENEMY));
    _player.setWhatIsItemLayer(L(Layer::ITEM));
    _player.setWhatIsWallLayer(L(Layer::WALL));

    // 무겁게
    _player.addAttackComment("칼날을 적의 피부 깊숙이 박아 끔찍한 고통을 선사했다");
    _player.addAttackComment("적의 살점을 찢어내며 잔혹하게 공격했다");
    _player.addAttackComment("붉은 피가 튀는 소리와 함께 맹공을 퍼부었다");
    _player.addAttackComment("공포가 무엇인지 알려줬다");
    _player.addAttackComment("적의 살갗을 찢어 피를 흐르게 했다");
    _player.addAttackComment("결의 찬 회심의 일격을 가했다");
    _player.addAttackComment("배에 칼을 박고 돌려 내장이 쏟아지게끔 했다");

    // 가볍게
    _player.addAttackComment("너무 약한 공격을 하여 이를 도발로 받아드린 적은 혈압이 올랐다");
    _player.addAttackComment("차마 입에 담기 꺼려지는 인신공격을 가했다");
    _player.addAttackComment("공격을 했지만 실패했다... 실패한 공격이 적의 새끼발톱을 쳐 끔찍한 고통을 가했다");
    _player.addAttackComment("균형을 잃어 적어게 넘어져 적에게 로멘틱한 자세를 취했다. 적의 심장이 빠르게 뛴다");
    _player.addAttackComment("음심에 가득한 신체접촉을 했다. 적이 기겁하면 정신적 충격을 받았다");


    // Enemy Init

    std::string enemyDataPoolName = "ENEMY";
    std::string e_star_name = "star";

    EntityManager* entityManager = EntityManager::GetInstance();

    entityManager->addEntityData(enemyDataPoolName, e_star_name, new Enemy());
    Enemy* enemyPtr = dynamic_cast<Enemy*>(entityManager->getEntityData(enemyDataPoolName, e_star_name));
    if (enemyPtr != nullptr) {
        Enemy& star = *enemyPtr;
        // active()를 하지않아 데이터 상으로 남아있게 함. 복사 생성으로 계속 사용이 가능하게
        star.init(EntityStat::makeStat(1, 5, 10, 10), L'E', false, L(Layer::ENEMY));

        star.setPlayer(&_player);
        star.setSenceRange(5);

        star.render.addAnimation(idleAnimation, { L'⛦', L'⛧' });
        star.render.setCurrentAnimation(idleAnimation);

        star.setName("별");
        star.addDeadMessage("자신의 별조각을 떨어트리며 사라졌다");
        star.addDeadMessage("약한 폭발과 합께 사라졌다");
        star.addDeadMessage("온 몸이 흩어져 날라갔다");
        star.addDeadMessage("자신의 존재 이유를 잊고 사그라졌다");

        star.addAttackComment("자신의 날카로운 조각으로 찔렀다");
        star.addAttackComment("빠르게 베었다");
        star.addAttackComment("강렬한 불빛으로 시야를 빼앗았다");
    }


    // Test

    _player.SetRenderPriotity(100);
    _player.SetUpdatePriotity(100);
    _player.setPosition({ 30, 30 });

    Entity* newEnemy = entityManager->activeRandomEntity(enemyDataPoolName);
    newEnemy->setPosition({10, 10});
}
