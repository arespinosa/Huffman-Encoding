#include "HCTree.hpp"

int main(int argc, char* argv[]){

    //Opening the input file for reading : Step 1
    FancyInputStream input(argv[1]);
    vector<int> count(256,0);

    if(input.filesize() == 0){
        FancyOutputStream output(argv[2]);
        return 0;
    }

    //Reading the file header of the input file

    if(!input.good()){
        cout << "error";
    }

    int counter = 0;
    for(unsigned int i = 0; i < count.size(); i++){
        int modified = input.read_int();
        count[i] = modified;
        counter += count[i];

    }

    //Creating a HCTree Object
    HCTree ht;

    ht.build(count);
    //Reconstructing the Huffman Tree be using the build function


    //Step 3: Opening the output file for writing
    FancyOutputStream output(argv[2]);

    //Step 4: Using the Huffman Coding tree, decoding the bits
    while(counter != 0){
        output.write_byte(ht.decode(input));
        counter--;
    }

    return 0;
}
