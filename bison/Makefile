CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra

all: upl_parser

# Tạo file parser từ upl.y trước
upl.tab.cpp upl.tab.hpp: upl.y
	bison -d -o upl.tab.cpp upl.y

# Biên dịch các file object
upl.tab.o: upl.tab.cpp
	$(CXX) $(CXXFLAGS) -c upl.tab.cpp -o upl.tab.o

lexer.o: lexer.cpp lexer.hpp
	$(CXX) $(CXXFLAGS) -c lexer.cpp -o lexer.o

parser_driver.o: parser_driver.cpp lexer.hpp upl_types.h
	$(CXX) $(CXXFLAGS) -c parser_driver.cpp -o parser_driver.o

# Liên kết các file object thành executable
upl_parser: parser_driver.o lexer.o upl.tab.o
	$(CXX) $(CXXFLAGS) -o $@ $^

# Mục tiêu dọn dẹp
clean:
	rm -f *.o upl_parser upl.tab.cpp upl.tab.hpp

# Đảm bảo make biết các mục tiêu này là mục tiêu, không phải tên file
.PHONY: all clean