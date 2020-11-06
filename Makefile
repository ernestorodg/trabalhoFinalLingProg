CXX    = g++
CXFLAGS =  -Wall -I $(IDIR)

IDIR = lib
ODIR = obj
SDIR = src
LIBS = sqlite3

_DEP = dataBank.h extra.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEP))

_OBJ = main.o dataBank.o extra.o
OBJS = $(patsubst %,$(ODIR)/%,$(_OBJ))

EXEC = exercicio

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CXX) -c -o $@ $< $(CXFLAGS) -l $(LIBS) 

$(EXEC): $(OBJS)
	$(CXX) -o $@ $^ $(CXFLAGS) -l $(LIBS)

.PHONY: clean

clean:
	rm -f $(EXEC) $(ODIR)/*.o *~ core