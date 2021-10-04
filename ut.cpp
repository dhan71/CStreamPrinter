#define BOOST_TEST_MODULE sprint
#define BOOST_TEST_DYN_LINK
//#define BOOST_TEST_MAIN

//#include <CStreamPrinter.h>
#include "CStreamPrinter.h"

#include <boost/test/unit_test.hpp>
#include <iostream>
#include <fstream>

using namespace std;
using namespace boost::unit_test;

/*
BOOST_AUTO_TEST_CASE(test_format)
{
const char* f = "abc%d!@#%f한글OK\n";
gprintf(f, 3, 3.14);
gprintf(f, 123, 3.14);
cout << "Big string formst TEST" << endl;
const char* F = R"(akjfkda
asdkfj
adkfjla
adkjal
adkjlf
adf
%f
%s
)";
gprintf(F, 123, 3.14, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\nBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB\nCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC\n");
}
BOOST_AUTO_TEST_CASE(test_format1)
{
  cout << "test_format1() called" << endl;
  const char* f = "abc%!@#%한글OK%\n";
  gprintf(f, 3, 3.14, "LAST");
  gprintf(f, 123, 3.14, "LAST");
}
BOOST_AUTO_TEST_CASE(test_format2)
{
  cout << "test_format2() called" << endl;
  const char* f = "abc%!@#%한글OK%\n";
  gprintf(f, " ", 3, ',', 3.14, " LAST");
  gprintf(f, ' ', 123, ":", 3.14, " LAST");
}
BOOST_AUTO_TEST_CASE(test_format3)
{
  cout << "test_format3() called" << endl;
  const char* f1 = "abc%!@#%%한글OK% - last %%\n";
  gprintf(f1, 3, 3.14, "LAST");
  const char* f2 = "abc%!@#%한글OK% - last %% : ";
  gprintf(f2, ' ', 123, ":", 3.14, " LAST");
  gprintf("START:", 123, ":", 3.14, " LAST");
}
BOOST_AUTO_TEST_CASE(test_format4)
{
  vector<int> v { 1, 2, 3 };
  gprint(v, "\n");
  gprint(v, 1, "\n");
  gprint(1, v, 2);
  gprint(v, 1, 2);

  vector<vector<int> > vv;
  vv.push_back(v);
  vv.push_back(v);
  vv.push_back(v);
  gprint(vv);
  gprint(vv, 1, "END");
}
BOOST_AUTO_TEST_CASE(test_format5)
{
  vector<int> v { 1, 2, 3, 4, 5 };
  gprint(v);
  gprint(v, v);
  gprintf("vector contents 2 = % - %\n", v, v);
}
BOOST_AUTO_TEST_CASE(test_format6)
{
  gprint(1, 2, 3, 4, 5);
  gprint('a', 'b', 'c');
  gprint({ 1, 2, 3, 4, 5 });
}
BOOST_AUTO_TEST_CASE(test_format7)
{
  map<int, int> m;
  m[1] = 100;
  m[2] = 200;
  m[3] = 300;
  gprint(m);
  gprintf("map contents=%s\n", m);

  vector<string> v1 { "A1", "A2", "A3" };
  vector<string> v2 { "B1", "B2", "B3" };
  vector<string> v3 { "C1", "C2", "C3" };
  map<int, vector<string> > mm;
  mm[1] = v1;
  mm[2] = v2;
  mm[3] = v3;
  gprint(mm);
}
BOOST_AUTO_TEST_CASE(test_format8)
{
  int* i1 = new int(100);
  int* i2 = new int(200);
  int* i3 = new int(300);
  vector<int*> v1 { i1, i2, i3 };
  gprint(v1);

  double* d1 = new double(0.1);
  double* d2 = new double(0.2);
  double* d3 = new double(0.3);
  gprint(*d1, *d2, *d2);

  vector<double*> vd { d1, d2, d3 };
  gprint(vd);
  gprint({ d1, d2, d3 });
}
*/

BOOST_AUTO_TEST_CASE(test_sformat_0)
{
  cout << " test_sformat_0" << endl;
}
BOOST_AUTO_TEST_CASE(test_sformat1)
{
  cout << "test_sformat1() called" << endl;
  const char* f = "abc%!@#%한글OK%\n";
  string r = gsprintf(f, 3, 3.14, "LAST");
  cout << "f=[" << f << "]\nr=[" << r << "]" << endl;
  BOOST_ASSERT(r == "abc3!@#3.14한글OKLAST\n");
  r = gsprintf(f, 123, 3.14, "LAST");
  BOOST_ASSERT(r == "abc123!@#3.14한글OKLAST\n");
}
BOOST_AUTO_TEST_CASE(test_sformat2)
{
  cout << "test_sformat2() called" << endl;
  const char* f = "abc%!@#%한글OK%\n";
  string r = gsprintf(f, " ", 3, ',', 3.14, " LAST");
  cout << "r1=[" << r << "]" << endl;
  BOOST_ASSERT(r == "abc !@#3한글OK,\n");
  r = gsprintf(f, ' ', 123, ":", 3.14, " LAST");
  cout << "r2=[" << r << "]" << endl;
  BOOST_ASSERT(r == "abc !@#123한글OK:\n");
}
BOOST_AUTO_TEST_CASE(test_sformat3)
{
  cout << "test_sformat3() called" << endl;
  const char* f1 = "abc%!@#% %%한글OK% - last %%\n";
  string r = gsprintf(f1, 3, 3.14, "LAST");
  cout << "r1=[" << r << "]" << endl;
  BOOST_ASSERT(r == "abc3!@#3.14 %한글OKLAST - last %\n");

  const char* f2 = "abc%!@#%한글OK% - last %% : ";
  r = gsprintf(f2, ' ', 123, ":", 3.14, " LAST");
  cout << "r2=[" << r << "]" << endl;
  BOOST_ASSERT(r == "abc !@#123한글OK: - last % : ");

  r = gsprint("START:", 123, ":", 3.14, " LAST");
  BOOST_ASSERT(r == "START:123:3.14 LAST");
}
BOOST_AUTO_TEST_CASE(test_sformat4)
{
  cout << "test_sformat4() called" << endl;
  vector<int> v { 1, 2, 3 };
  string r = gsprint(v, "\n");
  BOOST_ASSERT(r == "[ 1 2 3 ]\n");

  r = gsprint(v, 1, "\n");
  cout << "r2=[" << r << "]" << endl;
  BOOST_ASSERT(r == "[ 1 2 3 ]1\n");

  r = gsprint(1, v, 2);
  BOOST_ASSERT(r == "1[ 1 2 3 ]2");

  r = gsprint(v, 1, 2);
  BOOST_ASSERT(r == "[ 1 2 3 ]12");

  r = gsprint(v, " ", 1, " ", 2);
  BOOST_ASSERT(r == "[ 1 2 3 ] 1 2");

  vector<vector<int> > vv;
  vv.push_back(v);
  vv.push_back(v);
  vv.push_back(v);
  r = gsprint(vv);
  BOOST_ASSERT(r == "[ [ 1 2 3 ] [ 1 2 3 ] [ 1 2 3 ] ]");
  r = gsprint(vv, 1, "END");
  BOOST_ASSERT(r == "[ [ 1 2 3 ] [ 1 2 3 ] [ 1 2 3 ] ]1END");
}
BOOST_AUTO_TEST_CASE(test_sformat5)
{
  cout << "test_sformat5() called" << endl;
  vector<int> v { 1, 2, 3, 4, 5 };
  string r = gsprint(v);
  BOOST_ASSERT(r == "[ 1 2 3 4 5 ]");

  r = gsprint(v, v);
  BOOST_ASSERT(r == "[ 1 2 3 4 5 ][ 1 2 3 4 5 ]");

  r = gsprintf("vector contents 2 = % - %\n", v, v);
  cout << "r3=[" << r << "]" << endl;
  BOOST_ASSERT(r == "vector contents 2 = [ 1 2 3 4 5 ] - [ 1 2 3 4 5 ]\n");
}
BOOST_AUTO_TEST_CASE(test_sformat6)
{
  cout << "test_sformat6() called" << endl;
  string r = gsprint(1, 2, 3, 4, 5);
  BOOST_ASSERT(r == "12345");
  r = gsprint('a', 'b', 'c');
  BOOST_ASSERT(r == "abc");
  r = gsprint({ 1, 2, 3, 4, 5 });
  BOOST_ASSERT(r == "< 1 2 3 4 5 >");
}
BOOST_AUTO_TEST_CASE(test_sformat7)
{
  cout << "test_sformat7() called" << endl;
  map<int, int> m;
  m[1] = 100;
  m[2] = 200;
  m[3] = 300;
  string r = gsprint(m);
  cout << "r1=[" << r << "]" << endl;
  BOOST_ASSERT(r == "{\n  1 : 100\n  2 : 200\n  3 : 300\n}\n");
  r = gsprintf("map contents=%\n", m);
  cout << "r2=[" << r << "]" << endl;
  BOOST_ASSERT(r == "map contents={\n  1 : 100\n  2 : 200\n  3 : 300\n}\n\n");

  vector<string> v1 { "A1", "A2", "A3" };
  vector<string> v2 { "B1", "B2", "B3" };
  vector<string> v3 { "C1", "C2", "C3" };
  map<int, vector<string> > mm;
  mm[1] = v1;
  mm[2] = v2;
  mm[3] = v3;
  r = gsprint(mm);
  cout << "r3=[" << r << "]" << endl;
  BOOST_ASSERT(r == "{\n  1 : [ A1 A2 A3 ]\n  2 : [ B1 B2 B3 ]\n  3 : [ C1 C2 C3 ]\n}\n");
}
BOOST_AUTO_TEST_CASE(test_sformat8)
{
  cout << "test_sformat8() called" << endl;
  int* i1 = new int(100);
  int* i2 = new int(200);
  int* i3 = new int(300);
  vector<int*> v1 { i1, i2, NULL, i3 };
  string r = gsprint(v1);
  cout << "r1=[" << r << "]" << endl;
  BOOST_ASSERT(r == "[ 100 200 nullptr 300 ]");

  double* d1 = new double(0.1);
  double* d2 = new double(0.2);
  double* d3 = new double(0.3);
  r = gsprint(*d1, *d2, *d3);
  cout << "r2=[" << r << "]" << endl;
  BOOST_ASSERT(r == "0.10.20.3");
  r = gsprint(*d1, " ", *d2, " ", *d3);
  BOOST_ASSERT(r == "0.1 0.2 0.3");

  vector<double*> vd { d1, d2, d3 };
  r = gsprint(vd);
  BOOST_ASSERT(r == "[ 0.1 0.2 0.3 ]");
  r = gsprint({ d1, d2, d3 });
  cout << "r5=[" << r << "]" << endl;
  BOOST_ASSERT(r == "< 0.1 0.2 0.3 >");

  vector<const char*> vs1 { "ONE", "TWO", "THREE" };
  r = gsprint(vs1);
  BOOST_ASSERT(r == "[ ONE TWO THREE ]");

  vector<const char*> vs2 { "ONE", "TWO", NULL, "THREE" };
  r = gsprint(vs2);
  BOOST_ASSERT(r == "[ ONE TWO nullptr THREE ]");

  r = gsprint({ "ONE", "TWO", "THREE" });
  BOOST_ASSERT(r == "< ONE TWO THREE >");

  set<const char*> ss3;// { "ONE", "TWO", "THREE" };
	ss3.insert("ONE");
	ss3.insert("TWO");
	ss3.insert("THREE");
  r = gsprint(ss3);
  cout << "r9=[" << r << "]" << endl;
  BOOST_ASSERT(r == "( ONE TWO THREE )");

  set<const char*> ss4 { "ONE", "TWO", "THREE" };
  r = gsprint(ss4);
  cout << "r10=[" << r << "]" << endl;
  BOOST_ASSERT(r == "( ONE TWO THREE )");

  set<const char*> ss5 { "ONE", "TWO", NULL, "THREE" };
  r = gsprint(ss5);
  cout << "r11=[" << r << "]" << endl;
  BOOST_ASSERT(r == "( nullptr ONE TWO THREE )");
}
