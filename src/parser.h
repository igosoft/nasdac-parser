#ifndef ITCHPARSER_H
#define ITCHPARSER_H

#include "bswap.h"
#include "messages.h"
#include "observer.h"
#include <iostream>
#include <map>

#define DEBUG

template <typename Observer> class ItchParser {
private:
  Observer &_observer;

  OrderMessage _orderMessage;
  TradeMessage _tradeMesaage;

  std::map<char, std::function<void(const char *)>> _order_parsers;

public:
  ItchParser(Observer &observer) : _observer(observer) {
    auto add = [&](const char *buf) {
      _orderMessage.order_ref = bswap::swap8bytes(buf + 11);
      _orderMessage.bs = buf[19] == 'B' ? OrderMessage::TypeOfOrder::BUYER
                                        : OrderMessage::TypeOfOrder::SELLER;
      _orderMessage.number_shares = bswap::swap4bytes(buf + 20);
      _orderMessage.stock_symbol = bswap::swap8bytes(buf + 24);
      _orderMessage.price = bswap::swap4bytes(buf + 32);

      _observer.addOrder(_orderMessage);
    };

    _order_parsers.emplace('A', add);
  }
  ~ItchParser() {}

  void parse(const char *message) {

    // auto parser_function = _order_parsers[*message];
    // parser_function(message);

    switch (message[0]) {
    case 'A':
    case 'F':
      parseAddOrder(message);
      break;
    case 'E':
      parseExecutedOrder(message);
      break;
    case 'C':
      parseExecutedWithPriceOrder(message);
      break;
    case 'X':
      parseCancelOrder(message);
      break;
    case 'D':
      parseDeleteOrder(message);
      break;
    case 'U':
      parseReplaceOrder(message);
      break;
    case 'S':
      parseSystemEvent(message);
      break;
    default:
      break;
    }
  }

private:
  void parseBaseOrder() {}

  void parseAddOrder(const char *buf) {

    // alt : use address to OrderMessage object , give it to Observer and return
    // to parsering new message auto orderMessage = OrderMessagePool::get();

    _orderMessage.order_ref = bswap::swap8bytes(buf + 11);
    _orderMessage.bs = buf[19] == 'B' ? OrderMessage::TypeOfOrder::BUYER
                                      : OrderMessage::TypeOfOrder::SELLER;
    _orderMessage.number_shares = bswap::swap4bytes(buf + 20);
    _orderMessage.stock_symbol = bswap::swap8bytes(buf + 24);
    _orderMessage.price = bswap::swap4bytes(buf + 32);

    _observer.addOrder(_orderMessage);
  }

  void parseExecutedOrder(const char *buf) {
    _orderMessage.order_ref = bswap::swap8bytes(buf + 11);
    _orderMessage.number_shares = bswap::swap4bytes(buf + 19);
    _orderMessage.match_number = bswap::swap8bytes(buf + 23);

    _observer.executedOrder(_orderMessage);
  }

  void parseExecutedWithPriceOrder(const char *buf) {
    _orderMessage.order_ref = bswap::swap8bytes(buf + 11);
    _orderMessage.number_shares = bswap::swap4bytes(buf + 19);
    _orderMessage.match_number = bswap::swap8bytes(buf + 23);
    _orderMessage.printable = buf[31] == 'Y' ? true : false;
    _orderMessage.price = bswap::swap4bytes(buf + 32);

    _observer.executedWithPriceOrder(_orderMessage);
  }

  void parseCancelOrder(const char *buf) {
    _orderMessage.order_ref = bswap::swap8bytes(buf + 11);
    _orderMessage.number_shares = bswap::swap4bytes(buf + 19);
    _observer.cancelOrder(_orderMessage);
  }

  void parseDeleteOrder(const char *buf) {
    _orderMessage.order_ref = bswap::swap8bytes(buf + 11);

    _observer.deleteOrder(_orderMessage);
  }

  void parseReplaceOrder(const char *buf) {
    _orderMessage.order_ref = bswap::swap8bytes(buf + 11);
    _orderMessage.new_order_ref = bswap::swap8bytes(buf + 19);
    _orderMessage.new_number_shares = bswap::swap4bytes(buf + 27);
    _orderMessage.price = bswap::swap4bytes(buf + 31);

    _observer.replaceOrder(_orderMessage);
  }

  void parseSystemEvent(const char *buf) {
    _orderMessage.tracking_number = bswap::swap2bytes(buf + 3);
    _orderMessage.timestamp = bswap::swap8bytes(buf + 5);
    uint8_t event_code = buf[11];
  }
};
#endif // !ITCHPARSER_H
