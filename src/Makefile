# Makefile - do not edit!

# Include project file 
include $(wildcard *.pro)

# Search path for source and header files
VPATH = $(DEPENDPATH)
INCLUDE = $(addprefix -I,$(INCLUDEPATH))

# Objects
OBJECTS = $(subst .cpp,.o,$(notdir $(SOURCES)))

# Choose compiler and linker
COMPILER = $(COMPILE.cpp)
LINKER = $(LINK.cpp)

# Build targets
$(TARGET): $(OBJECTS)
	$(LINKER) -o $@ $^

%.o: %.cpp
	$(COMPILER) $(INCLUDE) -O2 -MMD -MP -MF .depends/$@.d -o $@ $<

# Clean targets
.PHONY: clean
clean:
	rm -rf *.o .depends $(TARGET)

# Create dependencies directory
$(shell [ ! -e .depends ] && mkdir .depends)

# Enable dependency checking
DEPENDS = $(wildcard .depends/*.d)
ifneq ($(DEPENDS),)
include $(DEPENDS)
endif
