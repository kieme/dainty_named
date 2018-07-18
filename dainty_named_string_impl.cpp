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

#include <assert.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "dainty_named_string_impl.h"

namespace dainty
{
namespace named
{
namespace string
{
////////////////////////////////////////////////////////////////////////////////

  inline
  t_n_ multiple_of_64_(t_n_ n) {
    if (n%64)
      n = (n - n%64) + 64;
    return n;
  }

  t_n_ calc_chr_(t_n_ chars, t_n_ blks) {
    return blks*64 + multiple_of_64_(chars + 1);
  }

  p_str_ alloc_(t_n_ n) {
    p_str_ str = (p_str_)std::malloc(n + 1);
    if (!str)
      assert(0); // out of memory - invalid strings won't exist!
    return str;
  }

  t_void dealloc_(p_str_ str) {
    if (str)
      std::free(str);
  }

  p_str_ realloc_(p_str_ str, t_n_ n) {
    str = (p_str_)std::realloc(str, n + 1);
    if (!str)
      assert(0); // out of memory - invalid strings won't exist!
    return str;
  }

  t_n_ build_(p_str_ dst, t_n_ max, p_cstr_ format, va_list vars) {
    if (max)
      ++max;
    t_int n = std::vsnprintf(dst, max, format, vars);
    assert(n > 0);
    return n;
  }

  t_n_ build_(p_str_ dst, t_n_ max, p_cstr_ format, va_list vars,
              t_overflow_assert) {
    t_int n = std::vsnprintf(dst, max + 1, format, vars);
    assert(n > 0 && (t_n_)n <= max);
    return n;
  }

  t_n_ build_(p_str_ dst, t_n_ max, p_cstr_ format, va_list vars,
              t_overflow_truncate) {
    t_int n = std::vsnprintf(dst, max + 1, format, vars);
    assert(n>0);
    if ((t_n_)n > max)
      n = max;
    return n;
  }

  t_n_ copy_(p_str_ dst, t_n_ max, p_cstr_ src, t_n_ n, t_overflow_assert) {
    t_n_ cnt = 0, min = max < n ? max : n;
    for (; cnt < min && src[cnt]; ++cnt)
      dst[cnt] = src[cnt];
    if (src[cnt] && cnt != n)
      assert(0);
    dst[cnt] = '\0';
    return cnt;
  }

  t_n_ copy_(p_str_ dst, t_n_ max, p_cstr_ src, t_n_ n, t_overflow_truncate) {
    t_n_ cnt = 0, min = max < n ? max : n;
    for (; cnt < min && src[cnt]; ++cnt)
      dst[cnt] = src[cnt];
    dst[cnt] = '\0';
    return 0;
  }

  t_n_ copy_(p_str_ dst, t_n_ max, p_cstr_ src, t_overflow_assert) {
    t_n_ cnt = 0;
    for (; cnt < max && src[cnt]; ++cnt)
      dst[cnt] = src[cnt];
    if (src[cnt])
      assert(0);
    dst[cnt] = '\0';
    return cnt;
  }

  t_n_ copy_(p_str_ dst, t_n_ max, p_cstr_ src, t_overflow_truncate) {
    t_n_ cnt = 0;
    for (; cnt < max && src[cnt]; ++cnt)
      dst[cnt] = src[cnt];
    dst[cnt] = '\0';
    return cnt;
  }

  t_n_ fill_(p_str_ dst, t_n_ max, r_cblock block, t_overflow_assert) {
    auto bmax = get(block.max);
    if (bmax > max)
      assert(0);
    for (t_n_ cnt = 0; cnt < bmax; ++cnt)
      dst[cnt] = block.c;
    dst[bmax] = '\0';
    return bmax;
  }

  t_n_ fill_(p_str_ dst, t_n_ max, r_cblock block, t_overflow_truncate) {
    auto bmax = get(block.max);
    t_n_ min = max < bmax ? max : bmax;
    for (t_n_ cnt = 0; cnt < min; ++cnt)
      dst[cnt] = block.c;
    dst[min] = '\0';
    return min;
  }

  t_void display_(p_cstr_ str) {
    std::printf("%s\n", str);
  }

  t_int compare_(p_cstr_ lh, p_cstr_ rh) {
    return std::strcmp(lh, rh);
  }

  t_n_ length_(p_cstr_ str) {
    return std::strlen(str);
  }

  t_n_ length_(p_cstr_ format, va_list vars) {
    va_list args;
    va_copy(args, vars);
    t_n_ require = std::vsnprintf(NULL, 0, format, args);
    va_end(args);
    return require;
  }

  t_bool match_(p_cstr_ str, p_cstr_ pattern) {
    p_cstr_ l = 0; // XXX not fully correct
    while (*pattern && *str) {
             if (*pattern == *str)    ++pattern;
        else if (*pattern == '*') l = ++pattern;
        else if (*pattern == '?') {   ++pattern;
      } else if (l) {
        if (pattern != l) {
          pattern = l;
          continue;
        }
      } else
        return false;
      ++str;
    }
    return *str ? (t_bool)l : !*pattern;
  }

  t_n_ count_(t_char c,  p_cstr_ str) {
    t_n_ cnt = 0;
    for (; *str; ++str)
      if (*str == c)
        ++cnt;
    return cnt;
  }

////////////////////////////////////////////////////////////////////////////////
}
}
}
