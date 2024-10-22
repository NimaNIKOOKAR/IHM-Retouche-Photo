#include "displaymenulambda.h"

namespace ui {
    DisplayMenuLambda::DisplayMenuLambda(ViewManager * manager)
    : _manager(manager), _area(manager->currentView()) {
        this->viewChange(this->_manager->currentView());
        QObject::connect(this->_manager, SIGNAL(changedView(ImageArea*)), this, SLOT(viewChange(ImageArea*)));
    }

    void DisplayMenuLambda::initializeMenu(const QMenu * menu) {
        this->_menu = menu;

    }

    void DisplayMenuLambda::viewChange(ImageArea *) {
        if(this->_menu != nullptr) {
            if(this->_area != nullptr) {
                QObject::disconnect(this->_menu->actions().at(Actions::ZOOM_IN),  SIGNAL(triggered()), this->_area, SLOT(increaseZoom()));
                QObject::disconnect(this->_menu->actions().at(Actions::ZOOM_OUT), SIGNAL(triggered()), this->_area, SLOT(decreaseZoom()));
            }

            this->_area = this->_manager->currentView();

            if(this->_area != nullptr) {
                QObject::connect(this->_menu->actions().at(Actions::ZOOM_IN),  SIGNAL(triggered()), this->_area, SLOT(increaseZoom()));
                QObject::connect(this->_menu->actions().at(Actions::ZOOM_OUT), SIGNAL(triggered()), this->_area, SLOT(decreaseZoom()));
            }
        }
    }
}
