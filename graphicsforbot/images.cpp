#include "images.h"

images::images(QObject *parent) : QObject(parent)
{

}

QPixmap images::setWatermark(QString path, QString text, QColor color, QFont font)
{
    QImage image(path);
    QPixmap result = QPixmap::fromImage(image);
    QPainter painter(&result);

    painter.setFont(font);
    painter.setPen(color);
    QFontMetrics metrics(font);
    painter.drawText(result.width()-metrics.width(text),result.height()-2,text);


    return result;

}

QPixmap images::pixelizeV1(QString path,int pixelizing)
{
    QImage image(path);
    image = image.copy(QRect(0,0,image.width()-image.width()%pixelizing,image.height() - image.height()%pixelizing));
    for(unsigned x = 0 ;x < image.width();x = x + pixelizing  )
    {

        for(auto y = 0; y < image.height(); y =y+pixelizing)
        {
            QColor c = image.pixelColor(x,y);
            for(int i = x; i < x + pixelizing ;i++)
            {
                for(unsigned j = y ;j < y+pixelizing; j++)
                {
                    image.setPixelColor(i,j,c);
                }
            }
        }
    }
    auto result = QPixmap::fromImage(image);
    return result;

}

QPixmap images::pixelizeV2(QString path, int pixelizing)
{
    QImage image(path);
    image = image.copy(QRect(0,0,image.width()-image.width()%pixelizing,image.height() - image.height()%pixelizing));
    int R = 0;
    int G = 0;
    int B = 0;


    for(unsigned x = 0 ;x < image.width();x = x + pixelizing  )
    {
        for(unsigned y = 0; y < image.height(); y =y+pixelizing)
        {
            R = 0;
            G = 0;
            B = 0;
            for(int i = x; i < x + pixelizing ;i++)
            {
                for(unsigned j = y ;j < y+pixelizing; j++)
                {
                    QColor c = image.pixelColor(i,j);
                    R = R+ c.red();
                    G = G+ c.green();
                    B = B+ c.blue();
                }
            }
            R /=(pixelizing*pixelizing);
            G /=(pixelizing*pixelizing);
            B /= (pixelizing*pixelizing);
            QColor c = QColor(R,G,B);
            for(int i = x; i < x + pixelizing ;i++)
            {
                for(unsigned j = y ;j < y+pixelizing; j++)
                {
                    image.setPixelColor(i,j,c);

                }
            }


        }
    }

    auto result = QPixmap::fromImage(image);
    return result;

}

QString images::toAsciiV1(QString path, int pixelizing)
{
    QImage image(path);
    QString result;
    image = image.copy(QRect(0,0,image.width()-image.width()%pixelizing,image.height() - image.height()%pixelizing));
    for(unsigned x = 0 ;x < image.height();x = x + pixelizing  )
    {

        for(auto y = 0; y < image.width(); y =y+pixelizing)
        {
            QColor c = image.pixelColor(y,x);
            int average = (c.red() + c.green() + c.blue())/3;
            if (average > 225)
                result +="▁";
            else if  (average > 200)
                result +="▕";
            else if  (average > 175)
                result +="░";
            else if  (average > 150)
                result +="▋";
            else if  (average > 125)
                result +="▒";
            else if  (average > 75)
                result +="▐";
            else if  (average > 50)
                result +="▓";
            else if  (average > 25)
                result +="▟";
            else result +="█";
        }
        result = result+"\n";
    }
    return result;

}

QString images::toAsciiV2(QString path, int pixelizing)
{
    QImage image(path);
    QString result;
    image = image.copy(QRect(0,0,image.width()-image.width()%pixelizing,image.height() - image.height()%pixelizing));
    int R = 0;
    int G = 0;
    int B = 0;
    for(unsigned x = 0 ;x < image.height();x = x + pixelizing  )
    {

        for(auto y = 0; y < image.width(); y =y+pixelizing)
        {
            R = 0;
            G = 0;
            B = 0;
            for(int i = x; i < x + pixelizing ;i++)
            {
                for(unsigned j = y ;j < y+pixelizing; j++)
                {
                    QColor c = image.pixelColor(j,i);
                    R = R+ c.red();
                    G = G+ c.green();
                    B = B+ c.blue();
                }
            }

            R /=(pixelizing*pixelizing);
            G /=(pixelizing*pixelizing);
            B /= (pixelizing*pixelizing);
            QColor c = QColor(R,G,B);
            int average = (c.red() + c.green() + c.blue())/3;

            if (average > 225)
                result +="▁";
            else if  (average > 200)
                result +="▕";
            else if  (average > 175)
                result +="░";
            else if  (average > 150)
                result +="▋";
            else if  (average > 125)
                result +="▒";
            else if  (average > 75)
                result +="▐";
            else if  (average > 50)
                result +="▓";
            else if  (average > 25)
                result +="▟";
            else result +="█";
        }
        result = result+"\n";
    }
    return result;

}
