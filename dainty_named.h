#ifndef _DAINTY_NAMED_H_
#define _DAINTY_NAMED_H_

// named: 'give a name to'
//
//   <named::> name builtin types and specify a simple naming convention
//   that should be followed by projects that use it.
//
//   the focus was on the embedded world that often use c++03.
//   (reason for not using type traits, constexpr, etc.). The API will
//   be changed to support c++17 features.
//
//   naming convention:
//
//     01. functions, method names must be verbs.
//     02. classes, struct, types names must be nouns.
//     03. specialization of named names & identifier are prefixed.
//     04. types must be prefixed with t_.
//         (avoid conflict with std:: convention).
//     05. literal values should be prefixed with v_.
//     06. constant global variable values must be prefixed with s_.
//     07. pointer definitions must be prefixed p_.
//     08. internal functions, methods, variables, types must have an
//         postfix _. API users should never use these.
//     09. when using <named::> builtin types on interfaces, use
//         specializations of t_explicit, to assign purpose to a type.
//     10. use printable lowercase characters that are c++ identifiers.
//     11. use '_' within long names to improve readability.
//     12. use <named::> builtin types instead of <std::>.
//     13. use qualified names or "using " when working with <named::> types.
//     14. prefix a const "type" name with c but not the parameter itself.
//           e.g. t_id id;  -> non-const id.
//                t_cid id; -> const id. but const is not identifyable with
//                             the variable name.
//     15. when writing classes/structs using the following naming convention
//         for function parameters, data memebers and types.
//         // -> t_value, value, value_
//         class t_class {
//         public:
//           typedef ... t_value;
//           void set_value(const t_value& value) {
//             value_ = value;
//           }
//         private:
//           t_value value;
//         };
//
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

  using p_void         = void*;
  using p_cvoid        = const void*;
  using p_cstr         = const char*;

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
  struct t_supported_strong_           { };

  template<>
  struct t_supported_strong_<t_bool>   { typedef t_bool t_type_; };

  template<>
  struct t_supported_strong_<t_char>   { typedef t_char t_type_; };

  template<>
  struct t_supported_strong_<t_uchar>  { typedef t_uchar t_type_; };

  template<>
  struct t_supported_strong_<t_int>    { typedef t_int t_type_; };

  template<>
  struct t_supported_strong_<t_uint>   { typedef t_uint t_type_; };

  template<>
  struct t_supported_strong_<t_short>  { typedef t_short t_type_; };

  template<>
  struct t_supported_strong_<t_ushort> { typedef t_ushort t_type_; };

  template<>
  struct t_supported_strong_<t_long>   { typedef t_long t_type_; };

  template<>
  struct t_supported_strong_<t_ulong>  { typedef t_ulong t_type_; };

  template<>
  struct t_supported_strong_<t_llong>  { typedef t_llong t_type_; };

  template<>
  struct t_supported_strong_<t_ullong> { typedef t_ullong t_type_; };

  template<>
  struct t_supported_strong_<t_double> { typedef t_double t_type_; };

  template<typename T>
  struct t_supported_strong_<T*> {
    typedef typename t_supported_strong_<T>::type_t_* t_type_;
  };

  template<typename T>
  struct t_supported_strong_<T**> { };

///////////////////////////////////////////////////////////////////////////////

  template<class, class> class t_explicit;
  template<class T, class TAG>           T& set(t_explicit<T, TAG>&);
  template<class T, class TAG> constexpr T  get(t_explicit<T, TAG>);

  template<class T, class TAG>
  class t_explicit {
  public:
    using t_value = typename t_supported_strong_<T>::t_type_;
    using t_tag   = TAG;

    constexpr explicit t_explicit(t_value value) : value_(value) { }
    t_explicit() = delete;                              // for clarity
    t_explicit(const t_explicit&) = default;            // for clarity
    t_explicit& operator=(const t_explicit&) = default; // for clarity

  private:
    template<class U, class TAG1> friend           U& set(t_explicit<U, TAG1>&);
    template<class U, class TAG1> friend constexpr U  get(t_explicit<U, TAG1>);
    t_value value_;
  };

///////////////////////////////////////////////////////////////////////////////

  template<class T, class TAG>
  inline
  T& set(t_explicit<T, TAG>& value) { return value.value_; }

  template<class T, class TAG>
  constexpr
  T get(t_explicit<T, TAG> value)   { return value.value_; }

///////////////////////////////////////////////////////////////////////////////

  template<class> struct t_explicit_helper_;

  template<class T, class TAG>
  struct t_explicit_helper_<t_explicit<T, TAG>> {
     template<typename TAG1> using t_src_ = t_explicit<T, TAG1>;
  };

  template<class E, class TAG1>
  constexpr
  E transform(typename t_explicit_helper_<E>::template t_src_<TAG1> src) {
    return E{get(src)};
  }

///////////////////////////////////////////////////////////////////////////////

  enum t_n_   {};
  using t_n   = named::t_explicit<named::t_uint32, t_n_>; // n, number
  enum t_ix_  {};
  using t_ix  = named::t_explicit<t_n::t_value,  t_ix_>;  // general index
  enum t_bix_ {};
  using t_bix = named::t_explicit<t_ix::t_value, t_bix_>; // begin index
  enum t_eix_ {};
  using t_eix = named::t_explicit<t_ix::t_value, t_eix_>; // end index

  constexpr t_ix  to_ix (t_n  n)  { return transform<t_ix> (n);  }
  constexpr t_n   to_n  (t_ix ix) { return transform<t_n>  (ix); }
  constexpr t_bix to_bix(t_ix ix) { return transform<t_bix>(ix); }
  constexpr t_eix to_eix(t_ix ix) { return transform<t_eix>(ix); }

  constexpr t_ix  operator"" _ix (t_ullong ix) { return t_ix(ix);  }
  constexpr t_bix operator"" _bix(t_ullong ix) { return t_bix(ix); }
  constexpr t_eix operator"" _eix(t_ullong ix) { return t_eix(ix); }
  constexpr t_n   operator"" _n  (t_ullong n)  { return t_n(n);    }

///////////////////////////////////////////////////////////////////////////////
}
}

#endif