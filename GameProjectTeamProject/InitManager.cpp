#include "InitManager.h"

InitManager::InitManager():
    _player(Player()) {
    PhysicsManager* physicsManager = PhysicsManager::GetInstance();
    physicsManager->initialize(100, 100);

    // 레이어 설정 필요
    int playerLayer = 0;
    char idleAnimation = 'i';
    char moveAnimation = 'm';
    _player.init(L'P', false, playerLayer);
    // {L'⛦', L'⛧' }
    _player.render.addAnimation(idleAnimation, {L'⛭', L'⛯' });
    _player.render.addAnimation(moveAnimation, {L'⛭', L'⛮' });
    _player.render.setCurrentAnimation(idleAnimation);

    // test
    _player.SetRenderPriotity(-100);
    _player.SetUpdatePriotity(-100);
    _player.setPosition({30, 30});
}
