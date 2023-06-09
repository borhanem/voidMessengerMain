#ifndef CREATEPRIVATEPAGE_H
#define CREATEPRIVATEPAGE_H

#include <QDialog>
#include "user.h"
#include <QMouseEvent>
namespace Ui {
class CreatePrivatePage;
}

class CreatePrivatePage : public QDialog
{
    Q_OBJECT

public:
    explicit CreatePrivatePage(const User* const user = nullptr,QWidget *parent = nullptr);
    ~CreatePrivatePage();

private slots:
    void on_newprivate_pbn_clicked();

    void on_cancel_pbn_clicked();

    void success_on_create_NewPrivate();

    void failure_on_create_NewPrivate(QString error);

    void on_Exit_pbn_clicked();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

signals:
    void NewPrivate(QString);
private:
    QPoint dragPosition;
    Ui::CreatePrivatePage *ui;
    const User* const mp_user;
};

#endif // CREATEPRIVATEPAGE_H
