#pragma once

#include <QTabWidget>
#include <QFileInfo>
#include <QMap>
#include <QPointer>
#include <QTableWidgetItem>

#include "../files/fileselector.h"
#include "imagearea.h"

namespace ui {
    class ViewManager : public QObject {
        Q_OBJECT
        private:
            FileSelector * _selector;
            QTabWidget * _tabs;

        public:
            ViewManager() = delete;
            ViewManager(FileSelector *selector, QTabWidget * tabs);

            inline ImageArea * currentView() const {return dynamic_cast<ImageArea *>(this->_tabs->currentWidget());}
            inline QTabWidget * tabs() const {return this->_tabs;}
            inline FileSelector * fileselector() const {return this->_selector;}

            QVector<ImageArea *> areas() const;

        public slots:
            void newView();
            void newView(const QFileInfo &);

            void deleteCurrentView();
            void deleteView(const QFileInfo &);
            void deleteView(int);

            void changeView(int);

            void saveCurrentView();
            void saveView(int);

            void saveAsCurrentView();
            void saveAsView(int);

            void saveAll();

        signals:
            void createdView(ImageArea *);
            void changedView(ImageArea *);
            void deletedView(ImageArea *);
    };
}
