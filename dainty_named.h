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

#ifndef _DAINTY_NAMED_H_
#define _DAINTY_NAMED_H_

// named: 'give a name to'
//
//   <named> name builtin types and specify a simple naming convention
//   that should be followed by projects that use it.
//
//   the focus was on the embedded world that often use c++03.
//   (reason for not using type traits, constexpr, etc.). The API will
//   be changed to support c++17 features.
//
//   naming convention:
//
//     N01. functions, method names must be verbs.
//     N02. classes, struct, types names must be nouns.
//     N03. literal and constant values should be written in capital letters.
//     N04. specialization of type named names & identifier are prefixed.
//     N05. types must be prefixed with t_.
//          (avoid conflict with std:: convention).
//     N06. pointer definitions must be prefixed p_.
//     N07. reference definitions must be prefixed r_.
//     N08. internal functions, methods, variables, types must have an
//          postfix _. API users should never use these.
//     N09. when using <dainty::named> builtin types on interfaces, use
//          specializations of t_explicit, to assign purpose to a type.
//     N10. use printable lowercase characters that are c++ identifiers.
//     N11. use '_' within long names to improve readability.
//     N12. use <dainty::named> builtin types instead of <std>.
//     N13. use qualified names or "using " when using <dainty::named>.
//     N14. prefix a const "type" name with c but not the parameter itself.
//           e.g. t_id  id; -> non-const id.
//                t_cid id; -> const id. but const is not identifyable with
//                             the variable name.
//     N15. when writing classes/structs using the following naming convention
//          for function parameters, data memebers and types.
//          // -> t_param, param, param_
//          e.g class t_class {
//              public:
//                using t_param = ... ;
//                void set(const t_param& param) {
//                  param_ = param;
//                }
//              private:
//                t_param param_;
//              };
//     N15.1 when a naming conflict exit, prefix a variable with _.
//           struct t_pair {
//             t_first  first;
//             t_second second; // not postfixed with _ because not internal.
//             t_pair(t_first _first, t_second _second)
//               : first(_first), second{_second) {
//             }
//           };
//
//   specialization of t_explicit for interface use:
//
//      Z01: use type t_ix that is intended to index into something.
//      Z02: use type t_n that is intended to represent a number of elements.
//      Z03: use t_validity to express if something is valid.
//
//   file naming convention:
//
//      F01: dainty_<namespace>.h of a namespace located withint dainty.
//      F02: dainty_<namespace>_<purpose>.h a functionality within namespace.
//      F03: the cpp files names are the same as the associated header files.
//           dainty_oops.h and dainty_oops.cpp
//      F04: example cpp files use the name of the functionality.
//           dainty_oops.cpp then dainty_oops_example<n>.cpp
//      F05: test cpp files use the name of the functionality.
//           dainty_oops.cpp then dainty_oops_test<n>.cpp
//
// should set be allowed. its meant only to transfer data through an interface.
//
// t_explicit:
//
//   note: with t_explicit<> assign a purpose to a builtin type.
//
//   e.g. the demonstation use the classic set_point(int x, int y) example.
//
//   enum t_x_ { };
//   enum t_y_ { };
//   typedef named::t_explicit<named::t_uint, t_x_> t_xpoint;
//   typedef named::t_explicit<named::t_uint, t_y_> t_ypoint;
//
//   void set_point(t_xpoint x, t_ypoint y);
//   void set_point(int x, int y);
//
//   void set_point(5, 10);
//   void set_point(xpoint(5), ypoint(10));
//
//  Why is such a feature not part of the cpp language?
//
//    e.g. using t_xpoint = explicit unsigned int; // make type t_xpoint
//         using t_ypoint = explicit unsigned int; // make type t_ypoint
//
//    t_xpoint and t_ypoint are different types.
//
//    unsigned int x = t_xpoint(1) // ok
//    t_xpoint x = 1;              // nok
//    t_xpoint x(1);               // ok
//    t_xpoint x{1};               // ok
//    t_xpoint x(-1);              // nok
//    t_xpoint x{-1)}              // nok

#include <cstdint>

#define OK  dainty::named::VALID
#define NOK dainty::named::INVALID

namespace dainty
{
namespace named
{
  using t_bool         = bool;
  using t_char         = char;
  using t_uchar        = unsigned char;
  using t_int          = int;
  using t_uint         = unsigned int;
  using t_short        = short;
  using t_ushort       = unsigned short;
  using t_long         = long int;
  using t_ulong        = unsigned long int;
  using t_llong        = long long int;
  using t_ullong       = unsigned long long int;
  using t_double       = double;
  using t_void         = void;

  using t_int8         = std::int8_t;
  using t_int16        = std::int16_t;
  using t_int32        = std::int32_t;
  using t_int64        = std::int64_t;

  using t_uint8        = std::uint8_t;
  using t_uint16       = std::uint16_t;
  using t_uint32       = std::uint32_t;
  using t_uint64       = std::uint64_t;

  using t_int_least8   = std::int_least8_t;
  using t_int_least16  = std::int_least16_t;
  using t_int_least32  = std::int_least32_t;
  using t_int_least64  = std::int_least64_t;

  using t_uint_least8  = std::uint_least8_t;
  using t_uint_least16 = std::uint_least16_t;
  using t_uint_least32 = std::uint_least32_t;
  using t_uint_least64 = std::uint_least64_t;

  using t_int_fast8    = std::int_fast8_t;
  using t_int_fast16   = std::int_fast16_t;
  using t_int_fast32   = std::int_fast32_t;
  using t_int_fast64   = std::int_fast64_t;

  using t_uint_fast8   = std::uint_fast8_t;
  using t_uint_fast16  = std::uint_fast16_t;
  using t_uint_fast32  = std::uint_fast32_t;
  using t_uint_fast64  = std::uint_fast64_t;

///////////////////////////////////////////////////////////////////////////////

  template<typename T>
  struct t_prefix {
    using t_  = T;

    using p_  = T*;
    using P_  = const T*;

    using r_  = T&;
    using R_  = const T&;

    using x_  = T&&;

    t_prefix() = delete;
  };

  template<>
  struct t_prefix<t_void> {
    using t_  = t_void;

    using p_  = t_void*;
    using P_  = const t_void*;

    t_prefix() = delete;
  };

  template<typename T> struct t_prefix<T*>;
  template<typename T> struct t_prefix<T&>;
  template<typename T> struct t_prefix<const T>;

///////////////////////////////////////////////////////////////////////////////

  using p_void = t_prefix<void>::p_;
  using P_void = t_prefix<void>::P_;

///////////////////////////////////////////////////////////////////////////////

  template<typename T> struct t__explicit_ { };

  template<> struct t__explicit_<t_bool>   { using t_type_ = t_bool;   };
  template<> struct t__explicit_<t_char>   { using t_type_ = t_char;   };
  template<> struct t__explicit_<t_uchar>  { using t_type_ = t_uchar;  };
  template<> struct t__explicit_<t_int>    { using t_type_ = t_int;    };
  template<> struct t__explicit_<t_uint>   { using t_type_ = t_uint;   };
  template<> struct t__explicit_<t_short>  { using t_type_ = t_short;  };
  template<> struct t__explicit_<t_ushort> { using t_type_ = t_ushort; };
  template<> struct t__explicit_<t_long>   { using t_type_ = t_long;   };
  template<> struct t__explicit_<t_ulong>  { using t_type_ = t_ulong;  };
  template<> struct t__explicit_<t_llong>  { using t_type_ = t_llong;  };
  template<> struct t__explicit_<t_ullong> { using t_type_ = t_ullong; };
  template<> struct t__explicit_<t_double> { using t_type_ = t_double; };
  template<> struct t__explicit_<t_void>   { using t_type_ = t_void;   };

  template<typename T>
  struct t__explicit_<T*> {
    using t_type_ = typename t__explicit_<T>::t_type_*;
  };

  template<typename T>
  struct t__explicit_<const T*> {
    using t_type_ = const typename t__explicit_<T>::t_type_*;
  };

  template<typename T>
  struct t__explicit_<T* const> {
    using t_type_ = typename t__explicit_<T>::t_type_* const;
  };

  template<typename T>
  struct t__explicit_<const T* const> {
    using t_type_ = const typename t__explicit_<T>::t_type_* const;
  };

  template<typename T> struct t__explicit_<T**>;

///////////////////////////////////////////////////////////////////////////////

  template<class, class, class> class t_explicit;
  template<class T, class TAG, class V>
  constexpr T  get(t_explicit<T, TAG, V>);
  template<class T, class TAG, class V>
  constexpr T& set(t_explicit<T, TAG, V>&);

  template<class T, class TAG>
  struct t_validate_ { static constexpr T check(T t) { return t; } };

  template<class T, class TAG, class V = t_validate_<T, TAG> >
  class t_explicit {
  public:
    using t_value    = typename t__explicit_<T>::t_type_;
    using t_tag      = TAG;
    using t_validate = V;

    constexpr explicit t_explicit(t_value value) : value_(V::check(value)) {
    }

    template<class T1, class V1>
    constexpr explicit t_explicit(t_explicit<T1, TAG, V1> value)
      : value_(V::check(value.value_)) {
    }

    t_explicit() = delete;                              // for clarity
    t_explicit(const t_explicit&) = default;            // for clarity
    t_explicit& operator=(const t_explicit&) = default; // for clarity

  private:
    template<class T1, class TAG1, class V1> friend class t_explicit;
    template<class T1, class TAG1, class V1>
    friend constexpr T1  get(t_explicit<T1, TAG1, V1>);
    template<class T1, class TAG1, class V1>
    friend constexpr T1& set(t_explicit<T1, TAG1, V1>&);
    t_value value_;
  };

///////////////////////////////////////////////////////////////////////////////

  template<class T, class TAG, class V>
  constexpr
  T  get(t_explicit<T, TAG, V> value)  { return value.value_; }

  template<class T, class TAG, class V>
  constexpr
  T& set(t_explicit<T, TAG, V>& value) { return value.value_; }

///////////////////////////////////////////////////////////////////////////////

  template<class> struct t_is_explicit_;

  template<class T, class TAG, class V>
  struct t_is_explicit_<t_explicit<T, TAG, V>> {
    using t_result_ = t_explicit<T, TAG, V>;
  };

  template<class E, class T, class TAG, class V>
  constexpr
  E transform(t_explicit<T, TAG, V> src) {
    return typename t_is_explicit_<E>::t_result_{get(src)};
  }

///////////////////////////////////////////////////////////////////////////////

  enum t_fd_tag_       {};
  enum t_n_tag_        {};
  enum t_ix_tag_       {};
  enum t_bix_tag_      {};
  enum t_eix_tag_      {};
  enum t_validity_tag_ {};
  enum t_cstr_tag_     {};

  using t_fd_       = t_int32;
  using t_n_        = t_uint32;
  using t_ix_       = t_n_;
  using t_bix_      = t_ix_;
  using t_eix_      = t_ix_;
  using t_validity_ = t_bool;
  using p_cstr_     = t_prefix<char>::p_;
  using P_cstr_     = t_prefix<char>::P_;

  using t_fd       = t_explicit<t_fd_,       t_fd_tag_>;
  using t_n        = t_explicit<t_n_,        t_n_tag_>;
  using t_ix       = t_explicit<t_ix_,       t_ix_tag_>;
  using t_bix      = t_explicit<t_ix_,       t_bix_tag_>;
  using t_eix      = t_explicit<t_ix_,       t_eix_tag_>;
  using t_validity = t_explicit<t_validity_, t_validity_tag_>;
  using p_cstr     = t_explicit<p_cstr_,     t_cstr_tag_>;
  using P_cstr     = t_explicit<P_cstr_,     t_cstr_tag_>;

///////////////////////////////////////////////////////////////////////////////

  // only support very limited operators for t_n because of its massive use.

  constexpr t_bool operator==(t_n lh, t_n rh)  { return get(lh) == get(rh); }
  constexpr t_bool operator!=(t_n lh, t_n rh)  { return get(lh) != get(rh); }
  constexpr t_bool operator< (t_n lh, t_n rh)  { return get(lh) < get(rh);  }
  constexpr t_bool operator<=(t_n lh, t_n rh)  { return get(lh) <= get(rh); }

  constexpr t_bool operator==(t_fd lh, t_fd rh) { return get(lh) == get(rh); }
  constexpr t_bool operator!=(t_fd lh, t_fd rh) { return !(lh == rh);        }

///////////////////////////////////////////////////////////////////////////////

  constexpr t_validity   VALID{true};
  constexpr t_validity INVALID{false};
  constexpr t_fd       BAD_FD {-1};

///////////////////////////////////////////////////////////////////////////////

  constexpr t_ix  to_ix (t_n  n)  { return transform<t_ix> (n);  }
  constexpr t_n   to_n  (t_ix ix) { return transform<t_n>  (ix); }
  constexpr t_bix to_bix(t_ix ix) { return transform<t_bix>(ix); }
  constexpr t_eix to_eix(t_ix ix) { return transform<t_eix>(ix); }

  constexpr t_ix  operator"" _ix (t_ullong ix) { return t_ix(ix);  }
  constexpr t_bix operator"" _bix(t_ullong ix) { return t_bix(ix); }
  constexpr t_eix operator"" _eix(t_ullong ix) { return t_eix(ix); }
  constexpr t_n   operator"" _n  (t_ullong n)  { return t_n(n);    }

///////////////////////////////////////////////////////////////////////////////

  constexpr t_bool operator==(const t_validity& lh, const t_validity& rh) {
    return get(lh) == get(rh);
  }

  template<int N>
  constexpr p_cstr mk_str(char (&str)[N])         { return p_cstr{str};  }
  constexpr p_cstr mk_str(p_cstr_ str)            { return p_cstr{str};  }

  template<int N>
  constexpr P_cstr mk_cstr(const char (&cstr)[N]) { return P_cstr{cstr}; }
  constexpr P_cstr mk_cstr(P_cstr_ cstr)          { return P_cstr{cstr}; }

///////////////////////////////////////////////////////////////////////////////

  enum  t_errn_tag_ {};
  using t_errn_ = named::t_int;
  using t_errn  = named::t_explicit<t_errn_, t_errn_tag_>;

  constexpr t_bool operator==(t_errn errn, t_validity validity) {
    return get(errn) == 0 && validity == VALID;
  }

///////////////////////////////////////////////////////////////////////////////

  template<typename T>
  class t_verifiable {
  public:
    T      value;
    t_errn errn;

    constexpr operator t_validity() const {
      return get(errn) == 0 ? VALID : INVALID;
    }

    constexpr
    t_verifiable(T _value, t_errn _errn) : value(_value), errn(_errn) {
    }
  };

  template<typename T>
  constexpr const T& get(const t_verifiable<T>& verifiable) {
    return verifiable.value;
  }

  template<typename T>
  constexpr T& set(t_verifiable<T>& verifiable) {
    return verifiable.value;
  }

  template<class T, class TAG, class V>
  constexpr T get(const t_verifiable<t_explicit<T, TAG, V>>& verifiable) {
    return get(verifiable.value);
  }

  template<class T, class TAG, class V>
  constexpr T& set(t_verifiable<t_explicit<T, TAG, V>>& verifiable) {
    return set(verifiable.value);
  }

///////////////////////////////////////////////////////////////////////////////

  template<typename TAG>
  struct t_user {
    union {
      t_int64 id;
      p_void  ptr;
      P_void cptr;
    };
    t_user() : id(0) { }
    inline t_user(t_int64  _id) :   id(_id)   { }
    inline t_user(p_void  _ptr) :  ptr(_ptr)  { }
    inline t_user(P_void _cptr) : cptr(_cptr) { }
  };

  template<typename TAG>
  constexpr t_bool operator==(const t_user<TAG>& lh, const t_user<TAG>& rh) {
    return lh.id == rh.id;
  }

  template<typename TAG>
  constexpr t_bool operator!=(const t_user<TAG>& lh, const t_user<TAG>& rh) {
    return lh.id != rh.id;
  }

///////////////////////////////////////////////////////////////////////////////

  constexpr t_bool reset(t_bool& t) {
    t_bool tmp = t;
    t = false;
    return tmp;
  }

  template<class T>
  constexpr T reset(T& t) {
    T tmp = t;
    t = 0;
    return tmp;
  }

  template<class T>
  constexpr T* reset(T*& t) {
    T* tmp = t;
    t = nullptr;
    return tmp;
  }

  template<class T, class TAG>
  constexpr T reset(t_explicit<T, TAG>& t) {
    return reset(set(t));
  }

  template<class TAG>
  constexpr t_int64 reset(t_user<TAG>& t) {
    return reset(t.id);
  }

///////////////////////////////////////////////////////////////////////////////

  constexpr t_bool reset(t_bool& t, t_bool value) {
    t_bool tmp = t;
    t = value;
    return tmp;
  }

  template<class T>
  constexpr T reset(T& t, T value) {
    T tmp = t;
    t = value;
    return tmp;
  }

  template<class T>
  constexpr T* reset(T*& t, T* value) {
    T* tmp = t;
    t = value;
    return tmp;
  }

  template<class T, class TAG>
  constexpr T reset(t_explicit<T, TAG>& t, T value) {
    return reset(set(t), value);
  }

  template<class T, class TAG>
  constexpr T reset(t_explicit<T, TAG>& t, t_explicit<T, TAG> value) {
    return reset(set(t), get(value));
  }

  template<class TAG>
  constexpr t_int64 reset(t_user<TAG>& t, t_int64 value) {
    return reset(t.id, value);
  }

///////////////////////////////////////////////////////////////////////////////

  enum  t_nsec_tag_ {};
  using t_nsec_ = t_ullong;
  using t_nsec  = t_explicit<t_nsec_, t_nsec_tag_>;

  enum  t_usec_tag_ {};
  using t_usec_ = t_ulong;
  using t_usec  = t_explicit<t_usec_, t_usec_tag_>;

  enum  t_msec_tag_ {};
  using t_msec_ = t_uint;
  using t_msec  = t_explicit<t_msec_, t_msec_tag_>;

  enum  t_sec_tag_ {};
  using t_sec_ = t_uint;
  using t_sec  = t_explicit<t_sec_, t_sec_tag_>;

  enum  t_min_tag_ {};
  using t_min_ = t_ushort;
  using t_min  = t_explicit<t_min_, t_min_tag_>;

  enum  t_ticks_tag_ {};
  using t_ticks_ = t_uint64;
  using t_ticks  = t_explicit<t_ticks_, t_ticks_tag_>;

///////////////////////////////////////////////////////////////////////////////

  template<t_n_ N, typename TAG>
  class t_multiple {
  public:
    constexpr static t_n of() {
      return t_n{N};
    }

    constexpr t_multiple(t_n_ _value) : value(_value) {
    }

    t_n value;
  };

  template<t_n_ N, typename TAG>
  constexpr t_n multiple_of(t_multiple<N, TAG> multiple) {
    return t_n{N*get(multiple.value)};
  }

///////////////////////////////////////////////////////////////////////////////
}
}

#endif
