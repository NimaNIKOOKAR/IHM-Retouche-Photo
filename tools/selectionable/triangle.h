#pragma once

#include "../selectionnable.h"

namespace tool {
    class Triangle : public Selectionable {
        private:
            QPoint _clicked;
            bool _hold;
            bool _multy;

        public:
            Triangle(const ColorPickerWidget &);

            virtual void onMousePressed(ui::ImageArea &, ui::Selection &, const QPoint &, const QImage &, const QMouseEvent &, const ColorPickerWidget &);
            virtual void onMouseReleased(ui::ImageArea &, ui::Selection &, const QPoint &, const QImage &, const QMouseEvent &, const ColorPickerWidget &);
            virtual void onMouseMoved(ui::ImageArea &, ui::Selection &, const QPoint &, const QImage &, const QMouseEvent &, const ColorPickerWidget &, bool);

            virtual void onKeyPress(ui::ImageArea &, ui::Selection &, const QPoint &, const QImage &, const QKeyEvent &, const ColorPickerWidget &);
            virtual void onKeyReleased(ui::ImageArea &, ui::Selection &, const QPoint &, const QImage &, const QKeyEvent &, const ColorPickerWidget &);
    };
}
