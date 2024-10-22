#pragma once

#include "editable.h"

namespace tool {
    class Hand : public Editable  {
        private:
            bool _leftButton;

        public:
            Hand(const ColorPickerWidget &);

            inline virtual Qt::CursorShape shape() const {return Qt::CursorShape::OpenHandCursor;}

            virtual void onMousePressed(ui::ImageArea &, QImage &, const QPoint &, const ui::Selection &, const QMouseEvent &, const ColorPickerWidget &);
            virtual void onMouseReleased(ui::ImageArea &, QImage &, const QPoint &, const ui::Selection &, const QMouseEvent &, const ColorPickerWidget &);
            virtual void onMouseMoved(ui::ImageArea &, QImage &, const QPoint &, const ui::Selection &, const QMouseEvent &, const ColorPickerWidget &, bool);
    };
}
