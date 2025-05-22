#ifndef UTILS_H
#define UTILS_H
#include <algorithm>
#include <cctype>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "stargen.h"

using namespace std;

extern long seed;
extern long jseed;
extern long ifrst;
extern long nextn;

bool compare_string_char(string& a_string, int place, const char *a_character, int length = 1);
//string replaceStrChar(string, const char *, const char *);
char *my_itoa(int, char *, int);
string float_to_string(long double);
long double random_number(long double, long double);
long double about(long double, long double);
long double random_eccentricity(long double);
long double gaussian(long double);
long poisson(long double);
long double exponential(long double);
long double quad_trend(long double, long double, long double, long double);
long double ln_trend(long double, long double, long double);
long double logistal_trend(long double, long double, long double, long double);
bool polynomialfit(int, int, double *, double *, double *);
long double soft(long double, long double, long double);
long double lim(long double);
string remove_spaces(string);
double randf();
void srandf(long);
long double fix_inclination(long double);
long double linear_trend(long double, long double, long double);
string my_strtoupper(string);
int star_type_to_num(string spec_type, long double luminosity, int run = 1);
void logfix(long double, long double, long double, long double, long double &, long double &);
long double rangeAdjust(long double, long double, long double, long double, long double);
void e_fix(long double, long double, long double, long double, long double &, long double &);
long double e_trend(long double, long double, long double);
void quadfix(long double, long double, long double, long double, long double, long double, long double &, long double &, long double &);
long double quintic_trend(long double, long double, long double, long double, long double, long double, long double);

template <typename T>
string toString(T val, int decimals = 0);

template <typename T>
size_t getNumDecimals(T);

template <typename T>
string replaceStrChar(string, T, T);

template <typename T>
void quicksort(vector<T>&, int, int);

template <typename T>
bool is_close(T a, T b, long double percent = 1);

template <typename T>
void writeVector(vector<T>& v, const string& separator = "  ");

// display the key-value pairs in the map. follow the output of
// each pair by separator. default value of separator = "  "
template <typename Key, typename T>
void writeMap(const map<Key,T>& m, const string& separator = "\n");

template <typename T>
string toString(T val, int decimals)
{
  stringstream ss;
  string output;
  
  if (decimals_arg != 0)
  {
    decimals = decimals_arg;
  }
  
  ss.str("");
  
  if (isnan(val))
  {
    ss << val;
  }
  else
  {
    if (decimals == 0)
    {
      //ss << showpoint << fixed << setprecision(getNumDecimals(val));
      output = float_to_string(val);
    }
    else
    {
      ss << showpoint << fixed << setprecision(decimals);
      ss << val;
      output = ss.str();
    }
  }
 
  return output;
}

template <typename T>
size_t getNumDecimals(T val)
{
  if (isnan(val))
  {
      return 0;
  }
  
  /*size_t decimals = 0;
  for (int i = 1; val != floor(val); i++)
  {
    decimals = i;
    val *= 10;
  }
  
  if (decimals == 0)
  {
    decimals = 1;
  }
  
  return decimals;*/
  int count = 0;
  val = fabs(val);
  val = val - int(val);
  while (fabs(val) >= 0.0000001)
  {
    val = val * 10;
    count++;
    val = val - int(val);
  }
  return count;
}


// stuff below this point are algoritms taken from "Data Structors With C++ Using STL (second edition)" by William Ford and William Topp
// I had to put these here because due to a bug in gcc/g++, they can't be in a .c or .cpp file... *grumble*
template <typename T>
int pivotIndex(vector<T>& v, int first, int last)
{
  // index for the midpoint of [first,last) and the
  // indices that scan the index range in tandem
  int mid, scanUp, scanDown;
  // pivot value and object used for exchanges
  T pivot, temp;
  
  if (first == last)
  {
    //cout << "returing last" << endl;
    return last;
  }
  else if (first == (last - 1))
  {
    //cout << "returing first" << endl;
    return first;
  }
  else
  {
    mid = (last + first) / 2;
    pivot = v[mid];
    
    // exchange the pivot and the low end of the range
    // and initialize the indices scanUp and scanDown.
    v[mid] = v[first];
    v[first] = pivot;
    
    scanUp = first + 1;
    scanDown = last - 1;
    
    // manage the indices to locate elements that are in
    // the wrong sublist; stop when scanDown <= scanUp
    for(;;)
    {
      // move up lower sublist; stop when scanUp enters
      // upper sublist or identifies an element >= pivot
      while (scanUp <= scanDown && v[scanUp] < pivot)
      {
	//cout << "scanning up " << pivot << " as pivot point." << endl;
	scanUp++;
      }
      
      // scan down upper sublist; stop when scanDown locates
      // an element <= pivot; we guarantee we stop at arr[first]
      while (pivot < v[scanDown])
      {
	//cout << "scanning down using " << pivot << " as pivot point." << endl;
	scanDown--;
      }
      
      // if indices are not in their sublists, partition complete
      if (scanUp >= scanDown)
      {
	//cout << "stoped scanning" << endl;
	break;
      }
      
      // indices are still in their sublists and identify
      // two elements in wrong sublists. exchange
      temp = v[scanUp];
      v[scanUp] = v[scanDown];
      v[scanDown] = temp;
      
      scanUp++;
      scanDown--;
    }
    
    // copy pivot to index (scanDown) that partitions sublists
    // and return scanDown
    v[first] = v[scanDown];
    v[scanDown] = pivot;
    return scanDown;
  }
}

template <typename T>
void quicksort(vector<T>& v, int first, int last)
{
  // index of the pivot
  int pivotLoc;
  // temp used for an exchange when [first,last) has
  // two elements
  T temp;
  
  // if the range is not at least two elements, return
  if ((last - first) <= 1)
  {
    //cout << "test1" << endl;
    //return;
  }
  // if sublist has two elements, compare v[first] and
  // v[last-1] and exchange if necessary
  else if ((last - first) == 2)
  {
    //cout << "test2" << endl;
    if (v[last - 1] < v[first])
    {
      //cout << "test3" << endl;
      temp = v[last - 1];
      v[last - 1] = v[first];
      v[first] = temp;
    }
    //cout << "test4" << endl;
    //return;
  }
  else
  {
    //cout << "before pivot index call." << endl;
    
    pivotLoc = pivotIndex(v, first, last);
    
    //cout << "before first recursive call." << endl;
    //writeVector(v, "\n");
    
    // make the recursive call
    quicksort(v, first, pivotLoc);
    
    //cout << "before second recursive call." << endl;
    //writeVector(v, "\n");
    
    // make the recursive call
    quicksort(v, pivotLoc + 1, last);
    
    //cout << "after second recursive call." << endl;
    //writeVector(v, "\n");
  }
}

template <typename T>
string replaceStrChar(string str, T old, T the_new)
{
  replace(str.begin(), str.end(), old, the_new);
  return str;
}

template <typename T>
bool is_close(T a, T b, long double percent)
{
  long double decimal = percent / (long double)100;
  long double range = b * decimal;
  
  if (a > (b - decimal) && a < (b + decimal))
  {
    return true;
  }
  return false;
}

template <typename T>
void writeVector(vector<T>& v, const string& separator)
{
  // capture the size of the vector in n
  int i, n = v.size();
  
  for(i = 0; i < n; i++)
  {
    cout << v[i] << separator;
  }
  cout << endl;
}

template <typename Key, typename T>
void writeMap(const map<Key,T>& m, const string& separator)
{
  typename map<Key, T>::const_iterator iter = m.begin();
  
  while(iter != m.end())
  {
    cout << (*iter).first << ": " << (*iter).second << separator;
    iter++;
  }
}

#endif