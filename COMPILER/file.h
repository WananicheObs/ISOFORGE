#pragma once
#include <string>

struct MapFile{
    //std::string m_dir;
    size_t m_length = 0;
    char* m_begin = nullptr;
};

namespace func_FileMap {
    void load_MapFile(std::string dir, MapFile& _mapFile);
    void print_MapFile(MapFile& _mapFile);
    void destroy_MapFile(MapFile& _mapFile);
};