#pragma once

#include "../editable.h"

#include <dialog/sizedialog.h>

namespace tool {
    class Pixeleraiser : public Editable {
        private:
            QSharedPointer<dialog::SizeDialog> _config;
            bool _leftButton;
            bool _rightButton;

        public:
            Pixeleraiser(const ColorPickerWidget &);

            virtual void onMousePressed(ui::ImageArea &, QImage &, const QPoint &, const ui::Selection &, const QMouseEvent &, const ColorPickerWidget &);
            virtual void onMouseReleased(ui::ImageArea &, QImage &, const QPoint &, const ui::Selection &, const QMouseEvent &, const ColorPickerWidget &);
            virtual void onMouseMoved(ui::ImageArea &, QImage &, const QPoint &, const ui::Selection &, const QMouseEvent &, const ColorPickerWidget &, bool);

            virtual void onKeyReleased(ui::ImageArea &, QImage &, const QPoint &, const ui::Selection &, const QKeyEvent &, const ColorPickerWidget &);

            virtual void eraise(ui::ImageArea &, QImage &, const QPoint &, const ui::Selection &);
    };
}
