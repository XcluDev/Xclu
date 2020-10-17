#include "xlink.h"

#include "incl_cpp.h"

//---------------------------------------------------------------------
XLink::XLink(bool enabled, QString link) {
    this->enabled = enabled;
    this->link = link;
}

//---------------------------------------------------------------------
XLink::XLink(QString link_str) {
    if (!link_str.isEmpty()) {
        if (link_str.left(1) == "#") {
            link_str.remove(0, 1);
            enabled = false;
            this->link = link_str;
        }
        else {
            enabled = true;
            this->link = link_str;
        }
    }
}

//---------------------------------------------------------------------
bool XLink::is_empty() const {
    return !enabled && link.isEmpty();
}

//---------------------------------------------------------------------
void XLink::clear() {
    enabled = false;
    link = "";
}

//---------------------------------------------------------------------
QString XLink::to_str() const {
    if (is_empty()) return "";
    if (enabled) {
        return link;
    }
    else {
        return "#" + link;
    }
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
//---------------------------------------------------------------------
/*static*/ QString XLinkParser::get_link_from_clipboard() {
    QString text = xclu_clipboard_get_text();
    if (text.length() < Max_Link_Length) {
        return text;
     }
    return "";
}

//---------------------------------------------------------------------
//for text longer Shorten_Link_Length changes end to "..."
/*static*/ QString XLinkParser::shorten_link(QString link) {
    if (link.length() > Shorten_Link_Length) {
        return link.left(Shorten_Link_Length).append("...");
    }
    return link;
}

//---------------------------------------------------------------------
XLinkParser::XLinkParser(QString module, QString var, int index, int index2) {
    this->module = module;
    this->var = var;
    this->index = index;
    this->index2 = index2;
}

//---------------------------------------------------------------------
XLinkParser::XLinkParser(QString link_str0) {
    is_empty = link_str0.isEmpty();
    if (is_empty) {
        return;
    }

    //для простоты "(", "->" на " " и убираем ")"
    //тогда module1->line(1) будет как "module1 line 1"
    QString link = link_str0.trimmed()
            .replace("->"," ").replace("("," ").replace(","," ").replace(")","");

    auto query = link.trimmed().split(" ");
    int n = query.size();
    xclu_assert(n >= 2
                && !query.at(0).isEmpty()
                && !query.at(1).isEmpty(),
                "Bad link '" + link_str0 + "', expected at format webcam1->image or module1->line(0) or module1->line(1,2)");
    xclu_assert(n < 3 || !query.at(2).isEmpty(), "Empty first index at link '" + link_str0 + "', expected in format webcam1->image or module1->line(0) or module1->line(1,2)");
    xclu_assert(n < 4 || !query.at(3).isEmpty(), "Empty second index at link '" + link_str0 + "', expected in format webcam1->image or module1->line(0) or module1->line(1,2)");

    module = query.at(0);
    var = query.at(1);
    index = (n >= 3) ? query.at(2).toInt():-1;
    index2 = (n >= 4) ? query.at(3).toInt():-1;
}

//---------------------------------------------------------------------
//String representation of link, such as `webcam1->image`
QString XLinkParser::to_str() const {
    QString res;
    res.append(module).append("->").append(var);
    if (index >= 0) {
        res.append(QString("(%1").arg(index));
        if (index2 >= 0) {
            res.append(QString("(%1").arg(index2));
        }
        res.append(")");
    }
    return res;
}

//---------------------------------------------------------------------
