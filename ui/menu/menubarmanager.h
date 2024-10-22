#pragma once

#include <QMenuBar>
#include <QMenu>
#include <QMap>
#include <QSharedPointer>

namespace ui {
    class MenuLambda : public QObject {
        Q_OBJECT
        public:
            virtual void initializeMenu(const QMenu *) = 0;
    };

    class MenubarManager : public QMap<const QMenu *, QSharedPointer<MenuLambda>> {
        public:
            void update();
    };
}

