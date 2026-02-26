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
//   cout << "Byte offset for Genesis 1:1: " << webBible.index[Ref(1,1,1)] << endl;
   return 0;
}

