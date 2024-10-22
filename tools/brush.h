#pragma once

#include "tool.h"

namespace tool {
    class Brush : public Tool {
        public:
            Brush(QListWidget *);
            Brush();
            virtual void use() const;
    };
}

