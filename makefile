BIN_DIR = bin
CC = g++
CPPFLAGS = -g -Wall 

all: $(BIN_DIR)/.dirstamp most_active_cookie

most_active_cookie: most_active_cookie.cpp $(BIN_DIR)/CookieLogger.o
	$(CXX) $(CPPFLAGS) $^ -o $@

$(BIN_DIR)/CookieLogger.o: CookieLogger.cpp CookieLogger.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

.phony: clean test

clean:
	-@rm -rf $(BIN_DIR)

$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp