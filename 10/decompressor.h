#pragma once

#include <string>
#include <fstream>

inline bool DecodeRLE(const std::string& src_name, const std::string& dst_name) {
    std::ifstream in(src_name, std::ios::binary);
    if (!in) {
        return false;
    }

    std::ofstream out(dst_name, std::ios::binary);
    if (!out) {
        return false;
    }

    unsigned char header;
    while (in.get(reinterpret_cast<char&>(header))) {
        int block_type = (header & 1);
        int data_size = (header >> 1) + 1;

        if (block_type) {
            unsigned char data;
            if (!in.get(reinterpret_cast<char&>(data))) {
                return false;
            }

            std::string repeated_data(data_size, static_cast<char>(data));
            out.write(repeated_data.c_str(), repeated_data.size());
        } else {
            char* buffer = new char[data_size];
            if (!in.read(buffer, data_size)) {
                delete[] buffer;
                return false;
            }

            out.write(buffer, data_size);
            delete[] buffer;
        }
    }

    return true;
}