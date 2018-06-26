#ifndef BEAMER_H
#define BEAMER_H

#include <QMainWindow>

namespace Ui {
class Beamer;
}

class Beamer : public QMainWindow
{
    Q_OBJECT

public:
    explicit Beamer(QWidget *parent = 0);
    ~Beamer();

private:
    Ui::Beamer *ui;
};

#endif // BEAMER_H
