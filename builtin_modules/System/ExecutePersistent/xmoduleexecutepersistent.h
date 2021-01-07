#ifndef XMODULEEXECUTEPERSISTENT_H
#define XMODULEEXECUTEPERSISTENT_H

/*
ExecutePersistent - a realtime link between Xclu and other programs such as Python.

Now you are able to use power of Python equipped with machine learning libraries 
such as Tensor Flow with realtime graphics, sound and Arduino in Xclu!

Because you may set up Python and CUDA independently of Xclu, 
currently it's the most flexible way of using machine learning algorithms in Xclu.

Technically, the communication goes through input and output console channels. 
It's fast and requires minimal changes of your original Python code.

### Python connection
https://en.wikiversity.org/wiki/Python_Concepts/Console_Output


### Credits
Thanks Pavel Vasev and Michail Bakhterev, who use the approach in their projects 
and demonstrate me it's powerfullness.

Article on this:
Bakhterev M.O., Vasev P.A., One method for visualizing the results of supercomputer calculations 
//Proceedings of the III All-Russian Scientific and Technical Conference 
"Supercomputer Technologies" (SKT-2014), September 29 - October 4, 2014. 
Taganrog, NII MVS SFedU. S. 50-55.
https://data2.lact.ru/f1/s/0/299/basic/1605/976/vasev-4.doc

*/

#include "sdk_h.h"
#include "xmodule.h"

class XModuleExecutePersistent: public XModule
{
public:
    XModuleExecutePersistent(QString class_name);
    ~XModuleExecutePersistent();
protected:
#include "auto.h"

    virtual void on_loaded() {}
    virtual void start();
    virtual void update();
    virtual void stop();

};



#endif // XMODULEEXECUTEPERSISTENT_H
