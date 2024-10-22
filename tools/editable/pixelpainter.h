#pragma once

#include "../editable.h"

#include <dialog/sizedialog.h>

namespace tool {
    class Pixelpainter : public Editable {
        private:
            QSharedPointer<dialog::SizeDialog> _config;
            bool _leftButton;

        public:
            Pixelpainter(const ColorPickerWidget &);

            virtual void onMousePressed(ui::ImageArea &, QImage &, const QPoint &, const ui::Selection &, const QMouseEvent &, const ColorPickerWidget &);
            virtual void onMouseReleased(ui::ImageArea &, QImage &, const QPoint &, const ui::Selection &, const QMouseEvent &, const ColorPickerWidget &);
            virtual void onMouseMoved(ui::ImageArea &, QImage &, const QPoint &, const ui::Selection &, const QMouseEvent &, const ColorPickerWidget &, bool);

            virtual void onKeyReleased(ui::ImageArea &, QImage &, const QPoint &, const ui::Selection &, const QKeyEvent &, const ColorPickerWidget &);

            virtual void paint(ui::ImageArea &, QImage &, const QPoint &, const ui::Selection &, const ColorPickerWidget &);
    };
}
