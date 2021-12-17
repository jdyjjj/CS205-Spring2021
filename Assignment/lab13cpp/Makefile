CC = g++
TARGET = main
OBJ = main.o CStereoShape.o CCube.o CSphere.o

CFLAGES = -c -Wall

$(TARGET): $(OBJ)
	$(CC) -o $(TARGET) $(OBJ)

main.o:main.cpp
	$(CC) -c main.cpp

CStereoShape.o:CStereoShape.cpp
	$(CC) -c CStereoShape.cpp

CCube.o:CCube.cpp
	$(CC) -c CCube.cpp

CSphere.o:CSphere.cpp
	$(CC) -c CSphere.cpp