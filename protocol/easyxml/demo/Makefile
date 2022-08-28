
all :
	g++ -I../src -I../third create.cpp ../src/easyxml.cpp ../third/tinyxml2.cpp -o create
	g++ -I../src -I../third parser.cpp ../src/easyxml.cpp ../third/tinyxml2.cpp -o parser
	
.PHONY: clean
clean:
	@rm -f create
	@rm -f parser
