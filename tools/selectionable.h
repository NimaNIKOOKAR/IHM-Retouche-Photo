#pragma once

#include "tool.h"
#include "../ui/view/selection.h"

namespace tool {
    class Selectionable : public Tool {
        private:
            const QString _name;
            const QIcon _icon;

        protected:
            void onPressed(ui::Selection *);
            void onreleased(ui::Selection *);

        public:
            Selectionable(const QString &, const QIcon &);
    };
}
