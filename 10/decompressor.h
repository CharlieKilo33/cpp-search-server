#pragma once

#include <string>
#include <fstream>


inline bool DecodeRLE(const std::string& src_name, const std::string& dst_name){
  std::ifstream in_file(src_name, std::ios::binary);
  if(!in_file.is_open()){
    return false;
  }

  std::ofstream out_file(dst_name, std::ios::binary);
  if(!out_file.is_open()){
    return false;
  }

  unsigned char header = in_file.get();

  while(in_file){
    int block_type = (header & 1);
    int data_size = (header >> 1) + 1;

    if(block_type){
      out_file << in_file.get();
    } else {
      std::string text(static_cast<char>(in_file.get()), data_size);
      out_file << text;

//      for(int i = 0; i < data_size; ++i){
//        out_file << static_cast<char>(in_file.get());
//      }
    }
    header = in_file.get();
  }
  return true;
}