#ifndef ADDITIONAL_H
#define ADDITIONAL_H
#include "lib/json.hpp"
#include <QDebug>
#include <iostream>
using json = nlohmann::json;
typedef  QMap<QString, QVector<QVariant> > SLMESSAGE;
QByteArray makeTCPMessage(unsigned id, const SLMESSAGE &data);
SLMESSAGE parseTCPMessage(QByteArray & ba);

json::value_type makeJsonFromQVariant (const QVariant  &value);
QVariant makeQVariantFromJson(const json::value_type & value);
bool retBit(unsigned int value,char num);
#endif // ADDITIONAL_H
