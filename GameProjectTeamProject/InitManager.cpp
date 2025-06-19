#include "InitManager.h"

InitManager::InitManager():
    _player(Player()) {
    PhysicsManager* physicsManager = PhysicsManager::GetInstance();
    physicsManager->initialize(100, 100);

    // 레이어 설정 필요
    _player.init(L'P', false, 0);

    // test
    _player.SetRenderPriotity(-100);
    _player.SetUpdatePriotity(-100);
    _player.setPosition({30, 30});
}
