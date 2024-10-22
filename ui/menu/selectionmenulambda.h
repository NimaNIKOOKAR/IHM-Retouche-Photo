#pragma once

#include "menubarmanager.h"

#include "../view/viewmanager.h"

namespace ui {
    class SelectionMenuLambda : public MenuLambda {
        Q_OBJECT
        private:
            const QMenu * _menu;
            ViewManager * _manager;

        protected:
            enum Actions {
                SUPPR,
                UNSELECT
            };

        public:
            SelectionMenuLambda(ViewManager *);

            virtual void initializeMenu(const QMenu *) final;

        public slots:
            void viewChanged(ImageArea *);
    };
}
