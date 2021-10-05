#ifndef CStreamPrinter_h
#define CStreamPrinter_h

/*****************************************************************************
 * author : dhan
 * email : dhan71@naver.com
 * Project : variable type stream printer
 * example :
 * gprint("Hello, %s!", "dhan") -> "Hello, dhan!"
 *****************************************************************************/

#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <sstream>
#include <initializer_list>
#include <type_traits>


class CStreamPrinter
{
public:
  /**
   * variable parameter stream print
   * @param     os      output stream
   * @param     val     output value
   * @param     args    variable type values
   */
  template <typename T, typename... TS>
  static void print(std::ostream& os, const T& val, const TS&... args)
  {
    CStreamPrinter::print(os, val);
    CStreamPrinter::print(os, args...);
  }

  /**
   * T type pointer stream print
   * - print base function
   * @param     os      output stream
   * @param     val     output value
   */
  template <typename T>
  static void print(std::ostream& os, const T& val)
  {
    if (to_pointer(val))
      os << *to_pointer(val);
    else
      os << "nullptr";
  }
  /**
   * T type pointer stream print
   * - print base function
   * @param     os      output stream
   * @param     val     output value
   */
  static void print(std::ostream& os, const char* val)
  {
    if (val)
      os << val;
    else
      os << "nullptr";
  }

  /**
   * T type vector stream print
   * - print base function
   * @param     os      output stream
   * @param     vec     vector of T type
   */
  template <typename T>
  static void print(std::ostream& os, const std::vector<T>& vec)
  {
    os << "[ ";
    for (auto i = vec.begin(); i != vec.end(); ++i)
    {
      CStreamPrinter::print(os, *i);
      os << " ";
    }
    os << "]";
  }
  /**
   * T pointer type vector stream print
   * - print base function
   * @param     os      output stream
   * @param     vec     vector of T pointer type
   */
  template <typename T>
  static void print(std::ostream& os, std::vector<T*>& vec)
  {
    os << "[ ";
    for (auto i = vec.begin(); i != vec.end(); ++i)
    {
      CStreamPrinter::print(os, *i);
      os << " ";
    }
    os << "]";
  }

  /**
   * T type set stream print
   * - print base function
   * @param     os      output stream
   * @param     st      set of T type
   */
  template <typename T>
  static void print(std::ostream& os, const std::set<T>& st)
  {
    os << "( ";
    for (auto i = st.begin(); i != st.end(); ++i)
    {
      CStreamPrinter::print(os, *i);
      os << " ";
    }
    os << ")";
  }
  /**
   * T pointer type set stream print
   * - print base function
   * @param     os      output stream
   * @param     st      set of T type
   */
  template <typename T>
  static void print(std::ostream& os, const std::set<T*>& st)
  {
    os << "( ";
    for (auto i = st.begin(); i != st.end(); ++i)
    {
      CStreamPrinter::print(os, *i);
      os << " ";
    }
    os << ")";
  }

  /**
   * T type initializer_list stream print
   * - print base function
   * @param     os      output stream
   * @param     il      initializer_list of T type
   */
  template <typename T>
  static void print(std::ostream& os, const std::initializer_list<T>& il)
  {
    os << "< ";
    for (auto i = il.begin(); i != il.end(); ++i)
    {
      CStreamPrinter::print(os, *i);
      os << " ";
    }
    os << ">";
  }
  /**
   * T pointer type initializer_list stream print
   * - print base function
   * @param     os      output stream
   * @param     il      initializer_list of T pointer type
   */
  template <typename T>
  static void print(std::ostream& os, const std::initializer_list<T*>& ilist)
  {
    os << "< ";
    for (auto i = ilist.begin(); i != ilist.end(); ++i)
    {
      CStreamPrinter::print(os, *i);
      os << " ";
    }
    os << ">";
  }

  /**
   * K key type and V value type map stream print
   * - print base function
   * @param     os      output stream
   * @param     kvs     K key, V value map
   */
  template <typename K, typename V>
  static void print(std::ostream& os, const std::map<K, V>& kvs)
  {
    os << "{\n";
    for (auto i = kvs.begin(); i != kvs.end(); ++i)
    {
      os << "  ";
      CStreamPrinter::print(os, i->first);
      os << " : ";
      CStreamPrinter::print(os, i->second);
      os << "\n";
    }
    os << "}\n";
  }

private:
  /**
   * reference -> pointer
   */
  template <typename T>
  static T* to_pointer(T& a)
  {
    return &a;
  }
  /**
   * pointer -> pointer
   */
  template <typename T>
  static T* to_pointer(T* a)
  {
    return a;
  }


public:
  /**
   * variable type formatted stream print
   * - printf base function
   * @param     os      output stream
   * @param     fmt     format
   */
  static void printf(std::ostream& os, const char* fmt)
  {
    for ( ; *fmt; ++fmt)
    {
      if (*fmt == '%' && *(fmt + 1) == '%')
      {
        ++fmt;
      }
      os << *fmt;
    }
  }

  /**
   * variable type formatted stream print
   * @param     os      output stream
   * @param     fmt     format
   * @param     val     output value
   * @param     args    variable type arguments
   * @exam      ("%%A%B%", 1, "S") -> %A1BS
   */
  template <typename T, typename... TS>
  static void printf(std::ostream& os, const char* fmt, const T& val, const TS&... args)
  {
    //std::cout << "printf: args=" << sizeof...(args) << endl;
    for ( ; *fmt; ++fmt)
    {
      if (*fmt == '%')
      {
        // "%%" -> print %
        if (*(fmt + 1) == '%')
        {
          ++fmt;
        }
        // print current value and call printf recusively
        else
        {
          CStreamPrinter::print(os, val);
          // recursive call with remained args
          CStreamPrinter::printf(os, fmt + 1, args...);
          return;
        }
      }
      os << *fmt;
    }
  }
};

/**
 * global cout printer
 * variable type formatted stream print
 * @param     fmt     format
 * @param     val     output value
 * @param     args    variable type arguments
 * @exam      ("%%A%B%", 1, "S") -> %A1BS
 */
template <typename... TS>
inline void gprintf(const char* fmt, const TS&... args)
{
  CStreamPrinter::printf(std::cout, fmt, args...);
}

/**
 * global cout printer
 * variable type stream print
 * @param     fmt     format
 * @param     args    variable type arguments
 */
template <typename... TS>
inline void gprint(const TS&... args)
{
  CStreamPrinter::print(std::cout, args...);
}

/**
 * global cout printer
 * variable type stream print
 * @param     fmt     format
 * @param     il      T type list
 */
template <typename T>
inline void gprint(const std::initializer_list<T> il)
{
  CStreamPrinter::print(std::cout, il);
}

/**
 * global string printer
 * variable type formatted stream print
 * @param     fmt     format
 * @param     val     output value
 * @param     args    variable type arguments
 * @exam      ("%%A%B%", 1, "S") -> %A1BS
 */
template <typename... TS>
inline std::string gsprintf(const char* fmt, const TS&... args)
{
  std::stringstream ss;
  CStreamPrinter::printf(ss, fmt, args...);
  return ss.str();
}

/**
 * global string printer
 * variable type stream print
 * @param     args    variable type arguments
 */
template <typename... TS>
inline std::string gsprint(const TS&... args)
{
  std::stringstream ss;
  CStreamPrinter::print(ss, args...);
  return ss.str();
}

/**
 * global string printer
 * variable type stream print
 * @param     il      T type list
 */
template <typename T>
inline std::string gsprint(const std::initializer_list<T> il)
{
  std::stringstream ss;
  CStreamPrinter::print(ss, il);
  return ss.str();
}

#endif
