SRC		= src
TEST_SRC	= test
BUILD		=	build

LIBS		= 	/usr/local/lib/libboost_filesystem.a \
			/usr/local/lib/libboost_system.a \
			/usr/local/lib/libboost_regex.a \
			/usr/local/lib/libboost_program_options.a

TEST_LIBS	= 	/usr/local/lib/libboost_unit_test_framework.a 

objects 	= 	

test_objects	=	

all:    svn-logfile-analyser

svn-logfile-analyser :	$(objects) $(BUILD)/main.o
	c++ $^ -o $@ $(LIBS)

test: svn-logfile-analyser-test
	./$^

svn-logfile-analyser-test: $(objects) $(test_objects) $(BUILD)/test_main.o
	c++ $^ -o $@ $(LIBS) $(TEST_LIBS)

$(BUILD)/%.o : $(TEST_SRC)/%.cpp
	c++ -I src/cpp -c $< -I/src/cpp -o $@

$(BUILD)/%.o : $(SRC)/%.cpp $(SRC)/%.hpp
	c++ -I src/cpp:/usr/local/include -c $< -I/src/cpp -o $@

clean:
	-rm -f $(BUILD)/*
	-rm code
	-rm code-test
build:
	mkdir build