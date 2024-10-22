#pragma once

#include "../view/selection.h"

namespace effect {
    class Effect {
        public:
            Effect() {}
   virtual ~Effect() {}

            virtual void apply(const QSet<QPoint> &, QImage &) const = 0;
            void use(const ui::Selection &, QImage &) const;
    };
}
