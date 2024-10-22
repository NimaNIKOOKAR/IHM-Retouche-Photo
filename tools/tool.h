#pragma once

#include <QListWidgetItem>
#include <QObject>
#include <QCursor>
#include <QDialog>

#include "../ui/view/imagearea.h"

namespace tool {
    class Tool : public QObject, public QListWidgetItem {
        Q_OBJECT
        private:
            QDialog * _configurationDialog;

        public:
            Tool(const QString &, const QIcon &);

            virtual inline Qt::CursorShape shape() const {return Qt::CursorShape::ArrowCursor;}

            inline bool HaveConfigurationDialog() const {return this->_configurationDialog != nullptr;}
            inline QDialog * configurationDialog() const {return this->_configurationDialog;}

            inline void setCongigurationDialog(QDialog * dial) {this->_configurationDialog = dial;}

            virtual void initialize(ui::ImageArea *) = 0;


        public slots:
            virtual void pressed(ui::ImageArea &, QImage &, QPoint &, ui::Selection &, QMouseEvent &) = 0;
            virtual void released(ui::ImageArea &, QImage &, QPoint &, ui::Selection &, QMouseEvent &) = 0;
            virtual void moved(ui::ImageArea &, QImage &, QPoint &, ui::Selection &, QMouseEvent &, bool) = 0;

            virtual void keyPressed(ui::ImageArea &, QImage &, QPoint &, ui::Selection &, QKeyEvent &) = 0;
            virtual void keyReleased(ui::ImageArea &, QImage &, QPoint &, ui::Selection &, QKeyEvent &) = 0;

            virtual void selectionCleared() = 0;

            void showConfiguration();

    };
}
