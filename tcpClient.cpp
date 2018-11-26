#include "tcpClient.h"
#include <QHostAddress>
#include <QDebug>
#include <QString>
#include <QPushButton>
#include <QHBoxLayout>

tcpClient::tcpClient(QWidget *parent)
    : QWidget(parent),
    m_port(666)
{
    auto *layout = new QHBoxLayout(this);
    m_button = new QPushButton("Send message", this);
    m_textEdit = new QTextEdit("Write message here...", this);
    //m_button->setFixedSize(width(), height()/4);
    layout->addWidget(m_button);
    layout->addWidget(m_textEdit);

    initClient();
}

void tcpClient::initClient()
{
    m_socket = new QTcpSocket(this);

    connect(m_button, &QPushButton::clicked, [this]() {
        SendMessage(m_textEdit->toPlainText());
    });
    connect(m_textEdit, &QTextEdit::cursorPositionChanged, [this]() {
        qDebug() << "Change text";
    });

    m_socket->connectToHost(QHostAddress::LocalHost, m_port);

    const int TIME_TO_WAIT_MS = 3000;

    m_socket->waitForConnected(TIME_TO_WAIT_MS);

    if (m_socket->state() != QTcpSocket::ConnectedState)
    {
        qDebug() << "Failed to connect to port: " << QString::number(m_port);
        return;
    }
    else
    {
        qDebug() << "Successfully connected to port: " << QString::number(m_port);
    }

    m_socket->waitForReadyRead();
    QByteArray readData = m_socket->readAll();
    qDebug() << "Client received the data: " << readData;

    //m_socket->close();
}

QSize tcpClient::sizeHint() const
{
    return { 400, 100 };
}

void tcpClient::SendMessage(const QString& message)
{
    QByteArray writeData = message.toLocal8Bit();
    m_socket->write(writeData);
    m_socket->flush();

    const int TIME_WAIT_MS = 3000;
    m_socket->waitForBytesWritten(TIME_WAIT_MS);
}
