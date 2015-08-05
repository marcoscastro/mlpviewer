CPP    = g++
WINDRES= windres
RM     = rm -f
OBJS   = core/Signal.o \
         core/Neuron.o \
         training/Training.o \
         gui/main.o \
         gui/scaling.o \
         gui/Node.o \
         gui/NeuralNetwork.o \
         gui/Edge.o \
         gui/InputNode.o \
         gui/NeuronNode.o \
         gui/OutputNode.o \
         AppResource.res

LIBS   = -mwindows -L..\..\..\..\..\..\Estudos\C\Projetos\libgui++\trunk\lib -static -lgui_unicode -lgdi32 -lcomctl32 -luxtheme -lpng -ljpeg -lz -lmsimg32 -lgdiplus
CFLAGS = -I..\..\..\..\..\..\Estudos\C\Projetos\libgui++\trunk\include -DUNICODE -fno-diagnostics-show-option

.PHONY: NeuralNetwork.exe clean

all: NeuralNetwork.exe

clean:
	$(RM) $(OBJS) NeuralNetwork.exe

NeuralNetwork.exe: $(OBJS)
	$(CPP) -Wall -o $@ $(OBJS) $(LIBS)

core/Signal.o: core/Signal.cpp core/Signal.h
	$(CPP) -Wall -c $< -o $@ $(CFLAGS)

core/Neuron.o: core/Neuron.cpp core/Neuron.h
	$(CPP) -Wall -c $< -o $@ $(CFLAGS)

training/Training.o: training/Training.cpp training/Training.h
	$(CPP) -Wall -c $< -o $@ $(CFLAGS)

gui/main.o: gui/main.cpp gui/scaling.h gui/NeuralNetwork.h gui/EdgeProperties.h gui/NodeProperties.h
	$(CPP) -Wall -c $< -o $@ $(CFLAGS)

gui/scaling.o: gui/scaling.cpp
	$(CPP) -Wall -c $< -o $@ $(CFLAGS)

gui/Node.o: gui/Node.cpp gui/Node.h
	$(CPP) -Wall -c $< -o $@ $(CFLAGS)

gui/NeuralNetwork.o: gui/NeuralNetwork.cpp gui/NeuralNetwork.h gui/scaling.h
	$(CPP) -Wall -c $< -o $@ $(CFLAGS)

gui/Edge.o: gui/Edge.cpp gui/Edge.h
	$(CPP) -Wall -c $< -o $@ $(CFLAGS)

gui/InputNode.o: gui/InputNode.cpp gui/InputNode.h
	$(CPP) -Wall -c $< -o $@ $(CFLAGS)

gui/NeuronNode.o: gui/NeuronNode.cpp gui/NeuronNode.h
	$(CPP) -Wall -c $< -o $@ $(CFLAGS)

gui/OutputNode.o: gui/OutputNode.cpp gui/OutputNode.h
	$(CPP) -Wall -c $< -o $@ $(CFLAGS)

AppResource.res: AppResource.rc
	$(WINDRES) -i AppResource.rc -J rc -o AppResource.res -O coff

