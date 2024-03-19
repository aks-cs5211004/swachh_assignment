## Task 1

Sources:- (https://chat.openai.com/c/50704a7b-5da6-4936-a055-ba788a74ebbc)


The Documentations:-

-  TreeNode Class: Represents a node in a binary search tree (BST). Each node contains a key-value pair and pointers to its left and right children.

-  HybridDataStructure Class: Combines features of a BST and a Hash Map. It maintains a BST to store key-value pairs and a Hash Map for quick lookups. It provides methods for insertion, deletion, search, and finding the nearest key in terms of absolute difference.

-  getRoot() Method: A public method of the HybridDataStructure class that returns a pointer to the root node of the BST.

-   insert() Method: Inserts a key-value pair into the HybridDataStructure. If the key already exists, updates the corresponding value.

-  delete() Method: Removes the key-value pair with the specified key from the HybridDataStructure.

-  search() Method: Searches for the value associated with the given key in the HybridDataStructure. Returns a pointer to the value if found, otherwise returns nullptr.

-  nearest() Method: Finds the value of the nearest key to the given key in terms of absolute difference. Returns the key of the nearest node.

-  nearestHelper() Method: A recursive helper function used by the nearest() method to traverse the BST and find the nearest node to the given key.

-  productsInRange() Function: Takes a HybridDataStructure object, a minimum price, and a maximum price as input. Returns a vector of pairs containing product IDs and their corresponding prices that fall within the specified price range, along with their nearest neighbors outside the range.
