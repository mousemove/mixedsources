#include "SL.h"


QByteArray makeTCPMessage(unsigned id,const SLMESSAGE & data)
{

    json j;
    j["id"] = id;
    for(auto iterator = data.begin(); iterator != data.end() ; iterator++)
    {
        if(iterator.value().size() == 0)
            continue;
        else if (iterator.value().size() == 1)
        {
            j[iterator.key().toStdString()]  = makeJsonFromQVariant(iterator.value().first());
        }
        else
        {
            for(auto s : iterator.value())
            {
                j[iterator.key().toStdString()] .push_back( makeJsonFromQVariant(s) )    ;
            }
        }
    }
    return QString::fromStdString((j.dump() + "\n")).toUtf8();
}

SLMESSAGE parseTCPMessage(QByteArray & ba)
{
    QMap<QString, QVector<QVariant> > result;
    json j = json::parse(ba.toStdString()) ;

    for (json::iterator it = j.begin(); it != j.end(); ++it) {
        for(auto & i : it.value())
        {
            result[QString::fromStdString(it.key())].push_back( makeQVariantFromJson(i));
        }
    }
    return result;
}

json::value_type makeJsonFromQVariant(const QVariant & value)
{
    if(value.type() == QVariant::Int)
    {
        return value.toInt();
    }
    else if (value.type() == QVariant::Double)
    {
        return value.toDouble();
    }
    else return value.toString().toStdString();
}

QVariant makeQVariantFromJson(const json::value_type & value)
{
    QVariant result;
    if (value.is_number_integer())
    {
        result = static_cast<int>(value);
    }

    else if (value.is_number_integer())
    {
        result = static_cast<float>(value);
    }
    else if (value.is_number())
    {
        result = static_cast<double>(value);
    }
    else  result = QString::fromStdString(value);
    return result;
}


//проверка на выставку бита для UDP команд
bool retBit(unsigned int value,char num)
{
    return (value >> num) &1u;
}
