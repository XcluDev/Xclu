#include "xclasstextvariation.h"
#include "incl_cpp.h"
#include "registrarxclass.h"
#include "project_props.h"


//registering module implementation
REGISTER_XCLASS(TextVariation)

//---------------------------------------------------------------------
XClassTextVariation::XClassTextVariation(QString class_name)
    :XClass(class_name)
{

}

//---------------------------------------------------------------------
XClassTextVariation::~XClassTextVariation()
{

}

//---------------------------------------------------------------------
void XClassTextVariation::start() {

}

//---------------------------------------------------------------------
void XClassTextVariation::update() {
    sets_output_text(variate(gets_input_text(), 0));
}

//---------------------------------------------------------------------
void XClassTextVariation::stop() {

}

//---------------------------------------------------------------------
//void XClassTimerariation::on_button_pressed(QString button_id) {
//}

//---------------------------------------------------------------------
//Recursive function for building variation
//For [A|B|C[D|E]] input it will generate randomly A,B,CD,CE.
//level - for debugging
QString XClassTextVariation::variate(QString text, int level) {
    if (!text.contains("[")) return text;
    int state = 0;  //0 - no [, 1 - collecting variants, 2 and more - we are inside [[[.

    QString result;
    QString collect;
    QStringList variants;
    for (int i=0; i<text.length(); i++) {
        auto c = text.at(i);
        if (c == QLatin1Char('[')) {
            state++;
            if (state > 1) collect += c;
            continue;
        }
        if (c == QLatin1Char('|')) {
            xc_assert(state >= 1, "Can't parse '" + text + "': '|' is not inside [...]");

            if (state == 1) {
                //add variant; note recursive call to resolve it totally
                variants.append(variate(collect, level+1));
                collect.clear();
            }
            else { //just continue collect
                collect += c;
            }
            continue;
        }
        if (c == QLatin1Char(']')) {
            state--;
            xc_assert(state >= 0, "Can't parse '" + text + "': extra ']'");
            if (state == 0) {
                //add variant; note recursive call to resolve it totally
                variants.append(variate(collect, level+1));
                collect.clear();

                //choose random variant
                if (!variants.isEmpty()) {
                    result += variants.at(xrandomi(0, variants.size()-1));
                    variants.clear();
                }
            }
            else { //collecting...
                collect += c;
            }
            continue;
        }
        if (state == 0) {
            result += c;
        }
        else {
            collect += c;
        }
    }
    xc_assert(state==0,  "Can't parse '" + text + "': no closing ']'");

    //----- debug
    //xc_console_append(QString("LEVEL %1").arg(level));
    //xc_console_append(QString("IN: %1").arg(text));
    //xc_console_append(QString("OUT: %1").arg(result));
    //-----

    return result;
}

//---------------------------------------------------------------------
