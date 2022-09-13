

#./darknet detector test ./cfg/coco.data ./cfg/yolov3.cfg ./yolov3.weights data/dog.jpg -i 0 -thresh 0.25


#./darknet detector test ./data/_obj_head.data _yolov3-tiny.cfg _yolov3-tiny_2500.weights _mad_camera_png2_00031.jpg -i 0 -thresh 0.20

# _mad_camera_3.mp4 0.20

./darknet detector test ./data/_obj_head.data _yolov3-tiny.cfg _yolov3-tiny_2675.weights ../Desktop/_image.jpg -i 0 -thresh 0.25 -save_labels 1 -dont_show 1
