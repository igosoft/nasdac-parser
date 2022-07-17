#pragma once

#ifndef BSWAP_H
#define BSWAP_H

#include <stdint.h>

namespace bswap {
// to little endian
uint32_t swap2bytes(const void *buf) {
  return __builtin_bswap16(*static_cast<const uint16_t *>(buf));
}

uint32_t swap4bytes(const void *buf) {
  return __builtin_bswap32(*static_cast<const uint32_t *>(buf));
}

uint64_t swap6bytes(const char *buf) {
  return (__builtin_bswap64(
              *reinterpret_cast<uint64_t *>(const_cast<char *>(buf))) &
          (((1L << 48) - 1) << 16)) >>
         16;
}
uint64_t swap8bytes(const void *buf) {
  return __builtin_bswap64(*static_cast<const uint64_t *>(buf));
}

// uint64_t swap8(const void *buf) {
//   return __builtin_bswap64(*static_cast<const uint64_t *>(buf));
// }

} // namespace bswap

#endif