CFLAGS   += -DVERSION="\"$(VERSION)\""
CXXFLAGS += -DVERSION="\"$(VERSION)\""

CXXFLAGS += -std=c++14 -Wall

validator: validator.o rgl.o
	$(CXX) -o validator validator.o rgl.o

clean:
	-rm -f validator.o rgl.o validator
