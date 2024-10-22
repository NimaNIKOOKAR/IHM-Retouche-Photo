#pragma once

#include <QListWidgetItem>
#include <QFile>

class FileItem : public QListWidgetItem {
    private:
        const QFile _file;

    public:
        FileItem() = delete;
        FileItem(const QString & path);

        inline const QFile & file() const {return this->_file;}
};

