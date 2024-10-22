#include "contrast.h"

#include <QDebug>

namespace effect {
    Contrast::Contrast(float brightnessFactor, float contrastFactor)
    : _brightnessFactor(brightnessFactor), _contrastFactor(contrastFactor) {}

    Contrast::~Contrast() {}

    void Contrast::apply(const QSet<QPoint> & points, QImage & image) const {
        for(auto & point : points) {
            QColor pixelColor = image.pixelColor(point);

            int adjustedRed = qBound(0, static_cast<int>(pixelColor.red() * this->_brightnessFactor * this->_contrastFactor), 255);
            int adjustedGreen = qBound(0, static_cast<int>(pixelColor.green() * this->_brightnessFactor * this->_contrastFactor), 255);
            int adjustedBlue = qBound(0, static_cast<int>(pixelColor.blue() * this->_brightnessFactor * this->_contrastFactor), 255);

            image.setPixelColor(point, QColor(adjustedRed, adjustedGreen, adjustedBlue));
        }

        qDebug() << "Ajustement de la luminosité et du contraste effectué.";
    }
}
