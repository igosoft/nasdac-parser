
#include "src/client_handler.h"
#include "src/data_feeder.h"
#include "src/observer.h"
#include "src/parser.h"
#include <iostream>

int main(int argc, char const *argv[]) {

  std::string file_path(
      "/home/igor/Projects/c++/nasdaq/data/01302019.NASDAQ_ITCH50");

  ClientHandler client_handler;
  MarkerObserver<ClientHandler> observer(client_handler);
  ItchParser<MarkerObserver<ClientHandler>> itch_parser(observer);
  DataFeeder<ItchParser<MarkerObserver<ClientHandler>>> data_feeder(
      itch_parser);

  try {
    data_feeder.open_data_source(file_path.data());
  } catch (std::ios::failure e) {
    std::cout << "[ERROR] Can't open data source file=" << argv[1] << " due to "
              << e.what() << "\n";
    return 1;
  }

  data_feeder.open();

  return 0;
}
