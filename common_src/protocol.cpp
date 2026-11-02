#include "protocol.h"

#include <stdexcept>

#include <arpa/inet.h>

#include "constants.h"

Protocol::Protocol(Socket &skt) : skt(skt) {}

void Protocol::send_u8(uint8_t value) {
  int sent = skt.sendall(&value, 1);
  if (sent == 0)
    throw std::runtime_error(SOCKET_CLOSE_SEND_ERROR);

  return;
}

void Protocol::send_u16(uint16_t value) {
  std::uint16_t net = htons(value);
  int sent = skt.sendall(&net, sizeof(net));

  if (sent == 0)
    throw std::runtime_error(SOCKET_CLOSE_SEND_ERROR);
}

uint8_t Protocol::receive_u8() {
  std::uint8_t value = 0;
  int recvd = skt.recvall(&value, 1);

  if (recvd == 0)
    throw std::runtime_error(SOCKET_CLOSE_RECEIVE_ERROR);
  return value;
}

uint16_t Protocol::receive_u16() {
  std::uint16_t net = 0;
  int recvd = skt.recvall(&net, sizeof(net));

  if (recvd == 0)
    throw std::runtime_error(SOCKET_CLOSE_RECEIVE_ERROR);
  return ntohs(net);
}

std::string Protocol::receive_string() {
  uint16_t len = receive_u16();

  std::string s(len, STRING_END);
  if (len > 0) {
    int recvd = skt.recvall(&s[0], len);
    if (recvd == 0)
      throw std::runtime_error(SOCKET_CLOSE_RECEIVE_ERROR);
  }
  return s;
}

void Protocol::send_string(const std::string &str) {
  send_u16(static_cast<uint16_t>(str.size()));
  int recvd = skt.sendall(str.data(), str.size());

  if (recvd == 0)
    throw std::runtime_error(SOCKET_CLOSE_SEND_ERROR);
}
