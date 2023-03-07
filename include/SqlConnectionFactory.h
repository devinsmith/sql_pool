/*
 * Copyright (c) 2012-2021 Devin Smith <devin@devinsmith.net>
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

#ifndef TDS_SQLCONNECTIONFACTORY_H
#define TDS_SQLCONNECTIONFACTORY_H

#include <string>
#include <list>
#include <mutex>

namespace tds {

class SqlConnection;

// Singleton
class SqlConnectionFactory {
public:
  SqlConnectionFactory(const SqlConnectionFactory&) = delete;
  SqlConnectionFactory& operator=(const SqlConnectionFactory &) = delete;
  SqlConnectionFactory(SqlConnectionFactory &&) = delete;
  SqlConnectionFactory & operator=(SqlConnectionFactory &&) = delete;

  static SqlConnectionFactory& instance()
  {
    static SqlConnectionFactory cf;
    return cf;
  }

  SqlConnection* acquire(const std::string& user, const std::string& pass,
      const std::string &server, const std::string &database);

  void release(SqlConnection*);

private:
  SqlConnectionFactory() = default;

  std::mutex _mutex;
  std::list<SqlConnection*> sql_connections;
};

} // namespace tds

#endif // TDS_SQLCONNECTIONFACTORY_H
