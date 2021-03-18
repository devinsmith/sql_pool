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

#ifndef __DRS_SQLCLIENT_H__
#define __DRS_SQLCLIENT_H__

#include <string>
#include <vector>

#include "SqlParams.h"

namespace drs {

class SqlConnection;

// A wrapper around SqlConnections that uses pooling.
class SqlClient {
public:
  SqlClient(const std::string& user, const std::string& pass,
      const std::string& server, const std::string& database);

  ~SqlClient();

  SqlClient(const SqlClient&) = delete;
  SqlClient& operator=(const SqlClient&) = delete;
  SqlClient(SqlClient&&) = delete;
  SqlClient& operator=(SqlClient&&) = delete;

  // You should not need to call this method directly, but you can.
  void Connect();

  void ExecStoredProc(const char *proc, struct db_params *params, size_t parm_count);
  void ExecStoredProc(const char *proc, const std::vector<db_param>& params);
  void ExecNonQuery(const char *proc, struct db_params *params, size_t parm_count);
  void ExecNonQuery(const char *proc, const std::vector<db_param>& params);
  void ExecSql(const char *sql);
  void ExecDML(const char *dml);

  void Dispose();

  bool NextRow();
  bool NextResult();

  // Data extraction
  int GetOrdinal(const char *colName);
  std::vector<std::string> GetAllColumnNames();

  std::string GetStringCol(int col);
  std::string GetStringColByName(const char *colName);
  int GetInt32Col(int col);
  int GetInt32ColByName(const char *colName);
  int GetMoneyCol(int col, int *dol_out, int *cen_out);
  bool IsNullCol(int col);

private:
  std::string m_user;
  std::string m_pass;
  std::string m_server;
  std::string m_database;

  SqlConnection *m_conn;
};

}

#endif /* __DRS_SQLCLIENT_H__ */
