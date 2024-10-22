#include "tool.h"

namespace tool {
    Tool::Tool(const QString & name, const QIcon & icon)
    : QListWidgetItem(), _configurationDialog(nullptr) {
        this->setText(name);
        this->setIcon(icon);
    }

    void Tool::showConfiguration() {
        if(this->_configurationDialog != nullptr) {
            this->_configurationDialog->exec();
        }
    }
}
