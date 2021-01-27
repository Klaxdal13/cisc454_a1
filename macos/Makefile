LDFLAGS = -L. -lglfw -ldl # -lpthread
CXXFLAGS = -g -Wall -Wno-write-strings -Wno-parentheses -DMACOS #-pthread

vpath %.cpp ../src
vpath %.c   ../src/glad/src
vpath %.o   ../obj

OBJS = linalg.o ll.o world.o lander.o landscape.o gpuProgram.o strokefont.o fg_stroke.o glad.o 

EXEC = ll

all:    $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(OBJS) $(LDFLAGS) 

glad.o: ../src/glad/src/glad.c

clean:
	rm -f  *~ $(EXEC) $(OBJS) Makefile.bak

depend:	
	makedepend -Y ../src/*.h ../src/*.cpp 2> /dev/null
	@echo ""
	@echo "Now edit the Makefile to remove the ../src/ prefix of all of the dependences for the .o files"
	@echo ""

# DO NOT DELETE

gpuProgram.o: ../src/headers.h ../src/glad/include/glad/glad.h
gpuProgram.o: ../src/glad/include/KHR/khrplatform.h ../src/linalg.h
headers.o: ../src/glad/include/glad/glad.h
headers.o: ../src/glad/include/KHR/khrplatform.h ../src/linalg.h
lander.o: ../src/headers.h ../src/glad/include/glad/glad.h
lander.o: ../src/glad/include/KHR/khrplatform.h ../src/linalg.h
landscape.o: ../src/headers.h ../src/glad/include/glad/glad.h
landscape.o: ../src/glad/include/KHR/khrplatform.h ../src/linalg.h
strokefont.o: ../src/headers.h ../src/glad/include/glad/glad.h
strokefont.o: ../src/glad/include/KHR/khrplatform.h ../src/linalg.h
world.o: ../src/headers.h ../src/glad/include/glad/glad.h
world.o: ../src/glad/include/KHR/khrplatform.h ../src/linalg.h
world.o: ../src/landscape.h ../src/lander.h ../src/ll.h
fg_stroke.o: ../src/strokefont.h ../src/headers.h
fg_stroke.o: ../src/glad/include/glad/glad.h
fg_stroke.o: ../src/glad/include/KHR/khrplatform.h ../src/linalg.h
gpuProgram.o: ../src/gpuProgram.h ../src/headers.h
gpuProgram.o: ../src/glad/include/glad/glad.h
gpuProgram.o: ../src/glad/include/KHR/khrplatform.h ../src/linalg.h
lander.o: ../src/headers.h ../src/glad/include/glad/glad.h
lander.o: ../src/glad/include/KHR/khrplatform.h ../src/linalg.h
lander.o: ../src/lander.h ../src/world.h ../src/landscape.h
lander.o: ../src/ll.h ../src/gpuProgram.h
landscape.o: ../src/headers.h ../src/glad/include/glad/glad.h
landscape.o: ../src/glad/include/KHR/khrplatform.h ../src/linalg.h
landscape.o: ../src/landscape.h ../src/gpuProgram.h ../src/ll.h
linalg.o: ../src/linalg.h
ll.o: ../src/headers.h ../src/glad/include/glad/glad.h
ll.o: ../src/glad/include/KHR/khrplatform.h ../src/linalg.h
ll.o: ../src/gpuProgram.h ../src/world.h ../src/landscape.h
ll.o: ../src/lander.h ../src/ll.h
strokefont.o: ../src/strokefont.h ../src/headers.h
strokefont.o: ../src/glad/include/glad/glad.h
strokefont.o: ../src/glad/include/KHR/khrplatform.h ../src/linalg.h
strokefont.o: ../src/fg_stroke.h
world.o: ../src/world.h ../src/headers.h
world.o: ../src/glad/include/glad/glad.h
world.o: ../src/glad/include/KHR/khrplatform.h ../src/linalg.h
world.o: ../src/landscape.h ../src/lander.h ../src/ll.h
world.o: ../src/gpuProgram.h ../src/strokefont.h
