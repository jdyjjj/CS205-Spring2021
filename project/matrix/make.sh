cd /home/students_home/11812005/CODE/project/matrix
command g++ `pkg-config opencv --cflags` -o main test.cpp matrix.cpp ../complex/complex.cpp `pkg-config opencv --libs`
./main
