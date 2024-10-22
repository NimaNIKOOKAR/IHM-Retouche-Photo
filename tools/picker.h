#pragma once

#include "editable.h"

namespace tool {
    class Picker : public Editable  {
        Q_OBJECT
        public:
            Picker(const ColorPickerWidget &);
            virtual ~Picker();

            virtual void onMousePressed(ui::ImageArea &, QImage &, const QPoint &, const ui::Selection &, const QMouseEvent &, const ColorPickerWidget &);
            virtual void onMouseReleased(ui::ImageArea &, QImage &, const QPoint &, const ui::Selection &, const QMouseEvent &, const ColorPickerWidget &);
            virtual void onMouseMoved(ui::ImageArea &, QImage &, const QPoint &, const ui::Selection &, const QMouseEvent &, const ColorPickerWidget &, bool);

        signals:
            void colorPicked(const QColor &);


    };
}
