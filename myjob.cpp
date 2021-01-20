#include "myjob.h"

#define steps 7
#define dir 0
#define en 3
#define hm_sen 4

#define LED 26

MyJob::MyJob(QObject *parent) : QObject(parent)
{
    mStop = false;
    wiringPiSetup () ;
    pinMode (en, OUTPUT) ;
    pinMode (dir, OUTPUT) ;
    pinMode (steps, OUTPUT) ;
    pinMode (hm_sen, INPUT) ;
    pinMode (LED, PWM_OUTPUT);
    pwmWrite (LED, 0);
}

MyJob::~MyJob()
{

}

void MyJob::start(QString name)
{
    mStop = false;

//    for(int i = 0; i < 999999; i++)
//    {
//        if(mStop) return;
//        qDebug() << "From thread: " << i;
//        emit on_number(name,i);
//        QThread::currentThread()->msleep(100);
//    }
    pwmWrite (LED, 100);
    digitalWrite(en,LOW);
    digitalWrite(dir,HIGH);
    for (int i=0;i<30000;i++)
    {
        if(digitalRead(hm_sen)==1)
        {
            break;
        }
        else
        {
            digitalWrite(steps, HIGH);
            QThread::usleep(150);
            digitalWrite(steps, LOW);
            QThread::usleep(150);
        }
        if(mStop) return;

    }
    digitalWrite(en,HIGH);
     pwmWrite (LED, 0);
    digitalWrite(en,LOW);
    digitalWrite(dir,LOW);
    for (int i=0;i<24000;i++)
    {
            digitalWrite(steps, HIGH);
            QThread::usleep(50);
            digitalWrite(steps, LOW);
            QThread::usleep(50);
        }
     digitalWrite(en,HIGH);
}

void MyJob::stop()
{
    mStop = true;
}

