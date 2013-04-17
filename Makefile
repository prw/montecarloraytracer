CXX=g++
CXXFLAGS=-Ofast -mtune=native -march=native 
DEPS = camera.h  light.h  object.h  point.h  ray.h  render.h  scene.h  tracer.h  vector.h
OBJ = camera.o  light.o  object.o  point.o  ray.o  scene.o  trace.o  tracer.o  vector.o


%.o: %.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

tracer: $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)

clean:
	rm -v *.o tracer
