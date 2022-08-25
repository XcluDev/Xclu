#ifndef XMODULEMADROBOT_H
#define XMODULEMADROBOT_H

//EmoAI
#include "sdk_h.h"
#include "xraster.h"
#include "xmodulewidget.h"

/*

-------------- Running YOLO to work with this module (for Jetson Nano)
1) Change darknet sources:
   at detector.c, void test_detector:
  After:
      while (1) {
        if (filename) {
          ...
        }
  Put:
    //Waiting that somebody erases _image.txt   //DENIS
    //add #include <unistd.h> if required
    char labelpath[4096];
        replace_image_to_label(input, labelpath);

    bool printed = false;
    while (1) {
          FILE* fr = fopen(labelpath, "rb");
          if (fr) {
            fclose(fr);
            if (!printed) {
 printf("    waiting when you delete %s...\n", labelpath);
              printed = true;
            }
            usleep(50);
            continue;
          }
          else {
            break;
          }
    }


  Comment this line:
        //if (filename) break; //LOOP!!!! DENIS

  Open terminal and call "make" to build darknet.

  Now YOLO will process images endlessly and will
  wait while you delete _images.txt.


2) Create _image_yolov3.sh file - and run it to start YOLO:

./darknet detector test ./data/_obj_head.data _yolov3-tiny.cfg _yolov3-tiny_2675.weights ../Desktop/_image.jpg -i 0 -thresh 0.15 -save_labels 1 -dont_show 1

3) Mark it as executable: chmod +x *.sh

4) Now can start start YOLO by running
./_image_yolov3.sh
It will read _image.jpg and write _image.txt, without exiting,
- we will use it by writing images and reading text from Xclu.

Also YOLO will deleting _images.txt before processing - for sync.


  */

class XModuleMadRobot: public XModuleWidget
{
    Q_OBJECT
public:
    XModuleMadRobot(QString class_name);
    virtual ~XModuleMadRobot();

protected:
#include "auto.h"
    virtual void on_loaded() {}
    virtual void start();
    virtual void update();
    virtual void stop();

    virtual void draw(QPainter &painter, int w, int h);

    //web cam image
    XRaster_u8c3 webcam_;   //input image
    XRaster_u8c3 image_;   //transformed image for Python
    XProtectedObject image_gui_;

    //Data from Python
    void parse_yolo();
    //found objects
    QVector<vec2> pnt_;
    QVector<vec2> size_;

    void move_pickup();
    void move_forward();
    void move_backward();
    void move_left();
    void move_right();
    void move_stop();

    QString state_;
    void set_state(QString state);

    void mind_start();
    void mind_stop();

    int mind_on_ = false;
    void mind_update();
    vec2 target_;
    vec2 target_size_;
    float last_pickup = 0;

    const int Pickup = 1;
    const int Forward = 2;
    const int Backward = 3;
    const int Left = 4;
    const int Right = 5;
    const int Stop = 6;

    struct Action {
        int action = 0;
        float end_time = 0;
        Action() {}
        Action(int action0, float end_time0) {
            action = action0;
            end_time = end_time0;
        }
    };
    QVector<Action> queue_;
    void put_action(Action action) {
        queue_.push_back(action);
    }

    //how long no targets
    int no_targets_ = 0;
    bool walking_ = false;

};

#endif // XMODULEMADROBOT_H
