cd /home/students_home/11812005/CODE/project/cv
command g++ `pkg-config opencv --cflags` -o cv cv.cpp `pkg-config opencv --libs`
./cv
