CXX = g++
EXEC = solarsystem
SOURCES = main.cpp stars.cpp solarsystem.cpp #
OBJECTS = main.o stars.o solarsystem.o #
LDFLAGS = -lglut -lGL -lGLU 

#默认执行选项，编译链接文件
all :
	$(CXX) -g $(SOURCES) $(LDFLAGS) -o $(EXEC)

#伪命令，清除冗余文件
clean :
	rm -f $(EXEC) *.gdb *.o *~

#伪命令，执行
e :
	./$(EXEC)
