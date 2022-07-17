
#ifndef DATA_FEEDER_H
#define DATA_FEEDER_H

#include "bswap.h"
#include <boost/iostreams/device/mapped_file.hpp>
#include <filesystem>

#define MAX_BUFFORE_SIZE 2048

template <typename DataParser> class DataFeeder {
private:
  DataParser &_data_parser;
  boost::iostreams::mapped_file_source _file;

public:
  DataFeeder(DataParser &parser) : _data_parser(parser) {}
  ~DataFeeder() {}

  void open_data_source(const char *file_path) {
    if (_file.is_open()) {
      _file.close();
    }

    _file.open(file_path);
  }

  void open() {
    size_t position = 0;
    int length = 0;
    uint32_t message_couter = 0;
    char buf[MAX_BUFFORE_SIZE];

    assert(_file.is_open() == true);

    while (position <= _file.size()) {
      // Read message length
      length = bswap::swap2bytes(_file.data() + position);
      memcpy(buf, _file.data() + position + 2, length);

      _data_parser.parse(buf);

      message_couter++;
      position += length + 2;
    }
  }
};
#endif // !DATA_FEEDER_H
