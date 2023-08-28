#include "HCTree.hpp"
//#include <vector>

//Parsing the command line arguments
int main(int argc, char* argv[]){
    //Throwing an error message, if user runs error incorrectly
    if(argc != 3){
        cout << "ERROR: Incorrect parameters" << endl;
        cout << "./refcompress <original_file> <compressed_file>" <<endl;
    }


    //Opening the input file for reading
    FancyInputStream input(argv[1]);

    if(input.filesize() == 0){
        FancyOutputStream output(argv[2]);
        return 0;
    }

    //Creating the vector to store the byte and the count
    vector<int> count(256,0);


    // Checking while the byte is valid
    while(input.good()){
        //Creating a variable that will store the byte
        int idx = input.read_byte();
        //Checking the next line which should be the current line
        if(!input.good()){
             break;
        }

        //Checking if the byte has previously been found
        count[idx] += 1;
    }

    HCTree hp;

    hp.build(count);


    FancyOutputStream output(argv[2]);

    //Step 6: "file header ? "
    for(unsigned int i = 0; i < count.size(); i++){
        int modified = count[i];
        output.write_int(modified);
    }

    //Step 7: Moving back to the beginning of the input file
    input.reset();

    //Going through the input once more
    while(input.good()){
        //Creating a variable that will store the byte
        char idx = input.read_byte();
        //Checking the next line which should be the current line
        if(!input.good()){
             break;
        }

        hp.encode(idx, output);
    }

    return 0;
}
