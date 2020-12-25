#include "xclu_parse_tree.h"
#include "incl_cpp.h"

//---------------------------------------------------------------------
//основная функция парсинга
void XcluParseTree::parse(const QStringList &lines) {
    items.clear();
    int pos = 0;
    //создание корня дерева
    XcluParseTreeItem root;
    items.push_back(root);
    //вызов рекурсивной функции
    parse_internal(lines, pos, 0);

    //тестовая печать структуры дерева
    //qDebug() << "Tree:";
    //for (int i=0; i<items.size(); i++) {
    //    auto &item = items[i];
    //    qDebug() << i << " " << item.indent << "  " << item.line << " parent: " << item.parent << ", children: " << item.children.size();
    //}
}

//---------------------------------------------------------------------
//рекурсивная функция создания дерева элементов
void XcluParseTree::parse_internal(const QStringList &lines, int &pos, int index) {

    while (pos < lines.size()) {
        QString line0 = lines.at(pos);
        pos++;
        if (line0.isEmpty()) continue;

        //вычисляем отступ в числе пробелов
        int indent=0;
        while (indent < line0.length() && line0.at(indent) == ' ') indent++;

        //подрезаем
        QString line = line0.trimmed();
        if (line.isEmpty()) continue;
        if (line.at(0) == '#') continue;    //комментарий

        //новый элемент
        XcluParseTreeItem new_item;
        new_item.line = line;
        new_item.indent = indent;

        //родитель
        xc_assert(index >= 0, "Parsing error at '" + line0 + "'");
        int indent0 = items[index].indent;
        //Помните: нельзя взять ссылку от items[index] и затем ее использовать,
        //так как он меняет себя при вставке new_item, и ссылка становится недействительной!
        //Поэтому, его нужно использовать каждый раз как items[index].

        if (indent > indent0) {
            //внутрь
            new_item.parent = index;
            items.push_back(new_item);
            int i = items.size()-1;
            //вставляем в parent
            items[index].children.push_back(i);
            //парсим это поддерево
            parse_internal(lines, pos, i);
            continue;
        }
        if (indent == indent0) {
            //продолжаем
            int parent = items[index].parent;
            xc_assert(parent >= 0, "Parsing error, wrong indentation at '" + line0 + "'");

            //вставляем в список
            new_item.parent = parent;
            items.push_back(new_item);
            int i = items.size()-1;
            //вставляем в parent
            items[parent].children.push_back(i);
            //парсим это поддерево
            parse_internal(lines, pos, i);
            continue;
        }
        if (indent < indent0) {
            //возврат
            pos--;      //пропарсим еще раз эту строку, но уже на другом проходе
            return;
        }
    }
}
