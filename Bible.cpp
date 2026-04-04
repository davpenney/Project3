/* Bible class function definitions
 * Computer Science, MVNU
 * CSC-3004 Introduction to Software Development
 *
 * NOTE: You may add code to this file, but do not
 * delete any code or delete any comments.
 *
 * STUDENT NAME: David Penney
*/

#include "Ref.h"
#include "Verse.h"
#include "Bible.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <bits/stdc++.h>

using namespace std;

// Default constructor
Bible::Bible()
{
   infile = "/home/class/csc3004/Bibles/web-complete";
   buildRefIndex(infile);
}

// Constructor – pass bible filename
Bible::Bible(const string s) { infile = s; buildRefIndex(infile); }

// REQUIRED: lookup finds a given verse in this Bible
Verse Bible::lookup(Ref ref, int numVerses, LookupResult& status)
{
   ifstream instream(infile);
   string combinedVerses;

   Ref currentRef = ref;
   status = SUCCESS;


   for(int i = 0; i < numVerses; i++)
   {
      auto it = index.find(currentRef);

      if(it == index.end())
      {
          status = OTHER;
          break;
      }
      if(status != SUCCESS) { return Verse(); }

      int byteNum = it->second;

      if(byteNum < 0 || byteNum > 1000) { return Verse(); }

      instream.seekg(byteNum);

      string line;
      getline(instream, line);

      if(line.empty()) { return Verse(); }

      combinedVerses.append("<br>");
      combinedVerses.append(line);

      // move to next verse
      currentRef = next(currentRef, status);
   }

   return Verse(combinedVerses);
}

void Bible::buildRefIndex (string filename) {
   ifstream infile;
   string text, line, word;

   infile.open(filename.c_str(), ios::in);
   if (!infile) {
        cerr << "Error - can't open input file: " << filename << endl;
   }

   int pos = infile.tellg();
   while (getline(infile, line)) {
      lastByte = pos;
      Verse verse = line;

      index[verse.getRef()] = pos;
      pos = infile.tellg();
   }
}


// REQUIRED: Return the next verse from the Bible file stream if the file is open.
// If the file is not open, open the file and return the first verse.
Verse Bible::nextVerse(LookupResult& status)
{
   string next; //string to be parameter for verse initialization
   if (!instream.is_open()) { instream.open(infile); } //Opens file if not already
   if (!instream) { status = OTHER; return Verse(); }  //Creates uninitialized verse object if file can't be found

   if(getline(instream, next)) { status = SUCCESS; return Verse(next); }  //If the next line is able to be read returns that line
   else { status = OTHER; return Verse(); } //Otherwise return uninitialized verse
}

// REQUIRED: Return an error message string to describe status
void Bible::error(LookupResult status, int errorNum)
{
   if(status == NO_CHAPTER) {
      if(errorNum > 150){ 
         cout << "Chapter number (" << errorNum << ") does not exist: CHAPTER NUMBER TOO HIGH";
      }else if(errorNum < 1){
         cout << "Chapter number (" << errorNum << ") does not exist: MUST BE POSITIVE NUMBER";
      }else{ cout << "Chapter number (" << errorNum << ") does not exist in current book"; }
   }
   else if(status == NO_VERSE) {
      if(errorNum > 176){
         cout << "Verse number (" << errorNum << ") does not exist: VERSE NUMBER TOO HIGH";
      }else if(errorNum < 1) {
         cout << "Verse number (" << errorNum << ") does not exist: MUST BE POSITIVE NUMBER";
      }else{ cout << "Verse number (" << errorNum << ") does not exist in current chapter"; }
   }
   else if(status == NO_BOOK) { cout << "Book does not exist"; }
   else { cout << "Bible Verse not found"; }
}

void Bible::display()
{
   cout << "Bible file: " << infile << endl;
   cout << "Bible index size: " << index.size() << endl;
   cout << "Byte Offset for Genesis 1:1 : " << index[Ref(1,1,1)] << endl;
   cout << "Byte Offset for Genesis 1:2 : " << index[Ref(1,1,2)] << endl;
   cout << "Byte Offset for Genesis 1:3 : " << index[Ref(1,1,3)] << endl;
   cout << "Last Byte Offset : " << lastByte << endl;
}

// OPTIONAL access functions
// OPTIONAL: Return the reference after the given ref
Ref Bible::next(const Ref ref, LookupResult& status)
{
   auto it = index.find(ref);

   if(it == index.end()){
      status= OTHER;
      return ref;
   }

   it++;

   if(it == index.end()){
      status = OTHER;
      return ref;
   }else{
      status = SUCCESS;
      return it->first;
   }
}

// OPTIONAL: Return the reference before the given ref
Ref Bible::prev(const Ref ref, LookupResult& status)
{
   auto it = index.find(ref);

   if(it == index.end()){
      status= OTHER;
      return Ref();
   }

   it--;

   if(it == index.end()){
      status = OTHER;
      return Ref();
   }else{
      status = SUCCESS;
      return it->first;
   }
}

