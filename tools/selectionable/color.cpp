#include "color.h"

namespace tool {
    Color::Color(const ColorPickerWidget & cp)
    : Selectionable(cp, "Couleur", QIcon(":/oxygen/16x16/ressource/image/oxygen/icons/16x16/preferences-activities.png"), true),
    _config(new dialog::SizeDialog("Paramètre  de la séléction par couleur", "Proximité de la couleur", 0, 255, 16, "Units")),_lastClicked(-1,-1), _ctrl(false) {
        this->setCongigurationDialog(this->_config.get());

    }

    void Color::onMousePressed(ui::ImageArea &, ui::Selection & s, const QPoint & c, const QImage & i, const QMouseEvent & e, const ColorPickerWidget &) {
        if(!this->_ctrl || e.button() == Qt::RightButton) {
            s.clear();
        }

        if(e.button() == Qt::LeftButton) {
            this->select(s, c, i);
        }
    }

    void Color::onMouseReleased(ui::ImageArea &, ui::Selection &, const QPoint &, const QImage &, const QMouseEvent &, const ColorPickerWidget &) {

    }

    void Color::onMouseMoved(ui::ImageArea &, ui::Selection &, const QPoint &, const QImage &, const QMouseEvent &, const ColorPickerWidget &, bool) {

    }

    void Color::onKeyPress(ui::ImageArea &, ui::Selection & s, const QPoint & c, const QImage & i, const QKeyEvent & e, const ColorPickerWidget &) {
        if(e.key() == Qt::Key_Control) {
            this->_ctrl = true;
        }

        if(e.key() == Qt::Key_Return) {
            this->select(s, c, i);
        }
    }

    void Color::onKeyReleased(ui::ImageArea &, ui::Selection &, const QPoint &, const QImage &, const QKeyEvent & e, const ColorPickerWidget &) {
        if(e.key() == Qt::Key_Control) {
            this->_ctrl = false;
        }
    }

    void Color::select(ui::Selection & s, const QPoint & c, const QImage & img) {
        this->_lastClicked = c;
        QColor color = img.pixelColor(c);
        int prox = this->_config->value();
        for(int x = 0; x < img.width(); x++) {
            for(int y = 0; y < img.height(); y++) {
                QPoint p = QPoint(x, y);
                if(img.rect().contains(p)) {
                    QColor iColor = img.pixelColor(p);

                    if(iColor.red() < (color.red() + prox) && iColor.red() >= (color.red() - prox)
                        && iColor.green() < (color.green() + prox) && iColor.green() >= (color.green() - prox)
                        && iColor.blue() < (color.blue() + prox) && iColor.blue() >= (color.blue() - prox)) {
                        s.select(p);
                    }
                }
            }
        }
    }
}
