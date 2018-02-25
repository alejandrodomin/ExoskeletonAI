#include "global.hpp"
#include <gtest/gtest.h>

TEST(NodeFunctions, get_typeHidden){
   Node* node = new Node(1,2);
   EXPECT_EQ(1, node->get_type());
}

int main(int argc, char **argv){
   testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}