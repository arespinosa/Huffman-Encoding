#include "HCTree.hpp"
#include <bits/stdc++.h>

//Implementing the skeletons of the HCTree functions

/**
 * Implement the HCTree destructor
 */

// Creating a helper function to clear everything from the HCNodes
void postorder(HCNode* curr){
   if(curr == nullptr){
      return;
   }

   if(curr -> c0 != nullptr){
      postorder(curr -> c0);
   }

   if(curr -> c1 != nullptr){
      postorder(curr -> c1);
   }

   delete curr;
}


HCTree::~HCTree() {
   postorder(root);
   root = nullptr;

}

/**
* Use the Huffman algorithm to build a Huffman coding tree.
* PRECONDITION: freqs is a vector of ints, such that freqs[i] is the frequency of occurrence of byte i in the input file.
* POSTCONDITION: root points to the root of the trie, and leaves[i] points to the leaf node containing byte i.
*/

 void HCTree::build(const vector<int>& freqs){

   //Creating the priority queue from Design Notes
   priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> pq;

   //Storing the intial PQ
   for(unsigned int i = 0; i < freqs.size(); i++){
      if(freqs[i] > 0){
         //Creating a new HCNode which stores the freqs and typecasts i
         HCNode* temp = new HCNode(freqs[i], (char)i );
         pq.push(temp);
         //Store the leaves vector
         leaves[i] =temp;
      }
   }

   //Update: Checking to see if we have an empty file
   if(pq.size() == 0){
      root = nullptr;
      return;
   }

   //Creating a while loop to check for pq's size which should have more than one tree
   while(pq.size() != 1){
      // Now creating two variables with lowest frequencies
      HCNode* T1 = pq.top();
      pq.pop();
      HCNode* T2 = pq.top();
      pq.pop();

      //Creating a newer node with the combined frequencies
      HCNode* new_node = new HCNode(T1 -> count + T2 -> count, T1 -> symbol);
      new_node -> c0 = T1;
      new_node -> c1 = T2;

      T2 -> p = new_node;
      T1 -> p = new_node;

      //Inserting this back into the priority queue
      pq.push(new_node);
   }

   //After we are done with the Huffman Tree, instantiating the root
   if(pq.size() == 1){
      root = pq.top();
   }


   return;


}

/**
* Write to the given FancyOutputStream the sequence of bits coding the given symbol.
* PRECONDITION: build() has been called, to create the coding tree, and initialize root pointer and leaves vector.
*/
void HCTree::encode(unsigned char symbol, FancyOutputStream & out) const{
   //Creating a member variable
   HCNode* curr;

   // Checking if the symbol is in the leaves vector
   curr = leaves[symbol];

   //Creating a vector<int> that will be used to store the path from leaf to root
   vector<int> path;



   //Traversing up the tree
   while(curr != root){
      //If it's on the right side, signifying a 1
      if(curr == curr -> p -> c1){
         path.push_back(1);
      }
      else{
         path.push_back(0);
      }

      //Going up one
      curr = curr -> p;

   }

   //Flipping the vector path to get the path of root to leaves
   reverse(path.begin(), path.end());

   //Writing it to the given FancyOutputStream
   for(unsigned int i = 0; i < path.size(); i++){
      out.write_bit(path[i]);
   }

   //After all that is done, just returning the function
   return;
}

/**
* Return symbol coded in the next sequence of bits from the stream.
* PRECONDITION: build() has been called, to create the coding tree, and initialize root pointer and leaves vector.
*/
unsigned char HCTree::decode(FancyInputStream & in) const{
   //Creating a node that will intially start at the root
   HCNode* curr = root;

   while(curr -> c1 != nullptr && curr -> c0 != nullptr){
      //step into the file  from the input stream
      int edge = in.read_bit();
      if(edge == 1){
         curr = curr -> c1;
      }
      else{
         curr = curr -> c0;
      }
   }

   return curr -> symbol;
}
