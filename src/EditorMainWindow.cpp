#include "EditorMainWindow.h"
#include "ui_EditorMainWindow.h"

EditorMainWindow::EditorMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EditorMainWindow)
{
    ui->setupUi(this);
}

EditorMainWindow::~EditorMainWindow()
{
    delete ui;
}
