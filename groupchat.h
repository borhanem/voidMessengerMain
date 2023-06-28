#ifndef GROUPCHAT_H
#define GROUPCHAT_H

#include <QDialog>
#include "abstractchat.h"
namespace Ui {
class GroupChat;
}

class GroupChat : public QDialog , public AbstractChat
{
    Q_OBJECT

public:
    explicit GroupChat(QString chatName,const AbstractChat::ChatType& ct,User* user=nullptr,QWidget *parent = nullptr);
    ~GroupChat();
    int saveToFile() override;
    int loadFromFile() override;
private slots:
    void on_send_pbn_clicked();
    void success_on_send_message();
    void failure_on_send_message(QString Error);

private:
    Ui::GroupChat *ui;
};

#endif // GROUPCHAT_H