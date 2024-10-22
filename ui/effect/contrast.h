#pragma once

#include "effect.h"

namespace effect {
    class Contrast : public Effect {
        private:
            float _brightnessFactor;
            float _contrastFactor;

        public:
            Contrast(float brightnessFactor, float contrastFactor);
   virtual ~Contrast();

            virtual void apply(const QSet<QPoint> &, QImage &) const;
    };
}

