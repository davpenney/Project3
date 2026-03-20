/* testreader.cpp
 * Computer Science, MVNU
 * CSC-3004 Introduction to Software Development
 *
 * main function for Project 3 part 1
 *
 * STUDENT NAME: David Penney
 */

#include "Ref.h"
#include "Verse.h"
#include "Bible.h"
#include <iostream>
#include <limits>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main (int argc, char *argv[])
{
   // Create Bible object to process the raw text file
   Bible webBible("/home/class/csc3004/Bibles/web-complete");

   Verse verse;
   int bookNum, chapterNum, verseNum, numVerses = 0;
   LookupResult result;

   cout << "Using Bible from: ";
   webBible.display();

   if(argc < 4){
      cout << "Enter 4 integers for book, chapter, verse, and added verses to find: " << flush;
      cin >> bookNum >> chapterNum >> verseNum >> numVerses;
   }else if(argc == 5){
      bookNum = stoi(argv[1]);
      chapterNum = stoi(argv[2]);
      verseNum = stoi(argv[3]);
      numVerses = stoi(argv[4]);
   }else if(argc == 4){
      bookNum = stoi(argv[1]);
      chapterNum = stoi(argv[2]);
      verseNum = stoi(argv[3]);
      numVerses = 1;
   }

   Ref ref(bookNum, chapterNum, verseNum);
   cout << "Looking up reference: ";
   ref.display();
   cout << endl;

   verse = webBible.lookup(ref, numVerses, result);
   cout << "Result status: " << result << endl;
   verse.display();
   cout << endl;

   return 0;
}


