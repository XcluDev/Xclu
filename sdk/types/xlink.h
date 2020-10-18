#ifndef XLINK_H
#define XLINK_H

//Working with с links - creating and parsing links as following strings:
//webcam1->image     - link to component
//#module1->var      - disabled link, also empty string means disabled link too
//module1->line(1)   - link to part of component (word or line) pointed by one index
//module1->line(1,2) - link to part of component (word) pointed by two indices index

#include "incl_h.h"
class Module;

//---------------------------------------------------------------------
//XLink - packed link stored as a string
//---------------------------------------------------------------------
//Storing link string and enabled/disabled property
class XLink {
public:
    //Clipboard:
    static const int Max_Link_Length = 100;   //constant for limiting link length from clibboard to avoit "giant" strings
    static const int Shorten_Link_Length = 30;   //constant for limiting link length when output at menu
    static QString get_link_from_clipboard(); //for text longer Max_Link_Length returns empty string
    static QString shorten_link(QString link); //for text longer Shorten_Link_Length changes end to "..."
public:
    bool enabled = false;
    QString link;
    XLink() {}
    XLink(bool enabled, QString link);
    XLink(QString link_str);
    bool is_empty() const;
    void clear();
    QString to_str() const;

    bool is_equal(const XLink &link0);
};

//---------------------------------------------------------------------
//XLinkParsed - Parsed link
//---------------------------------------------------------------------
class XLinkParsed {
public:
    //Constructor
    XLinkParsed() {}
    XLinkParsed(QString module, QString var, int index = -1, int index2 = -1);
    XLinkParsed(QString link);
    XLinkParsed(const XLink &link);

    //String representation of link, such as `webcam1->image`
    QString to_str() const;

    bool has_index() const { return index >= 0; }

    bool is_empty = true;
    QString module;
    QString var;
    int index = -1; //if index >= 0 - interpret as a string separated by spaces 'a b c' and get its item 'index'
    int index2 = -1; //if index2 >= 0 - interpret as a string separated by "\n" and then spaces 'a b c' and get its line 'index' and item 'index2'
protected:
    void setup(QString link_str0);
};

//---------------------------------------------------------------------
//XLinkResolved - Parsed link with resolved module
//---------------------------------------------------------------------
class XLinkResolved: public XLinkParsed {
public:
    struct CheckLinkResult {
        bool ok = false;
        QString error;
    };
    //Test if link is valid - if not, returns error text
    static CheckLinkResult check_link(QString link);
public:
    XLinkResolved(QString link_str0);
    XLinkResolved(const XLinkParsed &link0);
    Module *module_ptr();

protected:
    void resolve();
    Module *module_ptr_ = nullptr;
};


#endif // XLINK_H
