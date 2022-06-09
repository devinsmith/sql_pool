/*
 * Copyright (c) 2012-2016 Devin Smith <devin@devinsmith.net>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <stdexcept>
#include <list>

#include "SqlConnection.h"
#include "SqlConnectionFactory.h"

namespace drs {


void SqlConnectionFactory::release(SqlConnection *c)
{
  std::lock_guard<std::mutex> locker(_mutex);
  c->Dispose();
  sql_connections.push_back(c);
}


SqlConnection* SqlConnectionFactory::acquire(const std::string& user,
    const std::string& pass, const std::string& server,
    const std::string& database)
{
  SqlConnection *c;

  {
    std::lock_guard<std::mutex> locker(_mutex);
    for (auto it = sql_connections.begin(); it != sql_connections.end(); ++it) {
      c = *it;
      // TODO: Consider username and password when acquiring from pool?
      if (c->Server() == server) {
        if (c->Database() == database) {
          sql_connections.erase(it);
          return c;
        } else if (c->ChangeDatabase(database)) {
          sql_connections.erase(it);
          return c;
        }
      }
    }
  }

  // Make new connection.
  std::string log_msg = "SqlConnectionFactory::acquire > Making a new connection: ";
  log_msg += server;
  log_msg += " - ";
  log_msg += database;

  sql_log(1, log_msg.c_str());

  c = new SqlConnection(user, pass, server, database);
  c->Connect();

  return c;
}

}
