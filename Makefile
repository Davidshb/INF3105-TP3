
G++ = g++ -std=c++11
BUILD = out
ifdef OUT
OUTPUT = $(OUT)/
endif

.PHONY : directories

all: directories $(OUTPUT)tp3

directories: $(BUILD)

$(BUILD):
	mkdir -p $(BUILD)

$(OUTPUT)tp3: $(BUILD)/main.o $(BUILD)/DocumentXML.o $(BUILD)/Histoire.o $(BUILD)/Phrase.o
	$(G++) -o $(OUTPUT)tp3 $(BUILD)/*.o

$(BUILD)/main.o: src/inf3105.cpp src/graphe.h $(BUILD)/Histoire.o $(BUILD)/DocumentXML.o
	$(G++) -o $(BUILD)/main.o -c src/inf3105.cpp

$(BUILD)/DocumentXML.o: src/DocumentXML.cpp src/DocumentXML.h
	$(G++) -o $(BUILD)/DocumentXML.o -c src/DocumentXML.cpp

$(BUILD)/Histoire.o: src/Histoire.cpp src/Histoire.h $(BUILD)/DocumentXML.o $(BUILD)/Phrase.o
	$(G++) -o $(BUILD)/Histoire.o -c src/Histoire.cpp

$(BUILD)/Phrase.o: src/Phrase.cpp src/Phrase.h
	$(G++) -o $(BUILD)/Phrase.o -c src/Phrase.cpp

clean:
	rm -fr $(BUILD)/ tp3

.PHONY: clean
