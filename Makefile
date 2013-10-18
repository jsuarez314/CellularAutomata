CXX = g++
CFLAGS = `root-config --cflags`
LFLAGS = `root-config --glibs`

TARGET = CellularAutomata.exe

all: $(TARGET)

CellularAutomata.exe : CellularAutomata.o Dict.o Application.o
	$(CXX) -o $@ $^ $(LFLAGS) 

%.o: %.cxx
	$(CXX) $(CFLAGS) -c $<

Dict.cxx : CellularAutomata.h
	@rootcint -f $@ -c $^

clean:
	@rm *.o *.d CellularAutomata.exe Dict.h Dict.cxx
