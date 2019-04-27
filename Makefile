G++ = g++ -std=c++11
BUILD = out
EXECUTABLE = tp3
SRC_DIR = src
SRC_FILES = $(wildcard $(SRC_DIR)/*)
ifdef OUT
OUTPUT = $(OUT)/
endif

.PHONY : directories
.PHONY : release

all: directories $(OUTPUT)$(EXECUTABLE)

directories: $(BUILD)

release: $(EXECUTABLE).tar.gz

$(EXECUTABLE).tar.gz:
	tar cvf $(EXECUTABLE).tar $(SRC_DIR)/ Makefile
	gzip -f $(EXECUTABLE).tar

$(BUILD):
	mkdir -p $(BUILD)

$(OUTPUT)$(EXECUTABLE): $(BUILD)/main.o $(BUILD)/DocumentXML.o $(BUILD)/Histoire.o $(BUILD)/Phrase.o
	$(G++) -o $(OUTPUT)$(EXECUTABLE) $(BUILD)/*.o

$(BUILD)/main.o: $(SRC_DIR)/inf3105.cpp $(SRC_DIR)/graphe.h $(BUILD)/Histoire.o $(BUILD)/DocumentXML.o
	$(G++) -o $(BUILD)/main.o -c $(SRC_DIR)/inf3105.cpp

$(BUILD)/DocumentXML.o: $(SRC_DIR)/DocumentXML.cpp $(SRC_DIR)/DocumentXML.h
	$(G++) -o $(BUILD)/DocumentXML.o -c $(SRC_DIR)/DocumentXML.cpp

$(BUILD)/Histoire.o: $(SRC_DIR)/Histoire.cpp $(SRC_DIR)/Histoire.h $(BUILD)/DocumentXML.o $(BUILD)/Phrase.o
	$(G++) -o $(BUILD)/Histoire.o -c $(SRC_DIR)/Histoire.cpp

$(BUILD)/Phrase.o: $(SRC_DIR)/Phrase.cpp $(SRC_DIR)/Phrase.h
	$(G++) -o $(BUILD)/Phrase.o -c $(SRC_DIR)/Phrase.cpp

clean:
	rm -fr $(BUILD)

clean-all:
	rm -fr $(BUILD)/ $(OUTPUT)$(EXECUTABLE) $(EXECUTABLE).tar.gz

.PHONY: clean
.PHONY: clean-all
