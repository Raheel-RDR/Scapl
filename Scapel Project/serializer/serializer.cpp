#include "serializer.h"
#include "string.h"
#include "./operand/operand.h"
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>
#include <QtDebug>
#include <QFile>

void Serializer::save_to_json(const std::string& label, Operand* operand)
{
  QJsonObject jsonObj;
  jsonObj["Label"] = QString::fromStdString(label);
  jsonObj["Operand"] = QString::fromStdString(operand->operandName()); //set JSON Operand field
  jsonObj["Arguments"] = operand->arguments();                        //set JSON Arguments field

  jsonArray.push_back(QJsonValue(jsonObj));                         //push the JSON of jsonObj for this specific operand into jsonArray

  if(operand->operandName() == "end"){                             //check if the operand is the end operand
    QJsonObject finalJsonObj;                                      //create QJsonObject finalJsonObj
    finalJsonObj.insert(QString("program"), QJsonValue(jsonArray)); //insert the program field and pass the built up jsonArray into finalJsonObj
    QJsonDocument doc(finalJsonObj);                                // create QJsonDocument from finalJsonObj
    QByteArray bytes = doc.toJson();                                //create a QByteArray called bytes from doc to save doc as JSON

    QFile newDoc(directory + ".json");
    if(newDoc.open(QIODevice::WriteOnly)){                          //check file permissions with open
        newDoc.write(bytes);                                        //save file
    }
    newDoc.close();                                                 //close file
  }
}

void Serializer::load_from_json() {
  QString val;
  QFile file;
  file.setFileName(this->directory);
  file.open(QIODevice::ReadOnly | QIODevice::Text);
  val = file.readAll();
  file.close();
  QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());

  QJsonObject obj = d.object();
  QJsonValue program = obj.value(QString("program"));
  this->jsonArray = program.toArray();
}
