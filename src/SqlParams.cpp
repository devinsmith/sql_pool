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

#include "SqlParams.h"

namespace drs {

void SqlParams::AddInt(const char *name, int ival)
{
  db_param p;
  p.name = name;
  p.type = ParamType::Int;
  p.ivalue = ival;
  p.datalen = -1;

  pvec.push_back(p);
}

void SqlParams::AddString(const char *name, const std::string& str)
{
  db_param p;
  p.name = name;
  p.type = ParamType::String;
  p.pvalue = str.c_str();
  p.datalen = str.size();

  pvec.push_back(p);
}

void SqlParams::AddString(const char *name, const char *str, size_t sz)
{
  db_param p;
  p.name = name;
  p.type = ParamType::String;
  p.pvalue = str;
  p.datalen = static_cast<int>(sz);

  pvec.push_back(p);
}

void SqlParams::AddBool(const char *name, bool bval)
{
  db_param p;
  p.name = name;
  p.type = ParamType::Bit;
  p.ivalue = bval;
  p.datalen = 1;

  pvec.push_back(p);
}

void SqlParams::AddNull(const char *name, ParamType type)
{
  db_param p;
  p.name = name;
  p.type = type;
  p.pvalue = nullptr;
  p.datalen = 0;

  pvec.push_back(p);
}

}
