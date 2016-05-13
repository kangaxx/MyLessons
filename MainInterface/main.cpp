#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include <QSplashScreen>
#include <QElapsedTimer>
#define INT_SPLASH_TIME 3000

int main(int argc, char *argv[])
{
    try {
        QApplication a(argc, argv);
        QApplication::addLibraryPath(QString("../lib"));
        QTextCodec *tc=QTextCodec::codecForName("utf-8");
        QTextCodec::setCodecForLocale(tc);

        //加载并显示启动画面
        QString splashImg = QApplication::applicationDirPath() + "/../icon/splash.png";
        QSplashScreen splash(QPixmap(splashImg.toStdString().c_str()));
        splash.setDisabled(true); //禁用用户的输入事件响应
        splash.show();

        splash.showMessage(QObject::tr("Load APP Data. Loading..."),
                           Qt::AlignLeft|Qt::AlignBottom,Qt::green);
        splash.showMessage(QObject::tr("Load Modules Data. Loading..."),Qt::AlignLeft|Qt::AlignBottom,Qt::green);

        QElapsedTimer t;
        t.start();
        while(t.elapsed()<INT_SPLASH_TIME)
        {
            QCoreApplication::processEvents();
        }
        splash.hide();
        MainWindow w;
        w.show();

        return a.exec();
    }
    catch (string err) {
        qDebug() << QString("QModeling start error :%1").arg(err.c_str());
    }
    catch (...){
        perror("QModeling start fail :");
    }
}
