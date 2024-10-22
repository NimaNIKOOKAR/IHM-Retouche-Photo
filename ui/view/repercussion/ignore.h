#pragma once

#include "repercussion.h"

namespace ui {
    class Ignore : public Repercution{
        public:
            Ignore() : Repercution("Ignore") {}
   virtual ~Ignore() {}

            virtual void apply(const QPoint &, const QColor &, const QImage *, QImage *);
    };
}

