#include "effect.h"

namespace effect {
    void Effect::use(const ui::Selection & selection, QImage & image) const {
        QSet<QPoint> pixels;
        if(selection.empty()) {
            for(int x = 0; x < image.width(); x++) {
                for(int y = 0; y < image.height(); y++) {
                    pixels.insert(QPoint(x,y));
                }
            }
        }
        else {
            pixels = selection.selection();
        }
        this->apply(pixels, image);
    }
}
