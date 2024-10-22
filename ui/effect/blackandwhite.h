#pragma once

#include "effect.h"


namespace effect {
    class BlackAndWhite : public Effect {
        public:
            BlackAndWhite();
   virtual ~BlackAndWhite();

            virtual void apply(const QSet<QPoint> &, QImage &) const;
    };
}

