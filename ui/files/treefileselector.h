#pragma once

#include "fileselector.h"

#include <QTreeView>
#include <QListWidget>
#include <QFileSystemModel>
#include <QPushButton>
#include <QDropEvent>

namespace ui {
    class TreeFileSelector : public FileSelector {
        Q_OBJECT
        private:
            QTreeView * _tree;
            QListWidget * _selected;
            QPushButton * _button_add;
            QPushButton * _button_remove;

            QFileSystemModel _model;
            QVector<QFileInfo> _items;

        public:
            TreeFileSelector() = delete;
            TreeFileSelector(QTreeView *, QListWidget *,QWidget * parent = nullptr);

            inline const QTreeView * getTree() const {return this->_tree;}
            inline const QListWidget * getSelected() const {return this->_selected;}
            inline const QPushButton * getAddPushButton() const {return this->_button_add;}
            inline const QPushButton * getRemovePushButton() const {return this->_button_remove;}
            inline const QFileSystemModel & getFileSystemModel() const {return this->_model;}
            inline const QVector<QFileInfo> & getSelectedItems() const {return this->_items;}

            QFileInfo getSelectedFile(unsigned int index) const;

            virtual void onDrop(QDropEvent * e);

        protected slots:
            void addItem(const QFileInfo &);
            void addItem(const QString & path);
            void addItem(const QModelIndex & index);

            void removeItem(const QModelIndex & index);
            void setTreeRootPath(const QString &);

        public slots:
            virtual void pushItem() final;
            virtual void removeSelectedItem() final;
            virtual void select(const QModelIndex &) final;

            virtual void setTreeRootPath() final;
    };
}
