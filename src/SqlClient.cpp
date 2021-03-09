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

#include <algorithm>
#include <stdexcept>

#include "SqlClient.h"
#include "SqlConnection.h"
#include "SqlConnectionFactory.h"

namespace drs {

SqlClient::SqlClient(const std::string& user, const std::string& pass,
    const std::string& server, const std::string& database) :
  m_user{user}, m_pass{pass}, m_server{server}, m_database{database}, m_conn{nullptr}
{
}

SqlClient::~SqlClient()
{
  if (m_conn) {
    m_conn->Dispose();
  }

  SqlConnectionFactory::instance().release(m_conn);
}

void SqlClient::Connect()
{
  if (m_conn != nullptr)
    return;

  m_conn = SqlConnectionFactory::instance().acquire(
      m_user, m_pass, m_server, m_database);
}

void SqlClient::ExecStoredProc(const char *proc, struct db_params *params, size_t parm_count)
{
  Connect();
  m_conn->ExecStoredProc(proc, params, parm_count);
}

void SqlClient::ExecNonQuery(const char *proc, struct db_params *params, size_t parm_count)
{
  Connect();
  m_conn->ExecNonQuery(proc, params, parm_count);
}

void SqlClient::Dispose()
{
  m_conn->Dispose();
}

void SqlClient::ExecSql(const char *sql)
{
  Connect();
  m_conn->ExecSql(sql);
}

void SqlClient::ExecDML(const char *dml)
{
  Connect();
  m_conn->ExecDML(dml);
}

bool SqlClient::NextRow()
{
  return m_conn->NextRow();
}

bool SqlClient::NextResult()
{
  return m_conn->NextResult();
}

std::string SqlClient::GetStringCol(int col)
{
  return m_conn->GetStringCol(col);
}

std::string SqlClient::GetStringColByName(const char *colName)
{
  return m_conn->GetStringColByName(colName);
}

int SqlClient::GetInt32Col(int col)
{
  return m_conn->GetInt32Col(col);
}

int SqlClient::GetInt32ColByName(const char *colName)
{
  return m_conn->GetInt32ColByName(colName);
}

int SqlClient::GetMoneyCol(int col, int *dol_out, int *cen_out)
{
  return m_conn->GetMoneyCol(col, dol_out, cen_out);
}

bool SqlClient::IsNullCol(int col)
{
  return m_conn->IsNullCol(col);
}

}
