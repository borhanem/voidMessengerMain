#ifndef REFRESHERDIRECT_H
#define REFRESHERDIRECT_H

#include <QObject>
#include "refresherabstract.h"

class refresherDirect : public refresherAbstract
{
    Q_OBJECT
public:
    explicit refresherDirect(QObject *parent = nullptr,const QString& argDst = "");
    explicit refresherDirect(const QString& argDst = "",User* argUser = nullptr,QObject *parent = nullptr);
    void refresherMain(User& argUser) override;
    void msgCountInit() override;
    void testInit(User& argUser);
    void jsonHandle() override;
private:
    QString dstDirect;
    int msgCount;
    User* currUser;
signals:
    void directRefreshSignal(QList<Message*>);
private slots:


};


#endif // REFRESHERDIRECT_H
