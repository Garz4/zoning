/*
 * MIT License
 *
 * Copyright (c) 2021 Uriel Rivas
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * https://github.com/Garz4/zoning/blob/master/LICENSE
 */

#pragma once

#include <arpa/inet.h>
#include <unistd.h>

#include "PaqueteDatagrama.h"

class SocketDatagrama final {
 public:
  explicit SocketDatagrama() noexcept = default;

  SocketDatagrama(int puerto);
  ~SocketDatagrama() { close(socket_); }

  /* Recibe un paquete tipo datagrama proveniente de este socket. */
  int recibe(PaqueteDatagrama& paquete);
  int recibe(
      PaqueteDatagrama& paquete, time_t segundos, suseconds_t microsegundos);

  /* Envía un paquete tipo datagrama desde este socket. */
  int envia(const PaqueteDatagrama& paquete);

  std::string ip_foranea() const noexcept {
    return inet_ntoa(direccion_foranea_.sin_addr);
  }

  unsigned short puerto_foranea() const noexcept {
    return direccion_foranea_.sin_port;
  }

 private:
  sockaddr_in direccion_local_;
  sockaddr_in direccion_foranea_;
  timeval timeout_;

  /* ID Socket. */
  int socket_;
};
