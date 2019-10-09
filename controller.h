#ifndef CONTROLLER_H
#define CONTROLLER_H


class Controller
{

public:
    int pwm = 0;

    void mouseMoveEvent (QMouseEvent* ev);
    void mouseReleaseEvent(QMouseEvent* ev);
};



#endif // CONTROLLER_H
