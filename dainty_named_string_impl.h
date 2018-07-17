/******************************************************************************

 MIT License

 Copyright (c) 2018 kieme, frits.germs@gmx.net

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.

******************************************************************************/

#ifndef _DAINTY_NAMED_STRING_IMPL_H_
#define _DAINTY_NAMED_STRING_IMPL_H_

#include <stdarg.h>
#include "dainty_named.h"

namespace dainty
{
namespace named
{
namespace string
{
  using named::t_bool;
  using named::t_void;
  using named::p_str_;
  using named::p_cstr_;
  using named::p_cstr;
  using named::t_n_;
  using named::t_n;
  using named::t_char;
  using named::t_int;

////////////////////////////////////////////////////////////////////////////////

  enum t_overflow_assert   { };
  enum t_overflow_truncate { };

////////////////////////////////////////////////////////////////////////////////

  struct t_block {
    t_char c   = '\0';
    t_n    max = t_n{0};

    t_block() = default;
    t_block(t_char _c, t_n _max) : c(_c), max(_max) { };
  };

  using r_cblock = const t_block&;

////////////////////////////////////////////////////////////////////////////////

  t_n_ build_  (p_str_, t_n_, p_cstr_, va_list, t_overflow_assert);
  t_n_ build_  (p_str_, t_n_, p_cstr_, va_list, t_overflow_truncate);
  t_n_ copy_   (p_str_, t_n_, p_cstr_, t_n_,    t_overflow_assert);
  t_n_ copy_   (p_str_, t_n_, p_cstr_, t_n_,    t_overflow_truncate);
  t_n_ copy_   (p_str_, t_n_, p_cstr_,          t_overflow_assert);
  t_n_ copy_   (p_str_, t_n_, p_cstr_,          t_overflow_truncate);
  t_n_ fill_   (p_str_, t_n_, r_cblock,         t_overflow_assert);
  t_n_ fill_   (p_str_, t_n_, r_cblock,         t_overflow_truncate);

  t_void display_(p_cstr_);
  t_int  compare_(p_cstr_, p_cstr_);
  t_bool match_  (p_cstr_, p_cstr_ pattern);
  t_n_   count_  (t_char,  p_cstr_);

////////////////////////////////////////////////////////////////////////////////

  template<class I>
  class t_string_impl_ {
  public:
    using t_char   = named::t_char;
    using r_cblock = string::r_cblock;

    inline
    t_string_impl_() : len_{0} {
    }

    inline
    t_string_impl_(p_str_ str) : len_{0} {
      str[0] = '\0';
    }

    inline
    t_string_impl_(p_str_ str, t_n_ max, p_cstr_ src)
      : len_{copy_(str, max, src, I())} {
    }

    inline
    t_string_impl_(p_str_ str, t_n_ max, r_cblock block)
      : len_{fill_(str, max, block, I())} {
    }

    inline
    t_void assign(p_str_ str, t_n_ max, p_cstr_ src) {
      len_ = copy_(str, max, src, I());
    }

    inline
    t_void assign(p_str_ str, t_n_ max, r_cblock block) {
      len_ = fill_(str, max, block, I());
    }

    inline
    t_void append(p_str_ str, t_n_ max, p_cstr_ src) {
      len_ += copy_(str + len_, max - len_, src, I());
    }

    t_void append(p_str_ str, t_n_ max, r_cblock block) {
      len_ += fill_(str + len_, max - len_, block, I());
    }

    inline
    t_void va_assign(p_str_ str, t_n_ max, p_cstr_ format, va_list vars) {
      len_ = build_(str, max, format, vars, I());
    }

    inline
    t_void va_append(p_str_ str, t_n_ max, const t_char* format,
                     va_list vars) {
      len_ += build_(str + len_, max - len_, format, vars, I());
    }

    inline
    t_void display(p_cstr_ str) const {
      if (len_)
        display_(str);
    }

    inline
    t_void display_then_clear(p_str_ str) {
      if (len_) {
        display_(str);
        str[0] = '\0';
      }
    }

    inline
    t_bool match(p_cstr_ str, p_cstr_ pattern) const {
      return match_(str, pattern);
    }

    inline
    t_void clear(p_str_ str) {
      str[0] = '\0';
    }

    inline
    p_cstr_ c_str(p_cstr_ str) const {
      return str;
    }

    inline
    t_n_ get_length() const {
      return len_;
    }

    inline
    t_n_ count(p_cstr_ str, t_char c) const {
      return count_(c, str);
    }

    inline
    t_char front(p_cstr_ str) const {
      return len_ ? str[0] : '\0';
    }

    inline
    t_char back(p_cstr_ str) const {
      return len_ ? str[len_ - 1] : '\0';
    }

    template<class F>
    inline
    t_void each(p_cstr_ str, F f) {
      for (t_n_ n = 0; n < len_; ++n)
        f(str[n]);
    }

    template<class F>
    inline
    t_void each(p_cstr_ str, F f) const {
      for (t_n_ n = 0; n < len_; ++n)
        f(str[n]);
    }

  private:
    t_n_ len_ = 0;
  };

///////////////////////////////////////////////////////////////////////////////
}
}
}

#endif
