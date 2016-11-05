#ifndef EDITORMAINWINDOW_H
#define EDITORMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class EditorMainWindow;
}

class EditorMainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit EditorMainWindow(QWidget *parent = 0);
    ~EditorMainWindow();
    
private:
    Ui::EditorMainWindow *ui;
};

#endif // EDITORMAINWINDOW_H
