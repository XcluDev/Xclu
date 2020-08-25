#ifndef XCLU_PARSE_TREE_H
#define XCLU_PARSE_TREE_H

//Парсинг дерева - строк с отступами
//результат хранится в виде массива узлов, и ссылки на узлы - по индексам в этом массиве.
//Допустимы строки-комментарии, начинающиеся с '#'.
//Допустимо любое число пробелов в качестве отступов.
/*
Это используется в модуле Window для парсинга структуры окна:
HorizontalLayout
  Tabs 5
    Tab Tab_1
      HorizontalLayout
        wnumber1
        wnumber2
    Tab Tab_2
    Tab Tab_3
  VerticalLayout 0
    wbutton1 0
    wbutton2 0
    Stretch 1
*/


#include "incl_h.h"

//элемент дерева
class XcluParseTreeItem {
public:
    int indent = -1; //отступ
    QString line;    //строка - уже без отступа, но еще не распарсенная
    QVector<int> children;  //номера детей
    int parent = -1;        //номер родителя
};

//класс для построения и хранения дерева
class XcluParseTree {
public:
    QVector<XcluParseTreeItem> items;

    //основная функция парсинга
    void parse(const QStringList &lines);

protected:
    //рекурсивная функция создания дерева элементов
    void parse_internal(const QStringList &lines, int &pos, int index);
};


#endif // XCLU_PARSE_TREE_H
