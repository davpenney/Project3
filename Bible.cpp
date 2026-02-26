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
   // TODO: scan the file to retrieve the line that holds ref ...
   ifstream instream(infile);

   if (!instream) { status = OTHER; return Verse(); }

   LookupResult nextStatus = SUCCESS; //creates a lookupresult object for the nextverse parameter
   Verse aVerse;
   bool verseFound = true;

   while(nextStatus == SUCCESS && verseFound) { //repeats while a next verse exists

      aVerse = nextVerse(nextStatus); //sets the verse tp
      if (ref == aVerse.getRef()) { verseFound = false; break; } //Compares ref objects to see if they match .
   }

   // update the status variable
   // placeholder until retrieval is attempted
   // create and return the verse object
   // default verse, to be replaced by a Verse object
   // that is constructed from a line in the file.
   Verse addedVerse;
   string combinedVerses = aVerse.getVerse();

   for(int i = 1; i < numVerses; i++){ //Loops through to append requested added verses to string
      if(nextStatus == OTHER){ break; }
      addedVerse = nextVerse(nextStatus);
      combinedVerses.append("<br>");
      combinedVerses.append(addedVerse.getVerse());
   }

   return(Verse(combinedVerses));
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
   return ref;
}

// OPTIONAL: Return the reference before the given ref
Ref Bible::prev(const Ref ref, LookupResult& status)
{
   return ref;
}
