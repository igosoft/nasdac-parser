
#ifndef OBSERVER_H
#define OBSERVER_H
#include "client_handler.h"
#include "messages.h"
#include <iomanip>

struct Order {};

struct OrderBook {

  void add(Order &&order) {}

private:
  // _order_book
};

template <typename Client> class MarkerObserver {
private:
  Client &_client;
  // OderBook _order_book = std::move(Factory::orderBook().build());
public:
  MarkerObserver(Client &client) : _client(client) {
    std::setw(2);
    std::setfill('0');
  }
  ~MarkerObserver() {}

  // Orders
  void addOrder(OrderMessage &order_message) {
    // auto order = Factory::order(order_message).build();
    //
    //_client.onOrder(order_message);

    // std::cout << "\r" << std::string(__FUNCTION__) << " " << std::flush;
  }
  void executedOrder(OrderMessage &orderMessage) {
    // std::cout << "\r" << __FUNCTION__ << " " << std::flush;
  }
  void executedWithPriceOrder(OrderMessage &orderMessage) {
    // std::cout << "\r" << __FUNCTION__ << " " << std::flush;
  }
  void cancelOrder(OrderMessage &orderMessage) {
    // std::cout << "\r" << __FUNCTION__ << " " << std::flush;
  }
  void deleteOrder(OrderMessage &orderMessage) {
    // std::cout << "\r" << __FUNCTION__ << " " << std::flush;
  }
  void replaceOrder(OrderMessage &orderMessage) {
    // std::cout << "\r" << __FUNCTION__ << " " << std::flush;
  }

  // Events
  void systemEvent(OrderMessage &&orderMessage) {
    // std::cout << __FUNCTION__ << " " << std::flush;
  }
};
#endif // !OBSERVER_H
