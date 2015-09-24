#include <QPainter>
#include <iostream>

#include "imageareapreview.h"
#include "defines.h"

#define IMAGE_SCALE 2

extern char EDITOR_FILEPATH[512];

ImageAreaPreview::ImageAreaPreview(QWidget *parent) : QWidget(parent)
{
    graphic_filename = "";

    x = 0;
    y = 0;
    w = 0;
    h = 0;
    ini_x = 0;
    ini_y = 0;
    dest_x = 0;
    dest_y = 0;


    this->resize(RES_W, RES_H);
    parent->adjustSize();
}

void ImageAreaPreview::setImageFilename(QString name)
{
    graphic_filename = QString(EDITOR_FILEPATH) + QString("/data/images/scenes/") + name;
    std::cout << ">> ImageAreaPreview::setImageFilename: " << graphic_filename.toStdString() << std::endl;
}

// viewpoint
void ImageAreaPreview::set_x(int set)
{
    x = set;
    repaint();
}

void ImageAreaPreview::set_y(int set)
{
    y = set;
    repaint();
}

void ImageAreaPreview::set_w(int set)
{
    w = set;
    repaint();
}

void ImageAreaPreview::set_h(int set)
{
    h = set;
    repaint();
}

void ImageAreaPreview::set_ini_x(int set)
{
    ini_x = set;
    repaint();
}

void ImageAreaPreview::set_ini_y(int set)
{
    ini_y = set;
    repaint();
}

void ImageAreaPreview::set_dest_x(int set)
{
    dest_x = set;
    repaint();
}

void ImageAreaPreview::set_dest_y(int set)
{
    dest_y = set;
    repaint();
}

void ImageAreaPreview::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QLineF line;
    QRectF target, source;

    painter.fillRect(0, 0, RES_W, RES_H, QColor(0, 0, 0, 255));

    if (graphic_filename.length() == 0) {
        std::cout << ">> ImageAreaPreview::paintEvent: LEAVE #1" << std::endl;
        return;
    }
    if (graphic_filename.toStdString().find(".png") == std::string::npos) {
        std::cout << ">> ImageAreaPreview::paintEvent: LEAVE #3" << std::endl;
        return;
    }

    QPixmap image(graphic_filename.toStdString().c_str());

    if (image.isNull() == true || image.width() <= 0) {
        std::cout << ">> ImageAreaPreview::paintEvent: LEAVE #4" << std::endl;
        return;
    }

    if (w == 0) {
        // @TODO: isto deve gerar um SIGNAL que a UI vai receber para atualizar o valor na spinbox
        w = image.width();
        emit on_image_w_changed(w);
    }
    if (h == 0) {
        // @TODO: isto deve gerar um SIGNAL que a UI vai receber para atualizar o valor na spinbox
        h = image.height();
        emit on_image_h_changed(h);
    }

    target = QRectF(QPoint(x+ini_x, y+ini_y), QSize(image.width(), image.height()));
    source = QRectF(QPoint(0, 0), QSize(image.width(), image.height()));
    painter.drawPixmap(target, image, source);

    // frame rectangle
    painter.setPen(QColor(255, 0, 0));
    // linha topo
    line = QLineF(x+ini_x, y+ini_y, (x+ini_x+w), y+ini_y);
    painter.drawLine(line);
    // linha baixo
    line = QLineF(x+ini_x, (y+ini_y+h), (x+ini_x+w), (y+ini_y+h));
    painter.drawLine(line);
    // linha esquerda
    line = QLineF(x+ini_x, y+ini_y, x+ini_x, (y+ini_y+h));
    painter.drawLine(line);
    // linha direita
    line = QLineF((x+ini_x+w), y+ini_y, (x+ini_x+w), (y+ini_y+h));
    painter.drawLine(line);

    // destiny rectangle
    painter.setPen(QColor(0, 255, 0));

    std::cout << "dest_x: " << dest_x << ", dest_y: " << dest_y << std::endl;

    // linha topo
    line = QLineF((x+dest_x), (y+dest_y), (x+dest_x+w), (y+dest_y));
    painter.drawLine(line);
    // linha baixo
    line = QLineF((x+dest_x), (y+dest_y+h), (x+dest_x+w), (y+dest_y+h));
    painter.drawLine(line);
    // linha esquerda
    line = QLineF((x+dest_x), (y+dest_y), (x+dest_x), (y+dest_y+h));
    painter.drawLine(line);
    // linha direita
    line = QLineF((x+dest_x+w), (y+dest_y), (x+dest_x+w), (y+dest_y+h));
    painter.drawLine(line);

    QPen pen(Qt::white, 1, Qt::DotLine);
    painter.setPen(pen);
    line = QLineF((x+ini_x), (y+ini_y), (x+dest_x), (y+dest_y));
    painter.drawLine(line);
    // linha baixo
    line = QLineF((x+ini_x), (y+ini_y+h), (x+dest_x), (y+dest_y+h));
    painter.drawLine(line);
    // linha esquerda
    line = QLineF((x+ini_x+w), (y+ini_y), (x+dest_x+w), (y+dest_y));
    painter.drawLine(line);
    // linha direita
    line = QLineF((x+ini_x+w), (y+ini_y+h), (x+dest_x+w), (y+dest_y+h));
    painter.drawLine(line);



}

