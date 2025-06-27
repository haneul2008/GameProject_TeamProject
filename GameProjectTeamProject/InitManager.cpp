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

    // test
    _player.SetRenderPriotity(100);
    _player.SetUpdatePriotity(100);
    _player.setPosition({ 30, 30 });


    // Enemy Init

    EntityManager* entityManager = EntityManager::GetInstance();

    entityManager->addEntityData("E_star", std::move(Enemy()));
    Enemy* starPtr = dynamic_cast<Enemy*>(entityManager->getEntityData("E_star"));
    if (starPtr != nullptr) {
        Enemy& star = *starPtr;
        star.init(EntityStat::makeStat(1, 5, 10, 10), L'E', false, L(Layer::ENEMY));
        // active()를 하지않아 데이터 상으로 남아있게 함. 복사 생성으로 계속 사용이 가능하게
        star.render.addAnimation(idleAnimation, { L'⛦', L'⛧' });
        star.render.setCurrentAnimation(idleAnimation);

        star.setName("별");
        star.addDeadMessage("자신의 별조각을 떨어트리며 사라졌다");
        star.addDeadMessage("약한 폭발과 합께 사라졌다");
        star.addDeadMessage("온 몸이 흩어져 날라갔다");
        star.addDeadMessage("자신의 존재 이유를 잊고 사그라졌다");
    }
}
