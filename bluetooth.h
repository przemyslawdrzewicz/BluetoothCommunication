#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <QMainWindow>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothSocket>
#include <QListWidget>
#include <QMouseEvent>
#include <QEvent>
#include <QString>

using namespace std;

namespace Ui {
class Bluetooth;
}

class Bluetooth : public QMainWindow
{
    Q_OBJECT

public:
    explicit Bluetooth(QWidget *parent = 0);
    ~Bluetooth();

    int pwm = 0;
    QByteArray send = "\r\n";
    void mouseMoveEvent (QMouseEvent* ev);
    void mouseReleaseEvent(QMouseEvent* ev);
    int led_red = 0;
    int led_white = 0;

private slots:
    void on_find_clicked();
    void deviceDiscovered(const QBluetoothDeviceInfo &device);
    void on_listWidget_itemClicked(QListWidgetItem *item);


    void on_next_clicked();
    void on_white_led_clicked();
    void on_red_led_clicked();
    void on_back_clicked();
    void on_exit_clicked();

private:
    Ui::Bluetooth *ui;
    QBluetoothDeviceDiscoveryAgent *agent = new QBluetoothDeviceDiscoveryAgent;
    QBluetoothSocket *socket;
};

#endif // BLUETOOTH_H
