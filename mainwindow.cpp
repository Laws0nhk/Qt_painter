#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(0, 0, 800, 480);
    setPalette(QPalette(Qt::gray));
    setAutoFillBackground(true);

    timer = new QTimer(this);
    angle = 0;
    timer->start(50);
    connect(timer, &QTimer::timeout, this, &MainWindow::timerTimeOut);
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    //设置抗锯齿，流畅转换
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    if(angle++ == 360)
        angle = 0;
    QPixmap image;
    image.load("/home/kk/图片/截图/1.png");
    //初始化一个矩形，使用浮点精度
    QRectF rect((this->width() - image.width()) / 2,
                (this->height() - image.height()) / 2,
                image.width(), image.height());
    //用向量dx,dy平移坐标
    painter.translate(0 + rect.x() + rect.width() / 2,
                      0 + rect.y() + rect.height() / 2);
    //以angle角度,顺时针旋转
    painter.rotate(angle);

    painter.translate(0 - (rect.x() + rect.width() / 2),
                      0 - (rect.y() + rect.height() / 2));
    painter.drawImage(rect, image.toImage(), image.rect());
    painter.drawRect(rect.toRect());
}

void MainWindow::timerTimeOut()
{
    this->update();
}

MainWindow::~MainWindow()
{

}
