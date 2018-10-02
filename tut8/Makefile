OPENGLLIB= -lGL
GLEWLIB= -lGLEW
GLFWLIB = -lglfw
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB)
LDFLAGS=-L/usr/local/lib 
CPPFLAGS=-I/usr/local/include

BIN=application

SRCS=application.cpp\
	 helper/gl_framework.cpp helper/shader_util.cpp helper/gl_helper.cpp\
	 myclasses/VertexBuffer.cpp myclasses/IndexBuffer.cpp myclasses/VertexArray.cpp

INCLUDES=helper/gl_framework.hpp helper/shader_util.hpp helper/gl_helper.h\
		 myclasses/VertexBuffer.h myclasses/IndexBuffer.h myclasses/VertexArray.h

all: $(BIN)

$(BIN): $(SRCS) $(INCLUDES)
	g++ $(CPPFLAGS) $(SRCS) -o $(BIN) $(LDFLAGS) $(LIBS)

clean:
	rm -f *~ *.o $(BIN)
