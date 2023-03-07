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

#ifndef TDS_SQLPARAMS_H
#define TDS_SQLPARAMS_H

#include <string>
#include <vector>

namespace tds {

// Legacy
struct db_params {
  const char *name;
  unsigned char status;
  int type;
  int maxlen;
  int datalen;
  const void *value;
};

// Legacy
#define INT32_TYPE 1
#define STRING_TYPE 2
#define BOOL_TYPE 3
#define BIT_TYPE 4

enum class ParamType {
  Int, Bit, String
};

struct db_param {
  const char *name;
  ParamType type;
  int datalen;
  const void *pvalue;
  int ivalue;
};

class SqlParams {
public:
  void AddInt(const char *name, int ival);
  void AddString(const char *name, const std::string& str);
  void AddString(const char *name, const char *str, size_t sz);
  void AddBool(const char *name, bool bval);

  void AddNull(const char *name, ParamType type);

  const std::vector<db_param>& ToVec() { return pvec; }
private:
  std::vector<db_param> pvec;
};

}

#endif // TDS_SQLPARAMS_H
