#include <iostream> // Include the iostream library for input and output
#include <cstring> // For std::strcmp
#include <vector>
#include "file.h"

#include <ISOFORGEconfig.h>

//arguments flags, in an array so that latter on, I can Implement a way to change those if needed
const char _flags[2][3] = {
    "-s",   //for source dir : 0
    "-c"    //to create at dir
};

//global varaibles
//std::string dir;
std::string dir;
MapFile testFile;

int main(int argc, char* argv[]) {
    /*
    // Print "Hello, World!" to the console
    std::cout << "Hello, World!" << std::endl;
    std::cout << p_NAME << "  --VERSION: " << p_VERSION_MAJOR << "." << p_VERSION_MINOR << std::endl;
    // Return 0 to indicate successful execution
    return 0;
    */
    try {
        //read arguments
        {
            //convert all commands into strings
            std::vector<std::string> all_args;
            //if there is more than one elements
            if (argc > 1 && (argc-1)%2==0) all_args.assign(argv + 1, argv + argc);
            else throw std::runtime_error("incorect arguments given");
            //for all elements
            for(int i = 0; i < all_args.size();) {
                if(all_args[i]==_flags[0]) {dir=all_args[i+1]; i+=2;}   //if we give a source dir
                else i++;
            }
            //verify that there are no errors
            if(dir=="") throw std::runtime_error("no source-dir given"); 
        }

        //test
        func_FileMap::load_MapFile(dir, testFile);
        func_FileMap::print_MapFile(testFile);
        func_FileMap::destroy_MapFile(testFile);
    }catch(std::exception e) {  //catch errors
        std::cout << "[ERROR] " << e.what() << std::endl;
        return -1;
    }

}

/*
    right now, nothing is really good, I need to find a way to load the file in the RAM, then read it
        to load the file I was thinking of maybe like a struct with a char* and a size, then just pass arround a pointer to this struct for every other classes
        now the question of loading files, we first need to load the ISOFORGE.set to know what the project has for us, this file will be divided into two part
        human readable and just pure data
*/