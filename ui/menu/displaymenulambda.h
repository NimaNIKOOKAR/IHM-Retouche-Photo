#pragma once

#include <QObject>
#include "menubarmanager.h"

#include "../view/viewmanager.h"

namespace ui {
    class DisplayMenuLambda : public MenuLambda {
        Q_OBJECT
        private:
            const QMenu * _menu;
            ViewManager * _manager;
            ImageArea * _area;

        protected:
            enum Actions : unsigned char {
                ZOOM_IN = 0,
                ZOOM_OUT = 1
            };

        public:
            DisplayMenuLambda(ViewManager * manager);
            virtual void initializeMenu(const QMenu *) final;

        public slots:
            void viewChange(ImageArea *);
    };
}

