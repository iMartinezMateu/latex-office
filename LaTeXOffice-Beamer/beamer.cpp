#include "beamer.h"
#include "ui_beamer.h"

Beamer::Beamer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Beamer)
{
    ui->setupUi(this);
}

Beamer::~Beamer()
{
    delete ui;
}
