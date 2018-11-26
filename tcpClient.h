#pragma once

#include <QtWidgets/QWidget>
#include <QTcpSocket>
#include <QPushButton>
#include <QTextEdit>

class tcpClient : public QWidget
{
    Q_OBJECT

public:
    explicit tcpClient(QWidget *parent = Q_NULLPTR);

    void initClient();


    virtual QSize sizeHint() const override;

public slots:
    void SendMessage(const QString& message);

private:
    int m_port;
    QPushButton *m_button;
    QTextEdit   *m_textEdit;
    QTcpSocket  * m_socket;
};
