CC = g++
CFLAGS = -g -Wall -Wextra -Werror --std=c++17
CRITERION_LINK = -lcriterion

NAME = matt-daemon
TEST_NAME = test_suite

SRC_DIR = src
OBJ_DIR = obj
TEST_DIR = tests

SRCS =	$(wildcard $(SRC_DIR)/logging/*.cpp) \
	$(wildcard $(SRC_DIR)/*.cpp) \

OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
TESTS = $(wildcard $(TEST_DIR)/*.cpp)

.PHONY: all
all: help

.PHONY: help
help: ## Prints help for targets with comments
	@echo "Available Rules:"
	@cat $(MAKEFILE_LIST) | grep -E '^[a-zA-Z_-]+:.*?## .*$$' | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

.PHONY: b
build: $(NAME) ## Builds the executable

.PHONY: clean
clean: ## Deletes transitive dependencies
	@rm -f $(OBJS)

.PHONY: fclean 
fclean: clean ## Deletes transitive dependencies + the executable
	@rm -f $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@$(CC) $(CFLAGS) -c $(CFLAGS) $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(TEST_NAME): $(OBJS) $(TESTS)
	$(CC) $(CFLAGS) $(CRITERION_LINK) $(TESTS) $(OBJS) -o $(TEST_DIR)/$(TEST_NAME)

.PHONY: test
test: $(TEST_NAME) ## Compiles and run the tests
	$(TEST_DIR)/$(TEST_NAME)

.PHONY: del-lock
del-lock: ## Delete the lockfile at /var/lock/matt_daemon.lock
	@rm -f /var/lock/matt_daemon.lock
