#include "Brush.h"

#include "../../dialog/sizedialog.h"

namespace tool {
    Brush::Brush(const ColorPickerWidget & cp)
    : Editable(cp, "Brosse", QIcon(":/oxygen/16x16/ressource/image/oxygen/icons/16x16/document-sign.png")),
    _config(new dialog::SizeDialog("Paramètre de la Brosse", "Taille de la brosse", 1, 255, 4)) {
        this->setCongigurationDialog(this->_config.get());
        QObject::connect(&cp, SIGNAL(currentColorChange(QColor)), this, SLOT(changeColor(QColor)));
    }

    void Brush::onMousePressed(ui::ImageArea &, QImage &, const QPoint &, const ui::Selection &, const QMouseEvent & e, const ColorPickerWidget & cp) {
        if(e.button() == Qt::LeftButton) {
            this->_leftButton = true;
        }
    }

    void Brush::onMouseReleased(ui::ImageArea &, QImage &, const QPoint &, const ui::Selection &, const QMouseEvent & e, const ColorPickerWidget &) {
        if(e.button() == Qt::LeftButton) {
            this->_leftButton = false;
        }
    }

    void Brush::onMouseMoved(ui::ImageArea & area, QImage & img, const QPoint & c, const ui::Selection & s, const QMouseEvent &, const ColorPickerWidget & cp, bool hold) {
        if(this->_leftButton && hold) {
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
                            if(!s.empty() && s.contain(p)) {
                                area.setColor(p, color);
                            }
                            else {
                                area.setColor(p, color);
                            }
                        }

                        p = QPoint(x, cy - dy);
                        if(img.rect().contains(p)) {
                            if(!s.empty() && s.contain(p)) {
                                area.setColor(p, color);
                            }
                            else {
                                area.setColor(p, color);
                            }
                        }
                    }

                    if(h >= 0) {
                        QPoint p(x, cy);
                        if(img.rect().contains(p)) {
                            if(!s.empty() && s.contain(p)) {
                                area.setColor(p, color);
                            }
                            else {
                                area.setColor(p, color);
                            }
                        }
                    }
                }
            }
        }
    }
}
