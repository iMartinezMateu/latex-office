#include "remotecontrolserver.h"


RemoteControlServer::RemoteControlServer(QObject *parent) :
    QObject(parent)
{
    server = new QTcpServer(this);

    // whenever a user connects, it will emit signal
    connect(server, SIGNAL(newConnection()),
            this, SLOT(newConnection()));


    //Get LAN IP
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost))
             this->address = address;
    }

    if(!server->listen(address, 17215))
    {
        qDebug() << "[SERVER] Server could not start";
    }
    else
    {
        qDebug() << "[SERVER] Server started at port 17215 !";
    }
}

void RemoteControlServer::generatePin()
{
    int randomValue ;
    // Create seed for the random
    // That is needed only once on application startup
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    randomValue = (qrand() % (9999+1-1000)) + 1000; //A random number of 4 digits

    this->pinCode = QString::number(randomValue);
}

QString RemoteControlServer::getPin()
{
    return this->pinCode;
}

void RemoteControlServer::newConnection()
{
    // need to grab the socket
    socket = server->nextPendingConnection();

    socket->write("HELLO.\r\n");
    qDebug() << "[SERVER] HELLO.\r\n";
    socket->flush();
    socket->write("REQUEST_AUTH_PIN.\r\n");
    qDebug() << "[SERVER] REQUEST_AUTH_PIN.\r\n";
    socket->flush();

    socket->waitForBytesWritten(3000);

    if(socket)
      {
          connect(socket ,SIGNAL(readyRead()),this,SLOT(readFromClient()));

          //Additionnal auto clean-up without keeping track of the pointer
          connect(socket ,SIGNAL(disconnected()),socket ,SLOT(deleteLater()));
      }


}

void RemoteControlServer::readFromClient()
{
    if (socket)
    {
        QString message(socket->readAll());

        qDebug() << message;
        if (message.contains("AUTH_PIN"))
        {
            qDebug() << "[SERVER] Authenticating...";
            authenticate(message);
            if (viewer)
            {
                qDebug() << "[SERVER] Sending page image to client...";
                QImage page = viewer->getImages().at(viewer->getCurrentPage());
                QByteArray ba;
                QBuffer buffer(&ba);
                page.save(&buffer, "JPEG", IMAGE_QUALITY);
                socket->write(ba);
            }
            if (slideViewer)
            {
                qDebug() << "[SERVER] Sending slide image to client...";
                QImage slide = slideViewer->getImages().at(slideViewer->getCurrentPage());
                QByteArray ba;
                QBuffer buffer(&ba);
                slide.save(&buffer, "JPEG", IMAGE_QUALITY);
                socket->write(ba);

            }
        }

        else if (message.contains("PREVIOUS_SLIDE"))
        {
            if (viewer)
            {
                qDebug() << "[SERVER] Loading previous page...";
                viewer->showPreviousPage();
                qDebug() << "[SERVER] Sending page image to client...";
                QImage page = viewer->getImages().at(viewer->getCurrentPage());
                QByteArray ba;
                QBuffer buffer(&ba);
                page.save(&buffer, "JPEG", IMAGE_QUALITY);
                socket->write(ba);
            }
            if (slideViewer)
            {
                qDebug() << "[SERVER] Loading previous slide...";
                slideViewer->showPreviousPage();
                qDebug() << "[SERVER] Sending slide image to client...";
                QImage slide = slideViewer->getImages().at(slideViewer->getCurrentPage());
                QByteArray ba;
                QBuffer buffer(&ba);
                slide.save(&buffer, "JPEG", IMAGE_QUALITY);
                socket->write(ba);

            }
        }

        else if (message.contains("NEXT_SLIDE"))
        {
            if (viewer)
            {
                qDebug() << "[SERVER] Loading next page...";
                viewer->showNextPage();
                qDebug() << "[SERVER] Sending page image to client...";
                QImage page = viewer->getImages().at(viewer->getCurrentPage());
                QByteArray ba;
                QBuffer buffer(&ba);
                page.save(&buffer, "JPEG", IMAGE_QUALITY);
                socket->write(ba);

            }

            if (slideViewer)
            {
                qDebug() << "[SERVER] Loading next slide...";
                slideViewer->showNextPage();
                qDebug() << "[SERVER] Sending slide image to client...";
                QImage slide = slideViewer->getImages().at(slideViewer->getCurrentPage());
                QByteArray ba;
                QBuffer buffer(&ba);
                slide.save(&buffer, "JPEG", IMAGE_QUALITY);
                socket->write(ba);

            }
        }

        else if (message.contains("MAXIMIZE"))
        {
            if (viewer)
            {
                qDebug() << "[SERVER] Increasing page view zoom...";
                viewer->maximizeZoom();
            }
            if (slideViewer)
            {
                qDebug() << "[SERVER] Increasing slide view zoom...";
                slideViewer->maximizeZoom();
            }
        }

        else if (message.contains("MINIMIZE"))
        {
            if (viewer)
            {
                qDebug() << "[SERVER] Decreasing page view zoom...";
                viewer->minimizeZoom();
            }

            if (slideViewer)
            {
                qDebug() << "[SERVER] Decreasing slide view zoom...";
                slideViewer->minimizeZoom();
            }
        }

    }

}

void RemoteControlServer::authenticate(QString authPinMessage)
{
    authPinMessage = authPinMessage.remove("AUTH_PIN ");

    if (authPinMessage.compare(getPin())==0)
    {
       socket->write("GOOD_PIN.\r\n");
        qDebug() << "[SERVER] GOOD_PIN.\r\n";
       socket->flush();
    }
    else
    {
        socket->write("BAD_PIN.\r\n");
        qDebug() << "[SERVER] BAD_PIN.\r\n";
        socket->flush();
    }
}

QString RemoteControlServer::getIPAddress()
{
    return server->serverAddress().toString();
}

QString RemoteControlServer::getPort()
{
    return QString::number(server->serverPort());
}

void RemoteControlServer::close()
{
    server->close();
}

void RemoteControlServer::loadDocumentViewer(DocumentViewer* viewer)
{
    this->viewer = viewer;
}

void RemoteControlServer::loadDocumentSlideShow(DocumentSlideShow* viewer)
{
    this->slideViewer = viewer;
}

void RemoteControlServer::unloadDocumentViewer()
{
    this->viewer = NULL;
}

void RemoteControlServer::unloadDocumentSlideShow()
{
    this->slideViewer = NULL;
}
