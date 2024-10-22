#pragma once

#include <QObject>
#include "menubarmanager.h"

#include <dialog/rescaledialog.h>
#include <dialog/resizedialog.h>

#include "../view/viewmanager.h"

namespace ui {
    class ImageMenuLambda : public MenuLambda {
        Q_OBJECT
        private:
            const QMenu * _menu;
            dialog::ReScaleDialog * _rescale;
            dialog::ReSizeDialog * _resize;
            ViewManager * _viewManager;
            ImageArea * _area;

        protected:
            enum Actions : unsigned char {
                RESIZE  = 0,
                RESCALE = 1,
                TURN    = 3,
                ROTATE  = 4
            };

        public:
            ImageMenuLambda(dialog::ReScaleDialog *, dialog::ReSizeDialog *,ViewManager *);

            virtual void initializeMenu(const QMenu *) final;

        public slots:
            void viewChange(ImageArea *);

            void turn_H();
            void turn_V();

            void turn_left();
            void turn_right();
    };
}
