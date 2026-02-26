/* Demo server program for Bible lookup using AJAX/CGI interface
 * By James Skon, Febrary 10, 2011
 * updated by Bob Kasper, January 2020
 * updated by Deborah Wilson, February 2026
 * Mount Vernon Nazarene University
 *
 * This sample program works using the cgicc AJAX library to
 * allow live communication between a web page and a program running on the
 * same server that hosts the web server.
 *
 * This program is run by a request from the associated html web document.
 * A Javascript client function invokes an AJAX request,
 * passing the input form data as the standard input string.
 *
 * The cgi.getElement function parses the input string, searching for the matching
 * field name, and returing a "form_iterator" oject, which contains the actual
 * string the user entered into the corresponding field. The actual values can be
 * accessed by dereferencing the form iterator twice, e.g. **verse
 * refers to the actual string entered in the form's "verse" field.
 *
 * STUDENT NAME: David Penney
 */

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <Bible.h>
#include <Ref.h>
#include <Verse.h>


/* Required libraries for AJAX to function */
#include "/home/class/csc3004/cgicc/Cgicc.h"
#include "/home/class/csc3004/cgicc/HTTPHTMLHeader.h"
#include "/home/class/csc3004/cgicc/HTMLClasses.h"

using namespace std;
using namespace cgicc;

int main()
{
   /* A CGI program must send a response header with content type
    * back to the web client before any other output.
    * For an AJAX request, our response is not a complete HTML document,
    * so the response type is just plain text to insert into the web page.
    */
   cout << "Content-Type: text/plain\n\n";

   Cgicc cgi;  // create object used to access CGI request data

   // GET THE INPUT DATA
   // browser sends us a string of field name/value pairs from HTML form
   // retrieve the value for each appropriate field name
   form_iterator st = cgi.getElement("search_type");
   form_iterator book = cgi.getElement("book");
   form_iterator chapter = cgi.getElement("chapter");
   form_iterator verse = cgi.getElement("verse");
   form_iterator nv = cgi.getElement("num_verse");

   // Convert and check input data
   bool validChapter = true;
   bool validVerse = true;
   bool validNumVerses = true;

   int chapterNum = chapter->getIntegerValue();
   int verseNum = verse->getIntegerValue();
   int numVerses = nv->getIntegerValue();

   if (chapter != cgi.getElements().end())
   {
      if (chapterNum > 150)
      {
         //cout << "<p>The chapter number (" << chapterNum << ") is too high.</p>" << endl;
         validChapter = false;
      }
      else if (chapterNum <= 0)
      {
         //cout << "<p>The chapter must be a positive number.</p>" << endl;
         validChapter = false;
      }
   }

   // TODO: OTHER INPUT VALUE CHECKS ARE NEEDED ... but that's up to you!
   if(verse != cgi.getElements().end())
   {
      if(verseNum > 176 || verseNum < 0)
      {
         //cout << "<p>The verse number (" << verseNum << ") is too high.</p>" << endl;
         validVerse = false;
      }
      else if(verseNum <= 0){
         //cout << "<p>The verse must be a positive number.</p>" << endl;
	 validVerse = false;
      }
   }

   if(nv != cgi.getElements().end())
   {
      if(numVerses > 31102)
      {
         cout << "<p>The number of verses (" << numVerses << ") is too high.</p>" << endl;
	 validNumVerses = false;
      }
      else if(numVerses <= 0){
         cout << "<p>The number of verses must be greater than 0.</p>" << endl;
	 validNumVerses = false;
      }
   }

   /* TODO: PUT CODE HERE TO CALL YOUR BIBLE CLASS FUNCTIONS
    *        TO LOOK UP THE REQUESTED VERSES
    */
   Bible bible("/home/class/csc3004/Bibles/web-complete");
   Verse bibleVerse;
   Ref ref(book->getIntegerValue(), chapterNum, verseNum);
   LookupResult status;

   bibleVerse = bible.lookup(ref, nv->getIntegerValue(), status);
   /* SEND BACK THE RESULTS
    * Finally we send the result back to the client on the standard output stream
    * in HTML text format.
    * This string will be inserted as is inside a container on the web page,
    * so we must include HTML formatting commands to make things look presentable!
    */

   if (validChapter && validVerse && validNumVerses)
   {
      ref.display();
      //cout << "<p>Your result: "
        //   << " " << **chapter << ":" << **verse
      cout << "<br>" << endl;
      cout << bibleVerse.getVerse() << endl;
   }
   else if(!validChapter)
   {
      status = NO_CHAPTER;
      bible.error(status, chapterNum);
   }
   else if(!validVerse)
   {
      status = NO_VERSE;
      bible.error(status, verseNum);
   }
   else
   {
      cout << "<p>Invalid Input: <em>" << "(" << **book << " " << **chapter << ":" << **verse << ") does not exist." << "</em></p>" << endl;
   }
   return 0;
}
