#pragma once

#include "repercussion.h"

namespace ui {
    class Clamp : public Repercution {
        public:
            Clamp() : Repercution("Clamp") {}
            virtual ~Clamp() {}

            virtual void apply(const QPoint &, const QColor &, const QImage *, QImage *);
    };
}

