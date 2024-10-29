#include "file.h"

#include <fstream>
#include <sys/stat.h>

#include <iostream>


namespace func_FileMap {
    void load_MapFile(std::string dir, MapFile& _mapFile) {
        //load file
        std::ifstream file(dir, std::ios::binary);
        if(file.fail()) throw std::runtime_error("enable to open file " + dir);
        //get size
        file.seekg(0, std::ios::end);
        _mapFile.m_length = file.tellg();
        file.seekg(0, std::ios::beg);
        //allocate memory for the file contents
        _mapFile.m_begin = new char[_mapFile.m_length];
        if(!_mapFile.m_begin) throw std::runtime_error("enable to allocate memory for file " + dir);
        //read the file into memory
        file.read(_mapFile.m_begin, _mapFile.m_length);
        if(!file) throw std::runtime_error("enable to read file " + dir);
        //finally return
        file.close();
    }
    void print_MapFile(MapFile& _mapFile) {
        std::cout << "Length: " << _mapFile.m_length << " bytes" << std::endl;
        if (_mapFile.m_length > 0 && _mapFile.m_begin != nullptr) {
            std::cout << "Contents: " << std::endl;
            std::cout.write(_mapFile.m_begin, _mapFile.m_length);
            std::cout << std::endl; // Add a newline after printing contents
        } else {
            std::cout << "File is empty or not loaded." << std::endl;
        }
    }
    void destroy_MapFile(MapFile& _mapFile) {
        delete[] _mapFile.m_begin;
        _mapFile.m_length = 0;
    }
};