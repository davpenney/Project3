/* Verse class function definitions
 * Computer Science, MVNU
 * CSC-3004 Introduction to Software Development
 *
 * NOTE: You may add code to this file, but do not
 * delete any code or delete any comments.
 *
 * STUDENT NAME: David Penney 
 */

#include "Verse.h"
#include <iostream>

using namespace std;

// Default constructor
Verse::Verse()
{
   verseText = "Specified verse is not in this chapter";
   verseRef = Ref();
}

// REQUIRED: Parse constructor - pass verse string from file
Verse::Verse(const string s)
{
   string text = s;
   // TODO: use Ref constructor to create verseRef
   verseRef = Ref(text);
   // store the remainder of the string in verseText
   int pos = text.find_first_of(":");
   verseText = text;
   //verseText = verseText.substr(pos);
}

// REQUIRED: Accessors
string Verse::getVerse()
{
   return verseText;
}

Ref Verse::getRef()
{
   return verseRef;
}

// display reference and verse
void Verse::display()
{
   //verseRef.display();
   cout << "\n" << verseText;
}
