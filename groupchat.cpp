#include "groupchat.h"
#include "ui_groupchat.h"
#include "msgBaseReceive.h"
#include "msgBaseSend.h"
#include "controllerrefresher.h"
#include "workerrefresher.h"
GroupChat::GroupChat(QString chatName,QWidget *parent) :
    QDialog(nullptr),
    AbstractChat(chatName,AbstractChat::Group),
    ui(new Ui::GroupChat),
    controller(new ControllerRefresher(WorkerRefresher::MSGList,User::Group,0,this->mp_user->getUserName(),chatName,this))
{
    setWindowFlags(Qt::FramelessWindowHint);
    ui->setupUi(this);
    ui->sendResult_lbl->clear();
    ui->send_pbn->setDefault(true);
    ui->groupname_led->setDisabled(true);
    ui->groupname_led->setText(this->m_chat_name);
    this->setWindowTitle(this->m_chat_name);
    ui->group_scroll_area->setWidget(ui->scrollAreaWidgetContents);
    messagesLayout = new QVBoxLayout(ui->scrollAreaWidgetContents);
    ui->scrollAreaWidgetContents->setLayout(messagesLayout);
    messagesLayout->setAlignment(Qt::AlignTop);
    connect(mp_user,&User::SuccessOnSendMessage,this,&GroupChat::success_on_send_message);
    connect(mp_user,&User::Failure,this,&GroupChat::failure_on_send_message);
    //connect(mp_user,&User::SuccessOnGetMessage,this,&GroupChat::Refresh_handler);
    connect(mp_user,&User::FailureOnGetMessage,this,&GroupChat::failure_on_send_message);
    connect(controller,&ControllerRefresher::msgResultReady,this,&GroupChat::Refresh_handler);
    this->loadFromFile();
    /* ---show all messages---
    for(auto&i : this->m_message_list)
    {
        ui->message_lstwdgt->addItem(i.body());
    }
    *
    */
    controller->setPreSize(this->m_message_list.size());
    controller->operate();
}


GroupChat::~GroupChat()
{
    delete ui;
    delete messagesLayout;
    delete controller;
}

int GroupChat::saveToFile()
{
    QDir LogDir;
    qDebug() << "GroupChat::saveToFile is  running";
    if(!LogDir.exists("vdata/MsgData/Groups"))
    {
        LogDir.mkpath("vdata/MsgData/Groups");
    }
    QFile logFile("vdata/MsgData/Groups/"+this->m_chat_name+".dat");
    if(!logFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        return -1;
    }
    QDataStream user_ds(&logFile);
    user_ds.setVersion(QDataStream::Qt_6_5);
    //user_ds << this->m_message_list;
    for(auto& i : this->m_message_list)
    {
        user_ds << *i;
    }

    logFile.close();
    return 0;
}

int GroupChat::loadFromFile()
{
    QFile logFile("vdata/MsgData/Groups/"+this->m_chat_name+".dat");
    qDebug() << "GroupChat::loadFromFile is  running";
    if(!logFile.open(QIODevice::ReadOnly))
    {
        return -1;
    }
    this->m_message_list.clear();
    QDataStream user_ds(&logFile);
    user_ds.setVersion(QDataStream::Qt_6_5);
    Message *temp = new Message();
    Message* msg;
    while(!logFile.atEnd())
    {
        user_ds >> *temp;
        if(temp->sender()==mp_user->getUserName())
        {
            msg = new msgBaseSend(temp->body(),temp->sender(),temp->receiver(),temp->time(),this);
        }
        else
        {
            msg = new msgBaseReceiver(temp->body(),temp->sender(),temp->receiver(),temp->time(),this);
        }
        this->m_message_list.push_back(msg);
    }
    delete temp;
    logFile.close();
    this->updateList();
    return 0;
}

void GroupChat::updateList()
{
    for(auto& i : this->m_message_list)
    {
        if(!i->isEmpty()){
        if(i->sender() == mp_user->getUserName())
        {
            msgBaseSend* msg = dynamic_cast<msgBaseSend*>(i);
            msg->setFixedSize(500,60);
            messagesLayout->addWidget(msg);
        }
        else{
            msgBaseReceiver* msg = dynamic_cast<msgBaseReceiver*>(i);
            msg->setFixedSize(500,60);
            messagesLayout->addWidget(msg);
        }
        }
    }
}


void GroupChat::mousePressEvent(QMouseEvent* event)
{
    dragPosition = event->globalPos() - frameGeometry().topLeft();
    event->accept();
}
void GroupChat::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        move(event->globalPos() - dragPosition);
        event->accept();
    }
}

void GroupChat::on_send_pbn_clicked()
{
    qDebug("on_send_pbn_clicked from GroupChat class\n");
    QString body = ui->messagebar_led->text();
    if(body.isEmpty())
    {
        ui->sendResult_lbl->setText("No message to send");
        return;
    }
    QString sender = mp_user->getUserName();
    Message msg(body,sender,m_chat_name);
    mp_user->sendMessage(msg,User::Group);
    ui->sendResult_lbl->setText("trying to Send Message\n");
}

void GroupChat::success_on_send_message()
{
    ui->sendResult_lbl->setText("Message Send Successfuly");
    ui->messagebar_led->clear();
}

void GroupChat::failure_on_send_message(QString Error)
{
    ui->sendResult_lbl->setText(Error);
}


void GroupChat::on_refresh_pbn_clicked()
{
    mp_user->getMsg(this->m_chat_name,User::Group);
    ui->sendResult_lbl->setText("Refreshing");
}

void GroupChat::Refresh_handler(QList<Message *> newList)
{
    qDebug() << "GroupChat::Refresh_handler called\n";
    this->m_message_list += newList;
    ui->sendResult_lbl->setText("Refreshed Successfully!\n");
    //ui->message_layout.
    this->updateList();
    this->saveToFile();
}


void GroupChat::on_Exit_pbn_clicked()
{
    this->close();
}

