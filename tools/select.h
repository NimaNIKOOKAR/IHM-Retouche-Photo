#pragma once

#include "tool.h"

namespace tool {
    class Select : public Tool {
        public:
            Select(const QString &, const QIcon &);

            virtual void setup() const = 0;

        public slots:
            virtual void use() const final;

    };
}

