#pragma once

#include <QObject>
#include <QDropEvent>
#include <QFileInfo>

namespace ui {
    class FileSelector : public QObject {
        Q_OBJECT
        public:
            virtual void onDrop(QDropEvent * e) = 0;

        public slots:
            virtual void pushItem() = 0;
            virtual void removeSelectedItem() = 0;
            virtual void select(const QModelIndex &) = 0;

            virtual void setTreeRootPath() = 0;

        signals:
            void insterItem(const QFileInfo &);
            void selectItem(const QFileInfo &);
            void dropItem(const QFileInfo &);
    };
}
