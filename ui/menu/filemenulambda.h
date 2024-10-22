#pragma once

#include "menubarmanager.h"
#include "../files/fileselector.h"
#include "../view/viewmanager.h"

namespace ui {
    class FilemenuLambda : public MenuLambda {
        Q_OBJECT
        private:
            FileSelector * _fileSelector;
            ViewManager * _viewManager;

        protected:
            enum Actions : unsigned char {
                NEW         = 0,
                OPEN        = 1,
                OPEN_DIR    = 2,
                SAVE        = 4,
                SAVE_AS     = 5,
                SAVE_ALL    = 6,
                CLOSE       = 8,
                QUIT        = 9
            };

        public:
            FilemenuLambda(FileSelector *, ViewManager *);
   virtual ~FilemenuLambda();

            virtual void initializeMenu(const QMenu *) final;
    };
}

