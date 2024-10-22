#pragma once

#include "repercussion.h"

namespace ui {
    class Average : public Repercution {
        public:
            Average() : Repercution("Average") {}
            virtual ~Average() {}

            virtual void apply(const QPoint &, const QColor &, const QImage *, QImage *);
    };
}

