#include "global.hpp"
#include <gtest/gtest.h>
#include <list>

TEST(NodeConstructors, get_typeHidden){
   Node* node = new Node(1,2);
   EXPECT_EQ(1, node->get_type());
   delete node;
}

TEST(NodeBoolFunctions, setLayer){
   Node *node = new Node();
   node->set_layer(5);
   EXPECT_EQ(5, node->get_layer());
   delete node;
}

TEST(NodeBoolFunctions, setOutputFunc){
   Node *node = new Node();
   node->set_outputfunc(5);
   EXPECT_EQ(5, node->get_outputfunc());
   delete node;
}

TEST(NodeBoolFunctions, outFunc){
   Node *node = new Node();
   Node *temp = new Node();
   
   list<Gene *> test;
   test.push_back(new Gene(node, temp, 0));

   ASSERT_TRUE(node->out_func(test));

   // delete node;
   // delete temp;
   // for(list<Gene *>::iterator it = test.begin(); it != test.end(); it++){
   //    delete *it;
   // }
   // test.clear();
}

// TEST(NodeBoolFunctions, findLayer){
//    Node *node = new Node(hidden,0);
//    Node *temp = new Node(hidden,1);
   
//    list<Gene *> test;
//    test.push_back(new Gene(node, temp, 0));

//    node->set_layer(0);
//    node->find_layer(test);

//    ASSERT_FALSE(node->get_layer() == 0);

//    delete node;
//    delete temp;
//    for(list<Gene *>::iterator it = test.begin(); it != test.end(); it++){
//       delete *it;
//    }
//    test.clear();
// }

int main(int argc, char **argv){
   testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}