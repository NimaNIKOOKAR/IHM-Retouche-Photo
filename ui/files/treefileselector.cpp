#include "treefileselector.h"

#include <QHeaderView>
#include <QFileIconProvider>
#include <QStandardPaths>
#include <QListWidgetItem>
#include <QFileDialog>
#include <QMimeData>

namespace ui {
    TreeFileSelector::TreeFileSelector(QTreeView * tree, QListWidget * list, QWidget * parent)
    : _tree(tree), _selected(list), _model(parent) {
        QStringList filters;
        filters.append("*.png");
        filters.append("*.jpg");
        filters.append("*.gif");

        this->_model.setNameFilters(filters);
        this->_model.setReadOnly(true);
        this->_model.setFilter(QDir::AllDirs | QDir::AllEntries |QDir::NoDotAndDotDot);

        this->_tree->setModel(&this->_model);
        this->_tree->setRootIndex(this->_model.setRootPath(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation)));

        this->_tree->header()->hideSection(1);
        this->_tree->header()->hideSection(2);
        this->_tree->header()->hideSection(3);
        this->_tree->setHeaderHidden(true);
        //this->_tree->setSortingEnabled(true);

        QObject::connect(this->_tree, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(addItem(QModelIndex)));
        QObject::connect(this->_selected, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(select(QModelIndex)));
    }

    void TreeFileSelector::onDrop(QDropEvent * e) {
        if(e->mimeData()->hasUrls()) {
            for(auto & url :  e->mimeData()->urls()) {
                QFileInfo info(url.toLocalFile());
                if(info.isDir()) {
                    this->setTreeRootPath(info.absoluteFilePath());
                }
                else if(info.isFile()) {
                    this->addItem(info);
                }
            }
        }
    }

    void TreeFileSelector::addItem(const QFileInfo & info) {
        if(info.isFile()) {
            /*if(info.suffix() == "png") {
                qDebug() << "png";
            }*/
            QFileIconProvider iconProvider;
            emit this->insterItem(info);
            this->_items.push_back(info);
            this->_selected->addItem(new QListWidgetItem(iconProvider.icon(info), info.fileName()));
        }
    }

    void TreeFileSelector::addItem(const QString & path) {
        this->addItem(QFileInfo(path));
    }

    void TreeFileSelector::addItem(const QModelIndex & index) {
        QFileInfo info = this->_model.fileInfo(index);
        this->addItem(info);
    }

    void TreeFileSelector::pushItem() {
        QFileDialog dialog;
        dialog.setFileMode(QFileDialog::ExistingFiles);
        dialog.setViewMode(QFileDialog::Detail);

        if(dialog.exec()) {
            for(auto & path : dialog.selectedFiles()) {
                this->addItem(path);
            }
        }
    }

    void TreeFileSelector::removeItem(const QModelIndex & index) {
        QFileInfo info = this->_model.fileInfo(index);
        if(info.isFile()) {
            for(qsizetype i = 0; i < this->_items.size(); i++) {
                if(this->_items.at(i).absoluteFilePath() == info.absoluteFilePath()) {
                    emit this->dropItem(info);
                    this->_items.removeAt(i);
                    this->_selected->takeItem(i);
                }
            }
        }
    }

    void TreeFileSelector::removeSelectedItem() {
        QList<QListWidgetItem *> selected = this->_selected->selectedItems();
        for(auto * item : selected) {
            int row = this->_selected->row(item);
            emit this->dropItem(this->_items.at(row));
            this->_selected->takeItem(row);
            this->_items.removeAt(row);
        }
    }

    void TreeFileSelector::select(const QModelIndex &) {
        QList<QListWidgetItem *> selected = this->_selected->selectedItems();
        for(auto * item : selected) {
            int row = this->_selected->row(item);
            emit this->selectItem(this->_items.at(row));
        }
    }

    void TreeFileSelector::setTreeRootPath(const QString & path) {
        this->_tree->setRootIndex(this->_model.setRootPath(path));
    }

    void TreeFileSelector::setTreeRootPath() {
        QFileDialog dialog;
        dialog.setFileMode(QFileDialog::Directory);
        dialog.setViewMode(QFileDialog::Detail);

        if(dialog.exec()) {
            QFileInfo info(dialog.selectedFiles().at(0));
            if(info.isDir()) {
                this->setTreeRootPath(info.absoluteFilePath());
            }
        }
    }
}
