#include "menubarmanager.h"

#include <QDebug>

namespace ui {
    void MenubarManager::update() {
        for(auto &[menu, lambda] : this->toStdMap()) {
            lambda->initializeMenu(menu);
        }
    }
}
