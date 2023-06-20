#ifndef REFRESHERABSTRACT_H
#define REFRESHERABSTRACT_H

#include <QObject>
#include <QThread>

#define FREEZEDURATION 1

class refresherAbstract : public QThread
{
    Q_OBJECT
public:
    explicit refresherAbstract(QObject *parent = nullptr);
    void run();
    virtual void jSonChecker(int& argMsgCount) = 0;
    int msgCountInit();
signals:
};

#endif // REFRESHERABSTRACT_H