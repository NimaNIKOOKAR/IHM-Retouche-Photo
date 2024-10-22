#include "pixelEraiser.h"

namespace tool {
    Pixeleraiser::Pixeleraiser(const ColorPickerWidget & cp)
    : Editable(cp, "Gomme", QIcon(":/oxygen/16x16/ressource/image/oxygen/icons/16x16/draw-eraser.png")),
      _config(new dialog::SizeDialog("Paramètre de la gomme", "Taille de la gomme", 1, 2048, 4, "pixels")), _leftButton(false), _rightButton(false) {
        this->setCongigurationDialog(this->_config.get());
    }

    void Pixeleraiser::onMousePressed(ui::ImageArea &, QImage &, const QPoint &, const ui::Selection &, const QMouseEvent & e, const ColorPickerWidget &) {
        if(e.button() == Qt::LeftButton) {
            this->_leftButton = true;
        }

        if(e.button() == Qt::RightButton) {
            this->_rightButton = true;
        }
    }

    void Pixeleraiser::onMouseReleased(ui::ImageArea &, QImage &, const QPoint &, const ui::Selection &, const QMouseEvent & e, const ColorPickerWidget &) {
        if(e.button() == Qt::LeftButton) {
            this->_leftButton = false;
        }

        if(e.button() == Qt::RightButton) {
            this->_rightButton = false;
        }
    }

    void Pixeleraiser::onMouseMoved(ui::ImageArea & area, QImage & img, const QPoint & c, const ui::Selection & s, const QMouseEvent &, const ColorPickerWidget &, bool hold) {
        if(hold) {
            if(this->_leftButton || this->_rightButton) {
                this->eraise(area, img, c, s);
            }
        }
    }

    void Pixeleraiser::onKeyReleased(ui::ImageArea & area, QImage & img, const QPoint & click, const ui::Selection & selection, const QKeyEvent & e, const ColorPickerWidget &) {
        if(e.key() == Qt::Key_Return) {
            this->eraise(area, img, click, selection);
        }
    }

    void Pixeleraiser::eraise(ui::ImageArea & area, QImage & img, const QPoint & c, const ui::Selection & s) {
        int cx = c.x();
        int cy = c.y();

        int size = this->_config->value();

        QColor color = img.format() == QImage::Format_RGBA32FPx4 ? QColor(0, 0, 0, 0) : QColorConstants::White;

        if(color.isValid()) {
            for(int i = 0; i < size; i++) {
                int dx = i - size / 2;
                int x = cx + dx;

                int h = qRound(size * qSqrt(size * size / 4.0 - dx * dx) /size);
                for(int dy = 1; dy < h; dy++) {
                    QPoint p(x, cy + dy);
                    if(img.rect().contains(p)) {
                        if(s.empty()) {
                            area.setColor(p, color);
                        }
                        else if(s.contain(p)) {
                            area.setColor(p, color);
                        }
                    }

                    p = QPoint(x, cy - dy);
                    if(img.rect().contains(p)) {
                        if(s.empty()) {
                            area.setColor(p, color);
                        }
                        else if(s.contain(p)) {
                            area.setColor(p, color);
                        }
                    }
                }

                if(h >= 0) {
                    QPoint p(x, cy);
                    if(img.rect().contains(p)) {
                        if(s.empty()) {
                            area.setColor(p, color);
                        }
                        else if(s.contain(p)) {
                            area.setColor(p, color);
                        }
                    }
                }
            }
        }
    }
}
