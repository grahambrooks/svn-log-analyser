SRC		= src
TEST_SRC	= test
BUILD		=	build

LIBS		= 	/usr/local/lib/libboost_filesystem.a \
			/usr/local/lib/libboost_system.a \
			/usr/local/lib/libboost_regex.a \
			/usr/local/lib/libboost_program_options.a

TEST_LIBS	= 	/usr/local/lib/libboost_unit_test_framework.a 

objects 	= 	$(BUILD)/svn_log_parser.o \
			$(BUILD)/report_writer.o \
			$(BUILD)/options_parser.o \
			$(BUILD)/file_filter.o

test_objects	=	$(BUILD)/test_utils.o \
			$(BUILD)/test_svn_log_parser.o \
			$(BUILD)/test_file_filter.o

all:    svn-log-analyser	\
	test

svn-log-analyser :	$(objects) $(BUILD)/main.o
	c++ $^ -o $@ $(LIBS)

test: svn-log-analyser-test
	./$^

svn-log-analyser-test: $(objects) $(test_objects) $(BUILD)/test_main.o
	c++ $^ -o $@ $(LIBS) $(TEST_LIBS)

$(BUILD)/%.o : $(TEST_SRC)/%.cpp
	c++ -I src -c $< -o $@

$(BUILD)/%.o : $(SRC)/%.cpp $(SRC)/%.hpp
	c++ -I src -I /usr/local/include -c $< -o $@

clean:
	-rm -f $(BUILD)/*
	-rm svn-log-analyser
	-rm svn-log-analyser-test
build:
	mkdir build