#include <iostream>
#include <stdlib.h>
#include "HCTree.hpp"

using namespace std;

/**
 * Define messages for use in the tester
 */
#define MESSAGE_SUCCESS "Success"
#define MESSAGE_INCORRECT "Your build() function returned the wrong node"

/**
 * Test BST class using numbers from standard input
 */
int main() {
    void postorder(HCNode* curr){
     if(curr == nullptr){
         return;
     }


     if(curr -> c0 != nullptr){
         postorder(curr -> c0);
         //postorder(curr);
     }

     if(curr -> c1 != nullptr){
         postorder(curr -> c1);

     }
     cout << curr -> symbol
     cout << "This is curr's right child "<< curr -> c1 << endl;
     cout << "This is curr's left child " <<  curr -> c0 << endl
     }




    return 0;

}
