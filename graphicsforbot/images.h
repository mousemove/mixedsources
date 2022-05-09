#ifndef IMAGES_H
#define IMAGES_H

#include <QObject>
#include <QPixmap>
#include <QPainter>
#include <QGraphicsTextItem>
#include <QtDebug>
#include <QTextItem>
//класс для бота обработка картинок(ватермарка-пикселизация-аскиарт)
class images : public QObject
{
    Q_OBJECT
public:
    explicit images(QObject *parent = nullptr);
    static QPixmap setWatermark(QString path, QString text, QColor color,QFont font = QFont());
    static QPixmap pixelizeV1(QString path,int pixelizing = 20);
    static QPixmap pixelizeV2(QString path,int pixelizing = 20);
    static QString toAsciiV1(QString path,int pixelizing = 20);
      static QString toAsciiV2(QString path,int pixelizing = 20);
signals:

};

#endif // IMAGES_H
