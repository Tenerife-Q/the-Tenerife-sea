CC = gcc
CFLAGS = -Wall -g
SRC_DIR = src
TRAVERSAL_DIR = $(SRC_DIR)/traversals
OBJ = $(SRC_DIR)/main.o $(SRC_DIR)/binary_tree.o \
      $(TRAVERSAL_DIR)/preorder_recursive.o \
      $(TRAVERSAL_DIR)/inorder_recursive.o \
      $(TRAVERSAL_DIR)/postorder_non_recursive.o \
      $(TRAVERSAL_DIR)/levelorder_recursive.o \
      $(TRAVERSAL_DIR)/levelorder_non_recursive.o
TARGET = binary_tree_traversal

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(SRC_DIR)/main.o: $(SRC_DIR)/main.c $(SRC_DIR)/binary_tree.h
	$(CC) $(CFLAGS) -c $< -o $@

$(SRC_DIR)/binary_tree.o: $(SRC_DIR)/binary_tree.c $(SRC_DIR)/binary_tree.h
	$(CC) $(CFLAGS) -c $< -o $@

$(TRAVERSAL_DIR)/preorder_recursive.o: $(TRAVERSAL_DIR)/preorder_recursive.c $(SRC_DIR)/binary_tree.h
	$(CC) $(CFLAGS) -c $< -o $@

$(TRAVERSAL_DIR)/inorder_recursive.o: $(TRAVERSAL_DIR)/inorder_recursive.c $(SRC_DIR)/binary_tree.h
	$(CC) $(CFLAGS) -c $< -o $@

$(TRAVERSAL_DIR)/postorder_non_recursive.o: $(TRAVERSAL_DIR)/postorder_non_recursive.c $(SRC_DIR)/binary_tree.h
	$(CC) $(CFLAGS) -c $< -o $@

$(TRAVERSAL_DIR)/levelorder_recursive.o: $(TRAVERSAL_DIR)/levelorder_recursive.c $(SRC_DIR)/binary_tree.h
	$(CC) $(CFLAGS) -c $< -o $@

$(TRAVERSAL_DIR)/levelorder_non_recursive.o: $(TRAVERSAL_DIR)/levelorder_non_recursive.c $(SRC_DIR)/binary_tree.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)