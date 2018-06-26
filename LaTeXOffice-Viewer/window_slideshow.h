#ifndef WINDOW_SLIDESHOW_H
#define WINDOW_SLIDESHOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QKeySequence>
#include "remotecontrolserver.h"
namespace Ui {
class Window_SlideShow;
}

class Window_SlideShow : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window_SlideShow(QString documentPath, RemoteControlServer *remoteControlServer, QWidget *parent = 0);
    ~Window_SlideShow();


private slots:
    void on_actionHide_triggered();

    void on_actionNext_Slide_triggered();

    void on_actionPrevious_Slide_triggered();

private:
    Ui::Window_SlideShow *ui;
};

#endif // DIALOG_SLIDESHOW_H
