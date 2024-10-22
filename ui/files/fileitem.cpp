#include "fileitem.h"

FileItem::FileItem(const QString & path)
    : QListWidgetItem(path), _file(path) {}
