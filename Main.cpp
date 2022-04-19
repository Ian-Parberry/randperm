/// \file Main.cpp
/// \brief The main source code file.
///
/// \mainpage
///
/// A tool to permute a list of strings into pseudo-random order in which each
/// permutation is equally likely. Input comes from a hard-coded file 
/// `Input.txt` containing a list of strings, one per line. Blank lines are
/// ignored. Output goes to a hard-coded file `Output.txt`. The standard 
/// pseudo-random permutation generation algorithm is used, based on the 
/// pseudo-random number generator `std::default_random_engine` seeded with
/// the Unix epoch time in seconds.

// MIT License
//
// Copyright (c) 2022 Ian Parberry
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS 
// IN THE SOFTWARE.

#include <iostream>
#include <fstream>

#include <string>
#include <vector>

#include <random>
#include <chrono>
#include <ctime>

/// \brief Read strings from a file.
///
/// Read strings from a file, one string per line, and collect them in an 
/// `std::vector` of `std::string`. Blank lines in the input are ignored.
/// \param fname File name.
/// \param v [OUT] An `std::vector` of `std::string` from the file.

void ReadStrings(const std::wstring& fname, std::vector<std::string>& v){
  std::ifstream infile(fname); //input file stream
  std::string strLine; //current input line
  v.clear(); //clear the vector for safety

  while(std::getline(infile, strLine)) //for each line
    if(!strLine.empty()) //if line not empty
      v.push_back(strLine); //push onto the result vector
} //ReadStrings

/// \brief Get the Unix epoch time.
///
/// Unix epoch time is the number of seconds since the Unix epoch, 
/// Jan 1, 1970 UTC, excluding leap seconds.
/// \tparam t Numeric type of result.
/// \return Unix epoch time.

template<class t> t GetEpochTime(){
  return static_cast<t>(static_cast<std::chrono::seconds>(std::time(0)).count());
} //GetEpochTime

/// \brief Randomly permute an `std::vector`.
///
/// Use the standard pseudo-random permutation generation algorithm to permute
/// the elements of an `std::vector` into pseudo-random order with the
/// pseudo-random number generator `std::default_random_engine` seeded by
/// the Unix epoch time (number of seconds since Jan 1, 1970 UTC, excluding
/// leap seconds). Each permutation is equally likely.
/// \tparam t Type of things to be permuted.
/// \param v [IN, OUT] An `std::vector` of things to be permuted.

template<class t> void Randomize(std::vector<t>& v){
  std::default_random_engine stdRandom; //pseudo-random number generator
  stdRandom.seed(GetEpochTime<unsigned>()); //sow seed
  
  for(size_t i=0; i<v.size(); i++)
    std::swap(v[i], v[std::uniform_int_distribution<size_t>(0, i)(stdRandom)]);
} //Randomize

/// \brief Write strings to a file.
///
/// Write strings from an `std::vector` of `std::string` to a file.
/// \param fname File name.
/// \param v An std::vector of `std::string`.

void WriteStrings(std::wstring fname, const std::vector<std::string>& v){
  std::ofstream outfile(fname); //output file stream

  for(const std::string& s: v) //for each string
    outfile << s << std::endl; //output it on a line
} //WriteStrings

/// \brief Main.
///
/// \param argc Number of arguments.
/// \param argv Arguments.
/// \return 0 (What could possibly go wrong?)

int main(int argc, char *argv[]){  
  std::vector<std::string> vecStrings; //vector of strings

  ReadStrings(L"Input.txt", vecStrings); //input the strings
  Randomize(vecStrings); //permute the strings pseudo-randomly
  WriteStrings(L"Output.txt", vecStrings); //output the strings

  return 0; //what could possibly go wrong?
} //main
