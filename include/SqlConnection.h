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

#ifndef __DRS_SQLCONNECTION_H__
#define __DRS_SQLCONNECTION_H__

#include <string>

#define MSDBLIB 1
#include <sqlfront.h>
#include <sybdb.h>

#include "SqlParams.h"

namespace drs {

class SqlConnection {
public:
  SqlConnection(const std::string& user, const std::string& pass,
      const std::string& server, const std::string& database) :
    _user{user}, _pass{pass}, _server{server}, _database{database}, _dbHandle{nullptr},
    _fetched_rows{true}, _fetched_results{true} {}

  ~SqlConnection();

  // No move or copy support. I don't want to deal with DBPROCESS pointer.
  SqlConnection(const SqlConnection&) = delete;
  SqlConnection& operator=(const SqlConnection&) = delete;
  SqlConnection(SqlConnection&&) = delete;
  SqlConnection& operator=(SqlConnection&&) = delete;

  const std::string& Server() const { return _server; }
  const std::string& Database() const { return _database; }

  // Executing a stored procedure or query will automatically connect
  // It should not be necessary to call this method directly.
  void Connect();

  void Disconnect();

  // When a query is executed freetds buffers the results into a
  // local buffer. Dispose must be called to clear out the results before
  // another query is run.
  void Dispose();

  // Execute Data Manipulation Language (UPDATE/INSERT/DELETE/etc)
  void ExecDML(const char *sql);

  // Execute SQL where you expect results/resultsets (SELECT).
  void ExecSql(const char *sql);

  // Execute a stored procedure where results/resultsets are expected.
  void ExecStoredProc(const char *proc, struct db_params *params,
    size_t parm_count);

  // Execute a stored procedure where results/resultsets are NOT expected
  // or where results/resultsets can be ignored.
  void ExecNonQuery(const char *proc, struct db_params *params,
    size_t parm_count);

  // Move to next result set.
  bool NextResult();

  // Move to the next row.
  bool NextRow();

  // Data extraction
  int GetOrdinal(const char *colName);

  std::string GetStringCol(int col);
  std::string GetStringColByName(const char *colName);
  int GetInt32Col(int col);
  int GetInt32ColByName(const char *colName);
  int GetMoneyCol(int col, int *dol_out, int *cen_out);
  bool IsNullCol(int col);

  // FreeTDS callback helper
  int MsgHandler(DBPROCESS * dbproc, DBINT msgno, int msgstate,
    int severity, char *msgtext, char *srvname, char *procname, int line);

private:
  void run_initial_query();
  std::string fix_server(const std::string& str);

  std::string _user;
  std::string _pass;
  std::string _server;
  std::string _database;
  DBPROCESS *_dbHandle;
  bool _fetched_rows;
  bool _fetched_results;
  std::string _error;
};

void sql_startup();
void sql_shutdown();

}

#endif /* __DRS_SQLCONNECTION_H__ */
