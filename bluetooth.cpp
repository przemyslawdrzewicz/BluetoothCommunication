#include "bluetooth.h"
#include "ui_bluetooth.h"
#include <QtBluetooth>
#include <QTouchEvent>
#include <QDebug>
#include <math.h>


Bluetooth::Bluetooth(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Bluetooth)
{
    ui->setupUi(this);

    //setCentralWidget(ui->widget);

    //ui->listWidget->hide();
    connect(agent, SIGNAL(deviceDiscovered(QBluetoothDeviceInfo)),
            this, SLOT(deviceDiscovered(QBluetoothDeviceInfo)));
    //agent->start();
    socket = new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);

    ui->slider->setAttribute(Qt::WA_TranslucentBackground);

    ui->controller->hide();
    ui->bluetooth_finder->setGeometry(QRect(0,0,1091,1851));


    ui->next->setEnabled(false);
}

Bluetooth::~Bluetooth()
{
    delete ui;

}

void Bluetooth::on_find_clicked()
{
    ui->listWidget->clear();
    agent->stop();
    agent->start();

}



void Bluetooth::deviceDiscovered(const QBluetoothDeviceInfo &device)
{
    ui->listWidget->addItem(device.address().toString());
}

void Bluetooth::on_listWidget_itemClicked(QListWidgetItem *item)
{
    QString string = item->text();

    static const QString serviceUuid(QStringLiteral("00001101-0000-1000-8000-00805F9B34FB"));
    socket->connectToService(QBluetoothAddress(string), QBluetoothUuid(serviceUuid), QIODevice::ReadWrite);

    agent->stop();

    if (socket->state() == QAbstractSocket::ConnectedState)
    {
        ui->next->setEnabled(true);
    }
}


void Bluetooth::mouseMoveEvent (QMouseEvent* ev)
{
    if ((ev->x()-100.5-440)*(ev->x()-100.5-440)+(ev->y()-100.5-510)*(ev->y()-100.5-510)<=380*380 &&
        (ev->x()-100.5-440)*(ev->x()-100.5-440)+(ev->y()-100.5-510)*(ev->y()-100.5-510)>=100*100  )
    {
        pwm = sqrt( (ev->x()-100.5-440)*(ev->x()-100.5-440)+(ev->y()-100.5-510)*(ev->y()-100.5-510) ) - 40;
        if(pwm > 255)
        {
            pwm = 255;
        }

        QByteArray int_to_qb;
        int_to_qb.setNum(pwm);

        socket->write(int_to_qb+send);
    }
    else
    {
        pwm = 0;

        QByteArray int_to_qb;
        int_to_qb.setNum(pwm);

        socket->write(int_to_qb+send);
    }


    if ((ev->x()-100.5-440)*(ev->x()-100.5-440)+(ev->y()-100.5-510)*(ev->y()-100.5-510)>=380*380)
    {
    }
    else
    {
        ui->slider->setGeometry(QRect(ev->x()-100.5,ev->y()-100.5,201,201));

            if( ev->x()>=435 && ev->x()<=645 && ev->y()<=505 &&
              (ev->x()-100.5-440)*(ev->x()-100.5-440)+(ev->y()-100.5-510)*(ev->y()-100.5-510)<380*380  )
            {
                socket->write("forward\r\n");
            }
            else if ( ev->x()>=645 && ev->y()<=505 &&
                    (ev->x()-100.5-440)*(ev->x()-100.5-440)+(ev->y()-100.5-510)*(ev->y()-100.5-510)<380*380  )
            {
                socket->write("f-r\r\n");
            }
            else if ( ev->x()>=645 && ev->y()>=505 && ev->y()<=715 &&
                    (ev->x()-100.5-440)*(ev->x()-100.5-440)+(ev->y()-100.5-510)*(ev->y()-100.5-510)<380*380  )
            {
                socket->write("right\r\n");
            }
            else if ( ev->x()>=645 && ev->y()>=715 &&
                    (ev->x()-100.5-440)*(ev->x()-100.5-440)+(ev->y()-100.5-510)*(ev->y()-100.5-510)<380*380  )
            {
                socket->write("b-r\r\n");
            }
            else if( ev->x()>=435 && ev->x()<=645 && ev->y()>=715 &&
                   (ev->x()-100.5-440)*(ev->x()-100.5-440)+(ev->y()-100.5-510)*(ev->y()-100.5-510)<380*380  )
            {
                socket->write("back\r\n");
            }
            else if ( ev->x()<=435 && ev->y()>=715 &&
                    (ev->x()-100.5-440)*(ev->x()-100.5-440)+(ev->y()-100.5-510)*(ev->y()-100.5-510)<380*380  )
            {
                socket->write("b-l\r\n");
            }
            else if ( ev->x()<=435 && ev->y()>=505 && ev->y()<=715 &&
                    (ev->x()-100.5-440)*(ev->x()-100.5-440)+(ev->y()-100.5-510)*(ev->y()-100.5-510)<380*380  )
            {
                socket->write("left\r\n");
            }
            else if ( ev->x()<=435 && ev->y()<=505 &&
                    (ev->x()-100.5-440)*(ev->x()-100.5-440)+(ev->y()-100.5-510)*(ev->y()-100.5-510)<380*380  )
            {
                socket->write("f-l\r\n");
            }
            else
            {
               socket->write("stop\r\n");
            }
       }



}

void Bluetooth::mouseReleaseEvent(QMouseEvent* ev)
{
    ui->slider->setGeometry(QRect(440,510,201,201));
    pwm = 0;

    QByteArray int_to_qb;
    int_to_qb.setNum(pwm);

    socket->write(int_to_qb+send);
    socket->write("stop\r\n");
}



void Bluetooth::on_next_clicked()
{
    ui->bluetooth_finder->hide();
    ui->controller->show();
    ui->controller->setGeometry(QRect(0,0,1151,1891));
}

void Bluetooth::on_white_led_clicked()
{
    if (led_white == 0)
    {
        socket->write("w-on\r\n");
        led_white = 1;
    }
    else
    {
        socket->write("w-off\r\n");
        led_white = 0;
    }
}

void Bluetooth::on_red_led_clicked()
{
    if (led_red == 0)
    {
        socket->write("r-on\r\n");
        led_red = 1;
    }
    else
    {
        socket->write("r-off\r\n");
        led_red = 0;
    }
}

void Bluetooth::on_back_clicked()
{
    ui->controller->hide();
    ui->bluetooth_finder->show();
    ui->bluetooth_finder->setGeometry(QRect(0,0,1091,1851));
}

void Bluetooth::on_exit_clicked()
{
    close();
}
