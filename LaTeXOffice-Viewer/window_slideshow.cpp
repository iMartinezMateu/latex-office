#include "window_slideshow.h"
#include "ui_window_slideshow.h"
Window_SlideShow::Window_SlideShow(QString documentPath, RemoteControlServer *remoteControlServer, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window_SlideShow)
{
    ui->setupUi(this);
    this->setWindowFlags( Qt::WindowStaysOnTopHint  );

    this->showFullScreen();
    this->setMinimumSize(this->geometry().size());
    this->setMaximumSize(this->geometry().size());
    ui->actionHide->setShortcut(Qt::Key_Escape);
    ui->actionHide->setShortcutContext(Qt::WindowShortcut);
    connect(ui->actionHide,SIGNAL(triggered()),this,SLOT(on_actionHide_triggered()));
    setContextMenuPolicy(Qt::ActionsContextMenu);
    ui->actionHide->setEnabled(true);

    ui->slideShowViewer->loadDocument(documentPath);
    remoteControlServer->loadDocumentSlideShow(ui->slideShowViewer);

}

Window_SlideShow::~Window_SlideShow()
{
    delete ui;
}

void Window_SlideShow::on_actionHide_triggered()
{
    this->showNormal();
    close();
}

void Window_SlideShow::on_actionNext_Slide_triggered()
{
    ui->slideShowViewer->showNextPage();
}

void Window_SlideShow::on_actionPrevious_Slide_triggered()
{
    ui->slideShowViewer->showPreviousPage();
}
