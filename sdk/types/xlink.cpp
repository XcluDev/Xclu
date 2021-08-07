#include "xlink.h"

#include "incl_cpp.h"
#include "module.h"
#include "xc_project.h"

//---------------------------------------------------------------------
//Clipboard:
/*static*/ QString XLink::get_link_from_clipboard() {
    QString text = xc_clipboard_get_text();
    if (text.length() < Max_Link_Length) {
        return text;
     }
    return "";
}

//---------------------------------------------------------------------
//for text longer Shorten_Link_Length changes end to "..."
/*static*/ QString XLink::shorten_link(QString link) {
    if (link.length() > Shorten_Link_Length) {
        return link.left(Shorten_Link_Length).append("...");
    }
    return link;
}

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
bool XLink::is_equal(const XLink &link0) {
    return (enabled == link0.enabled && link == link0.link);
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
//---------------------------------------------------------------------
XLinkParsed::XLinkParsed(QString module, QString var, int index, int index2) {
    this->module = module;
    this->var = var;
    this->index = index;
    this->index2 = index2;
}

//---------------------------------------------------------------------
XLinkParsed::XLinkParsed(const XLink &link) {
    setup(link.link);
}

//---------------------------------------------------------------------
XLinkParsed::XLinkParsed(QString link_str0) {
    setup(link_str0);
}

//---------------------------------------------------------------------
void XLinkParsed::setup(QString link_str0) {
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
    //xc_assert(n >= 2
    //            && !query.at(0).isEmpty()
    //            && !query.at(1).isEmpty(),
    //            "Bad link '" + link_str0 + "', expected at format webcam1->image or module1->line(0) or module1->line(1,2)");
    xc_assert(n < 3 || !query.at(2).isEmpty(), "Empty first index at link '" + link_str0 + "', expected in format webcam1->image or module1->line(0) or module1->line(1,2)");
    xc_assert(n < 4 || !query.at(3).isEmpty(), "Empty second index at link '" + link_str0 + "', expected in format webcam1->image or module1->line(0) or module1->line(1,2)");

    module = (n >= 1) ? query.at(0) : "";
    var =  (n >= 2) ? query.at(1) : "";
    index = (n >= 3) ? query.at(2).toInt():-1;
    index2 = (n >= 4) ? query.at(3).toInt():-1;
}

//---------------------------------------------------------------------
//String representation of link, such as `webcam1->image`
QString XLinkParsed::to_str() const {
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
//---------------------------------------------------------------------
//---------------------------------------------------------------------
//Test if link is valid - if not, returns error text
XLinkResolved::CheckLinkResult XLinkResolved::check_link(QString link) {
    CheckLinkResult result;
    result.ok = true;
    try{
        XLinkResolved resolved(link);
    }
    catch(XException& e) {
        result.ok = false;
        result.error = e.whatQt();
    }

    return result;
}


//---------------------------------------------------------------------
XLinkResolved::XLinkResolved(QString link_str0)
    : XLinkParsed(link_str0)
{
    resolve();
}

XLinkResolved::XLinkResolved(const XLinkParsed &link0)
    : XLinkParsed(link0)
{
    resolve();
}

//---------------------------------------------------------------------
void XLinkResolved::resolve() {
    //resolve module
    module_ptr_ = xc_get_module(module);
    //check variable exists

    xc_assert(module_ptr_->interf()->has_item(var),
                QString("Source module `%1` has no item `%2`")
                .arg(module_ptr_->name())
                .arg(var));
}

//---------------------------------------------------------------------
Module *XLinkResolved::module_ptr() {
    xc_assert(module_ptr_, "XLinkResolved::module_ptr - nullptr for link " + module + "->" + var);
    return module_ptr_;
}

//---------------------------------------------------------------------
