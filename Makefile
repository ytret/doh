.PHONY: all clean

SOURCES := main.cpp
OBJECTS := $(SOURCES:.cpp=.o)

OUTPUT := doh

CXXFLAGS := -fPIC

INCLUDEDIRS := -I/usr/include/qt \
               -I/usr/include/qt/QtCore \
	       -I/usr/include/qt/QtGui

LIBS := -lQt5Core -lQt5Gui

MOC_HEADERS :=
MOC_HEADERS_OUTPUT := $(addprefix moc_,$(MOC_HEADERS))

all: $(OUTPUT)

moc_%.h: %.h
	moc $^ -o $@

$(OUTPUT): $(OBJECTS) $(MOC_HEADERS_OUTPUT)
	g++ $(OBJECTS) -o $@ $(LIBS)

%.o: %.cpp
	g++ -c $^ -o $@ $(INCLUDEDIRS) $(CXXFLAGS)

clean:
	rm -rf $(MOC_HEADERS_OUTPUT) $(OBJECTS) $(OUTPUT)
