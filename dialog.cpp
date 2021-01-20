#include "dialog.h"
#include "ui_dialog.h"
#include "qmovie.h"


Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    emit on_stop();
    delete ui;
}

void Dialog::on_btnStart_clicked()
{
    //QT 4+ connect(obj,SIGNAL(), obj2,SLOT());

    //Qt 5
    connect(&mJob,&MyJob::on_number,this,&Dialog::newNumber);
    connect(this,&Dialog::on_stop, &mJob,&MyJob::stop);

    QFuture<void> test = QtConcurrent::run(&this->mJob,&MyJob::start,QString("kitten"));
    QMovie *movie = new QMovie("/home/pi/git/Qt-31/MyGuiThread/Spinner.gif");
    ui->label->setVisible(true);
    ui->label->setMovie(movie);
    //w->setMovie (movie);
    movie->start ();
    QProcess process;
    QString Command;
    Command= "raspistill -t 6000 -tl 700 -ss 1500 -o /home/pi/image%04d.jpg";
    //Command ="raspivid -t 10000 -o /home/pi/video.h264";
    //Command="raspivid -o /home/pi/myvideo.h264 --width 800 --height 600 --framerate 240 --timeout 10000 -roi 0.2,0.2,0.5,0.5";
    process.execute(Command);
    //process.waitForFinished();


}

void Dialog::on_btnStop_clicked()
{
    emit on_stop();
    ui->label->setVisible(false);
}

void Dialog::newNumber(QString name, int number)
{
     qDebug() << "From dialog: " << name << " " << number;
     ui->lineEdit->setText(name + " " + QString::number(number));
}
