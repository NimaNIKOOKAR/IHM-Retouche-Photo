#pragma once

#include "../editable.h"

namespace tool {
    class Bucket : public Editable {
        public:
            Bucket(const ColorPickerWidget &);

            virtual void onMousePressed(ui::ImageArea &, QImage &, const QPoint &, const ui::Selection &, const QMouseEvent &, const ColorPickerWidget &);
            virtual void onMouseReleased(ui::ImageArea &, QImage &, const QPoint &, const ui::Selection &, const QMouseEvent &, const ColorPickerWidget &);
            virtual void onMouseMoved(ui::ImageArea &, QImage &, const QPoint &, const ui::Selection &, const QMouseEvent &, const ColorPickerWidget &, bool);

            virtual void onKeyReleased(ui::ImageArea &, QImage &, const QPoint &, const ui::Selection &, const QKeyEvent &, const ColorPickerWidget &);
            virtual void fill(ui::ImageArea &, QImage &, const QPoint &, const ui::Selection &, const QColor &);
    };
}
