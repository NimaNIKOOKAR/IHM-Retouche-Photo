#include "pixelpainter.h"

namespace tool {
    Pixelpainter::Pixelpainter(const ColorPickerWidget & cp)
    : Editable(cp, "Crayon", QIcon(":/oxygen/16x16/ressource/image/oxygen/icons/16x16/draw-freehand.png")),
      _config(new dialog::SizeDialog("Paramètre du crayon", "Taille du crayon", 1, 2048, 4,  "pixels")), _leftButton(false) {
        this->setCongigurationDialog(this->_config.get());
    }

    void Pixelpainter::onMousePressed(ui::ImageArea &, QImage &, const QPoint &, const ui::Selection &, const QMouseEvent & e, const ColorPickerWidget &) {
        if(e.button() == Qt::LeftButton) {
            this->_leftButton = true;
        }
    }

    void Pixelpainter::onMouseReleased(ui::ImageArea &, QImage &, const QPoint &, const ui::Selection &, const QMouseEvent & e, const ColorPickerWidget &) {
        if(e.button() == Qt::LeftButton) {
            this->_leftButton = false;
        }
    }

    void Pixelpainter::onMouseMoved(ui::ImageArea & area, QImage & img, const QPoint & c, const ui::Selection & s, const QMouseEvent &, const ColorPickerWidget & cp, bool hold) {
        if(this->_leftButton && hold) {
            this->paint(area, img, c, s, cp);
        }
    }

    void Pixelpainter::onKeyReleased(ui::ImageArea & area, QImage & img, const QPoint & click, const ui::Selection & selection, const QKeyEvent & e, const ColorPickerWidget & cp) {
        if(e.key() == Qt::Key_Return) {
            this->paint(area, img, click, selection, cp);
        }
    }

    void Pixelpainter::paint(ui::ImageArea & area, QImage & img, const QPoint & c, const ui::Selection & s, const ColorPickerWidget & cp) {
        int cx = c.x();
        int cy = c.y();

        int size = this->_config->value();

        QColor color = cp.currentColor();

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
