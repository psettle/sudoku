#config
DEBUG=0

#setup
SOURCES=
LIBS=
INCLUDE=

#header includes
INCLUDE += build
INCLUDE += src

#source includes
SOURCES += src/sdk/sdk.cpp
SOURCES += src/sdk/Pipeline.cpp
SOURCES += src/sdk/data/Grid.cpp
SOURCES += src/sdk/data/Digit.cpp
SOURCES += src/sdk/rules/ExclusiveTupleRule.cpp
SOURCES += src/sdk/rules/CollectionRule.cpp
SOURCES += src/sdk/rules/LimitedTupleIdentifier.cpp
SOURCES += src/sdk/rules/LimitedTupleTrimmer.cpp
SOURCES += src/sdk/rules/LimitedTupleMatcher.cpp
SOURCES += src/sdk/rules/AlignedLimitedTupleRule.cpp

#lib includes

#more setup
EXECUTABLE=out/sudoku.exe
EXECUTABLE_MAIN=build/main.cpp
EXECUTABLE_MAIN_O=$(EXECUTABLE_MAIN:%.cpp=out/%.o)

ifeq ($(DEBUG), 1)
	FLAG_BUILD_MODE=-O0 -ggdb3
else
	FLAG_BUILD_MODE=-O3 -ggdb3
endif

LDFLAGS=-Wall $(FLAG_BUILD_MODE)
CC=g++
CFLAGS=-c -MMD -Wall $(FLAG_BUILD_MODE)
OBJECTS=$(SOURCES:.cpp=.o)
OBJECTS_FINAL=$(OBJECTS:%.o=out/%.o)
OBJECTS_FINAL_PLUS_MAIN=$(OBJECTS_FINAL)
OBJECTS_FINAL_PLUS_MAIN+=$(EXECUTABLE_MAIN_O)
DEPENDENCIES=$(OBJECTS_FINAL_PLUS_MAIN:.o=.d)

INCLUDE_FORMATTED=$(addprefix -I, $(INCLUDE))

#targets
.PHONY: all
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS_FINAL) $(EXECUTABLE_MAIN_O)
	@$(CC) $(LDFLAGS) $(OBJECTS_FINAL) $(EXECUTABLE_MAIN_O) $(LIBS) -o $@
	@echo $@

$(OBJECTS_FINAL_PLUS_MAIN): out/%.o : %.cpp
	@mkdir -p out/$(dir $<)
	@$(CC) $(CFLAGS) $(INCLUDE_FORMATTED) $< -o $@
	@echo $<


.PHONY: clean
clean:
	@rm -rf out/*

-include $(DEPENDENCIES)