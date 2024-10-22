#pragma once

#include <QColorDialog>
#include <QListWidget>
#include <QListWidgetItem>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

class ColorPickerWidget : public QWidget {
    Q_OBJECT
    private:
        QColor _currentColor;

        QVBoxLayout * _mainLayout;
        QHBoxLayout * _currentColorLayout;

        QListWidget * _colorListWidget;

        QLabel * _currentColorLabel;
        QFrame * _currentColorFrame;

        QPushButton * _addColorButton;
        QPushButton * _modifyColorButton;
        QPushButton * _chooseColorButton;
        QPushButton * _eraseColorButton;
        QPushButton * _duplicateColorButton;

    protected:
        void setFrameColor(const QColor &);

    public:
        ColorPickerWidget(QWidget *parent = nullptr);
       ~ColorPickerWidget();

        inline QColor currentColor() const {return this->_currentColor;}
        void setCurrentColor(const QColor &);


    private slots:
        void addColor();
        void addColor(const QColor &);
        void eraseColor();
        void eraseColor(const QColor &);
        void eraseSelectedColor();
        void modifyColor();
        void modifyColor(QListWidgetItem*);
        void chooseColor();
        void chooseColor(QListWidgetItem*);

        void duplicateCurrent();

    signals:
        void currentColorChange(const QColor &);
};
