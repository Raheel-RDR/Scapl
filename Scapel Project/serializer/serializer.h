#pragma once
#include <QJsonArray>

class Operand;

class Serializer
{
  QJsonArray jsonArray;
  QString directory;

public:
  Serializer(QString directory) : directory{ directory } {}
  QJsonArray get_jsonArray() {return jsonArray; }
  void save_to_json(const std::string& label, Operand* operand);
  void load_from_json();
};
