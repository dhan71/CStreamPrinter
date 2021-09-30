#ifndef CStreamPrinter_h
#define CStreamPrinter_h

/*****************************************************************************
 * author : dhan
 * email : dhan71@naver.com
 * Project : variable type stream printer
 * example :
 * gprint("Hello, %s!", "dhan") -> "Hello, dhan!"
 *****************************************************************************/

#include <initializer_list>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <set>

using std::ostream;
using std::stringstream;
using std::vector;
using std::map;
using std::set;
using std::initailizer_list;
using std::cout;

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
  static void print(ostream& os, const T& val, const TS&... args)
  {
    CStreamPrinter::print(os, val);
    CStreamPrinter::print(os, args);
  }

  /**
   * T type value stream print
   * - print base function
   * @param     os      output stream
   * @param     val     output value
   */
  template <typename T>
  static void print(ostream& os, const T& val)
  {
	os << val;
  }
  /**
   * T type pointer stream print
   * - print base function
   * @param     os      output stream
   * @param     val     output value
   */
  template <typename T>
  static void print(ostream& os, const T* valptr)
  {
	if (valptr)
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
  static void print(ostream& os, vector<T>& vec)
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
  static void print(ostream& os, vector<T*>& vec)
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
   * K key type and V value type map stream print
   * - print base function
   * @param     os      output stream
   * @param     kvs     K key, V value map
   */
  template <typename K, typename V>
  static void print(ostream& os, map<K, V>& kvs)
  {
	os << "{";
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
  /**
   * T type set stream print
   * - print base function
   * @param     os      output stream
   * @param     st      set of T type
   */
  template <typename T>
  static void print(ostream& os, set<T>& st)
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
  static void print(ostream& os, initailizer_list<T>& il)
  {
	os << "<I ";
	for (auto i = il.begin(); i != il.end(); ++i)
	{
	  CStreamPrinter::print(os, *i);
	  os << " ";
	}
	os << "I>";
  }
  /**
   * T pointer type initializer_list stream print
   * - print base function
   * @param     os      output stream
   * @param     il      initializer_list of T pointer type
   */
  template <typename T>
  static void print(ostream& os, initailizer_list<T*>& ilist)
  {
	os << "<I ";
	for (auto i = ilist.begin(); i != ilist.end(); ++i)
	{
      CStreamPrinter::print(os, *i);
	  os << " ";
	}
	os << "I>";
  }

public:
  /**
   * variable type formatted stream print
   * - printf base function
   * @param     os      output stream
   * @param     fmt     format
   */
  template <typename T>
  static void print(ostream& os, const char* fmt)
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
  static void printf(ostream& os, const char* fmt, const T& aVal, const TS...& args)
  {
	for ( ; *fmt; ++fmt)
	{
	  if (*fmt == '%')
	  {
		// "%%" -> print %
		if (*(fmt + 1) == '%')
		{
		  ++fmt;
		}
		// print current value and call print recusively
		else
		{
          CStreamPrinter::print(os, val);
		  // recursive call with remained args
          CStreamPrinter::print(os, fmt + 1, args...);
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
  CStreamPrinter::printf(cout, fmt, args...);
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
  CStreamPrinter::print(cout, args...);
}

/**
 * global cout printer
 * variable type stream print
 * @param     fmt     format
 * @param     il      T type list
 */
template <typename T>
inline void gprint(initializer_list<T> il)
{
  CStreamPrinter::print(cout, il);
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
inline string gsprintf(const char* fmt, const TS&... args)
{
  stringstream ss;
  CStreamPrinter::printf(ss, fmt, args...);
  return ss.str();
}

/**
 * global string printer
 * variable type stream print
 * @param     args    variable type arguments
 */
template <typename... TS>
inline string gsprint(const TS&... args)
{
  stringstream ss;
  CStreamPrinter::print(ss, args...);
  return ss.str();
}

/**
 * global string printer
 * variable type stream print
 * @param     il      T type list
 */
template <typename T>
inline string gsprint(initializer_list<T> ilist)
{
  stringstream ss;
  CStreamPrinter::print(ss, ilist);
  return ss.str();
}

#endif
