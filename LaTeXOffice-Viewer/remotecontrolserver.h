#ifndef REMOTECONTROLSERVER_H
#define REMOTECONTROLSERVER_H


#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QDebug>
#include <QNetworkInterface>
#include <QTime>
#include <QBuffer>
#include "documentviewer.h"
#include "documentslideshow.h"


class RemoteControlServer : public QObject
{
    Q_OBJECT
public:
    /**
      @brief This is the constructor function that must be called in order to create the corresponding dialog.
      @param parent The UI widget that becomes the parent of this dialog.
      @returns This is a void function.
      */
    explicit RemoteControlServer(QObject *parent = 0);
    /**
      @brief This function loads the Document Viewer reference.
      @param viewer the widget reference.
      @returns This is a void function.
      */
    void loadDocumentViewer(DocumentViewer* viewer);
    /**
      @brief This function loads the Document SlideShow reference.
      @param viewer the widget reference.
      @returns This is a void function.
      */
    void loadDocumentSlideShow(DocumentSlideShow* viewer);
    /**
      @brief This function unloads the Document Viewer reference.
      @returns This is a void function.
      */
    void unloadDocumentViewer();
    /**
      @brief This function unloads the Document SlideShow reference.
      @returns This is a void function.
      */
    void unloadDocumentSlideShow();
    /**
      @brief This function returns the server IP address. This direction must be supplied to a client.
      @returns This function returns the server IP address
      */
    QString getIPAddress();
    /**
      @brief This function returns the server IP port.
      @returns This function returns the server IP port.
      */
    QString getPort();
    /**
      @brief This function generate a random PIN so it provides a authentication system with the client to prevent unauthorized access.
      @returns This is a void function.
      */
    void generatePin();
    /**
      @brief This function returns the authentication pin code.
      @returns This function returns the pin code.
      */
    QString getPin();
    /**
      @brief This function starts the authentication between the server and the client using a pin code.
      @param authPinMessage the pin message sent from the client.
      @returns This is a void function.
      */
    void authenticate(QString authPinMessage);
    /**
      @brief This function closes all server connections.
      @returns This function returns the pin code.
      */
    void close();

signals:

public slots:
    void newConnection();
    void readFromClient();

private:
    QTcpServer *server;
    QHostAddress address;
    QString pinCode;
    QTcpSocket *socket ;
    DocumentViewer* viewer=NULL;
    DocumentSlideShow* slideViewer=NULL;
    const int IMAGE_QUALITY=7;

};

#endif // REMOTECONTROLSERVER_H
