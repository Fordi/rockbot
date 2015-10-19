#include "animtitle.h"
#include <QPainter>
#include <QString>
#include <QImage>

#include "mediator.h"


animTitle::animTitle(QWidget *parent) : QWidget(parent)
{
    std::cout << "animTitle::CONSTRUCTOR" << std::endl;
    myParent = parent;
    _timer = new QTimer(this);
    connect(_timer, SIGNAL(timeout()), this, SLOT(updateBG()));
    int delay = Mediator::get_instance()->game_data.anim_tiles[Mediator::get_instance()->selectedAnimTileset].delay[0];
    if (delay < 10) {
        delay = 10;
    }
    _timer->start(delay);

    update_properties();
}

void animTitle::update_properties()
{
    std::cout << "animTitle::update_properties" << std::endl;
    QString filename = QString(FILEPATH.c_str()) + QString("images/tilesets/anim/") + QString(Mediator::get_instance()->game_data.anim_tiles[Mediator::get_instance()->selectedAnimTileset].filename);
    image = QImage(filename);
    if (image.isNull()) {
        _timer->stop();
        repaint();
        return;
    }
    image = image.scaled(image.width()*2, image.height()*2);

    w = Mediator::get_instance()->game_data.anim_tiles[Mediator::get_instance()->selectedAnimTileset].w * TILESIZE;
    h = Mediator::get_instance()->game_data.anim_tiles[Mediator::get_instance()->selectedAnimTileset].h * TILESIZE;
    this->resize(w*2, h*2);
    myParent->adjustSize();
    max_frames = image.width()/(w*2);
    std::cout << "animTitle::update_properties::max_frames: " << max_frames << std::endl;

    _sprite_n = 0;
    _timer->stop();
    _timer->start(Mediator::get_instance()->game_data.anim_tiles[Mediator::get_instance()->selectedAnimTileset].delay[0]);
    repaint();
}


void animTitle::updateBG()
{
    _sprite_n++;
    if (_sprite_n > ANIM_FRAMES_COUNT-1) {
        _sprite_n = 0;
    }

    if (image.isNull()) {
        _timer->stop();
        return;
    }
    if (_sprite_n >= max_frames) {
        _sprite_n = 0;
    }
    _timer->stop();
    _timer->start(Mediator::get_instance()->game_data.anim_tiles[Mediator::get_instance()->selectedAnimTileset].delay[0]);
    repaint();
}


void animTitle::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QRectF target, source;

    if (image.isNull() == true || image.width() <= 0) {
        painter.fillRect(0, 0, this->width(), this->height(), QColor(0, 0, 0));
        return;
    }

    source = QRectF(QPoint(_sprite_n*(w*2), 0), QSize(w*2, h*2));
    target = QRectF(QPoint(0, 0), QSize(w*2, h*2));
    painter.drawImage(target, image, source);
}
