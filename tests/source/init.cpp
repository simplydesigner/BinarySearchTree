#include <BinarySearchTree.hpp>
#include <catch.hpp>
#include <fstream>

SCENARIO("BST init with initializer list", "[init]") {
	BinarySearchTree<int> tree = {8};
	REQUIRE( tree.size() == 1 );
}

SCENARIO("BST search inserted element", "[search]") {
	BinarySearchTree<int> tree = {8, 4, 3};
	REQUIRE( tree.find(4) );
}

SCENARIO("BST search non inserted element", "[search]") {
	BinarySearchTree<int> tree = {8, 4, 3};
	REQUIRE( !tree.find(5) );
}

// 				+----+
// 				|-08-|									*
// 				+----+
//
//
// 						 				 08
// 						 				---->
SCENARIO("BST delete non inserted element", "[delete]") {
	BinarySearchTree<int> tree = {8};
	REQUIRE( !tree.remove(4) );
	REQUIRE( !tree.isEmpty() );
}

// 				+----+
// 				|-08-|									*
// 				+----+
//
//
// 						 				 08
// 						 				---->
SCENARIO("BST delete root without children", "[delete]") {
	BinarySearchTree<int> tree = {8};
	REQUIRE( tree.remove(8) );
	REQUIRE( tree.isEmpty() );
}

//              +----+                                              +----+
//              |-08-|                                              | 04 |
//              +----+                                              +----+
//                /                                                   /
//               /                                                   /
//         +----+                                              +----+
//         | 04 |                                              | 03 |
//         +----+                                              +----+
//           /
//          /
//    +----+                              08
//    | 03 |                             ---->
//    +----+
SCENARIO("BST delete root with one child", "[delete]") {
	BinarySearchTree<int> tree = {8, 4, 3};
	REQUIRE( tree.remove(8) );
	REQUIRE( tree == BinarySearchTree<int>({4, 3}) );
}

//                +----+                                              +----+
//                |-08-|                                              | 09 |
//                +----+                                              +----+
//                  /\                                                  /\
//                 /  \                                                /  \
//           +----+    +----+                                    +----+    +----+
//           | 04 |    | 10 |                                    | 04 |    | 10 |
//           +----+    +----+                                    +----+    +----+
//             /         /\                                        /          \
//            /         /  \                                      /            \
//      +----+    +----+    +----+          08              +----+              +----+
//      | 03 |    | 09 |    | 13 |         ---->            | 03 |              | 13 |
//      +----+    +----+    +----+                          +----+              +----+
//                            /                                                   /
//                           /                                                   /
//                     +----+                                              +----+
//                     | 11 |                                              | 11 |
//                     +----+                                              +----+
//                        \                                                   \
//                         \                                                   \
//                          +----+                                              +----+
//                          | 12 |                                              | 12 |
//                          +----+                                              +----+
SCENARIO("BST delete root with children", "[delete]") {
	BinarySearchTree<int> tree = {8, 4, 3, 10, 9, 13, 11, 12};
	REQUIRE( tree.remove(8) );
	REQUIRE( tree == BinarySearchTree<int>({9, 4, 3, 10, 13, 11, 12}) );
}

//                +----+                                              +----+
//                | 08 |                                              | 08 |
//                +----+                                              +----+
//                  /\                                                  /\
//                 /  \                                                /  \
//           +----+    +----+                                    +----+    +----+
//           | 04 |    | 10 |                                    | 04 |    | 10 |
//           +----+    +----+                                    +----+    +----+
//             /         /\                                                  /\
//            /         /  \                                                /  \
//      +----+    +----+    +----+          03                        +----+    +----+
//      |-03-|    | 09 |    | 13 |         ---->                      | 09 |    | 13 |
//      +----+    +----+    +----+                                    +----+    +----+
//                            /                                                   /
//                           /                                                   /
//                     +----+                                              +----+
//                     | 11 |                                              | 11 |
//                     +----+                                              +----+
//                        \                                                   \
//                         \                                                   \
//                          +----+                                              +----+
//                          | 12 |                                              | 12 |
//                          +----+                                              +----+
SCENARIO("BST delete non root without children", "[delete]") {
	BinarySearchTree<int> tree = {8, 4, 3, 10, 9, 13, 11, 12};
	REQUIRE( tree.remove(3) );
	REQUIRE( tree == BinarySearchTree<int>({8, 4, 10, 9, 13, 11, 12}) );
}

//                +----+                                              +----+
//                | 08 |                                              | 08 |
//                +----+                                              +----+
//                  /\                                                  /\
//                 /  \                                                /  \
//           +----+    +----+                                    +----+    +----+
//           | 04 |    | 10 |                                    | 04 |    | 10 |
//           +----+    +----+                                    +----+    +----+
//             /         /\                                        /         /\
//            /         /  \                                      /         /  \
//      +----+    +----+    +----+          11              +----+    +----+    +----+
//      | 03 |    | 09 |    | 13 |         ---->            | 03 |    | 09 |    | 13 |
//      +----+    +----+    +----+                          +----+    +----+    +----+
//                            /                                                   /
//                           /                                                   /
//                     +----+                                              +----+
//                     |-11-|                                              | 12 |
//                     +----+                                              +----+
//                        \
//                         \
//                          +----+
//                          | 12 |
//                          +----+
SCENARIO("BST delete non root with one child", "[delete]") {
	BinarySearchTree<int> tree = {8, 4, 3, 10, 9, 13, 11, 12};
	REQUIRE( tree.remove(11) );
	REQUIRE( tree == BinarySearchTree<int>({8, 4, 3, 10, 9, 13, 12}) );
}

//                +----+                                              +----+
//                | 08 |                                              | 08 |
//                +----+                                              +----+
//                  /\                                                  /\
//                 /  \                                                /  \
//           +----+    +----+                                    +----+    +----+
//           | 04 |    |-10-|                                    | 04 |    | 11 |
//           +----+    +----+                                    +----+    +----+
//             /         /\                                        /         /\
//            /         /  \                                      /         /  \
//      +----+    +----+    +----+          10              +----+    +----+    +----+
//      | 03 |    | 09 |    | 13 |         ---->            | 03 |    | 09 |    | 13 |
//      +----+    +----+    +----+                          +----+    +----+    +----+
//                            /                                                   /
//                           /                                                   /
//                     +----+                                              +----+
//                     | 11 |                                              | 12 |
//                     +----+                                              +----+
//                        \
//                         \
//                          +----+
//                          | 12 |
//                          +----+
SCENARIO("BST delete non root with children", "[delete]") {
	BinarySearchTree<int> tree = {8, 4, 3, 10, 9, 13, 11, 12};
	REQUIRE( tree.remove(10) );
	REQUIRE( tree == BinarySearchTree<int>({8, 4, 3, 11, 9, 13, 12}) );
}
