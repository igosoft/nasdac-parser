#pragma once
#include <iostream>
#include <list>
#include <memory>

struct OrderMessage {
  enum class TypeOfOrder : char { BUYER = 'B', SELLER = 'S' };

  uint16_t stock_locate;

  uint64_t order_ref;
  uint64_t new_order_ref;
  OrderMessage::TypeOfOrder bs;
  uint32_t number_shares;
  uint32_t new_number_shares;
  uint64_t stock_symbol;
  uint32_t price;

  uint64_t match_number;
  bool printable;

  uint32_t tracking_number;

  uint64_t timestamp;
};

struct TradeMessage {};

struct SystemMessge {};
