/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   QueryEditor.cpp
 * Author: martin
 * 
 * Created on 25. Juni 2017, 18:37
 */

#include "QueryEditor.h"
#include <cstdio>
#include <cstdlib>
#include <stdio.h>
#include <string.h>

static const int TS = 14; // default editor textsize

Fl_Text_Display::Style_Table_Entry
                   styletable[] = {	// Style table
		     { FL_BLACK,      FL_COURIER,           TS }, // A - Plain
		     { FL_DARK_GREEN, FL_HELVETICA_ITALIC,  TS }, // B - Line comments
		     { FL_DARK_GREEN, FL_HELVETICA_ITALIC,  TS }, // C - Block comments
		     { FL_DARK_RED,   FL_COURIER,           TS }, // D - Strings
		     { FL_DARK_RED,   FL_COURIER,           TS }, // E - Directives
		     { FL_DARK_RED,   FL_COURIER_BOLD,      TS }, // F - Types
		     { FL_BLUE,       FL_COURIER,      TS }, // G - Keywords
		   };

const char         *code_keywords[] = {	// List of known C/C++ keywords...
		     "and",
		     "and_eq",
		     "asm",
		     "bitand",
		     "bitor",
		     "break",
		     "case",
		     "catch",
		     "compl",
		     "continue",
		     "default",
		     "delete",
		     "do",
		     "else",
		     "false",
		     "for",
		     "goto",
		     "if",
		     "new",
		     "not",
		     "not_eq",
		     "operator",
		     "or",
		     "or_eq",
		     "return",
		     "switch",
		     "template",
		     "this",
		     "throw",
		     "true",
		     "try",
		     "while",
		     "xor",
		     "xor_eq"
		   };


const char         *code_types[] = {	// List of known C/C++ types...
		     "auto",
		     "bool",
		     "char",
		     "class",
		     "const",
		     "const_cast",
		     "double",
		     "dynamic_cast",
		     "enum",
		     "explicit",
		     "extern",
		     "float",
		     "friend",
		     "inline",
		     "int",
		     "long",
		     "mutable",
		     "namespace",
		     "private",
		     "protected",
		     "public",
		     "register",
		     "short",
		     "signed",
		     "sizeof",
		     "static",
		     "static_cast",
		     "struct",
		     "template",
		     "typedef",
		     "typename",
		     "union",
		     "unsigned",
		     "virtual",
		     "void",
		     "volatile"
		   };


int compare_keywords( const void *a, const void *b ) {
    return (strcmp(*((const char **)a), *((const char **)b)));
}

void style_parse(const char *text, char *style, int length) {
  char	     current;
  int	     col;
  int	     last;
  char	     buf[255],
             *bufptr;
  const char *temp;

  // Style letters:
  //
  // A - Plain
  // B - Line comments
  // C - Block comments
  // D - Strings
  // E - Directives
  // F - Types
  // G - Keywords

  for (current = *style, col = 0, last = 0; length > 0; length --, text ++) {
    if (current == 'B' || current == 'F' || current == 'G') current = 'A';
    if (current == 'A') {
      // Check for directives, comments, strings, and keywords...
      if (col == 0 && *text == '#') {
        // Set style to directive
        current = 'E';
      } else if (strncmp(text, "//", 2) == 0) {
        current = 'B';
	for (; length > 0 && *text != '\n'; length --, text ++) *style++ = 'B';

        if (length == 0) break;
      } else if (strncmp(text, "/*", 2) == 0) {
        current = 'C';
      } else if (strncmp(text, "\\\"", 2) == 0) {
        // Quoted quote...
	*style++ = current;
	*style++ = current;
	text ++;
	length --;
	col += 2;
	continue;
      } else if (*text == '\"') {
        current = 'D';
      } else if (!last && (islower((*text)&255) || *text == '_')) {
        // Might be a keyword...
	for (temp = text, bufptr = buf;
	     (islower((*temp)&255) || *temp == '_') && bufptr < (buf + sizeof(buf) - 1);
	     *bufptr++ = *temp++) {
	  // nothing
        }

        if (!islower((*temp)&255) && *temp != '_') {
	  *bufptr = '\0';

          bufptr = buf;

	  if (bsearch(&bufptr, code_types,
	              sizeof(code_types) / sizeof(code_types[0]),
		      sizeof(code_types[0]), compare_keywords)) 
          {
	    while (text < temp) {
	      *style++ = 'F';
	      text ++;
	      length --;
	      col ++;
	    }

	    text --;
	    length ++;
	    last = 1;
	    continue;
	  } else if (bsearch(&bufptr, code_keywords,
	                     sizeof(code_keywords) / sizeof(code_keywords[0]),
		             sizeof(code_keywords[0]), compare_keywords)) 
          {
	    while (text < temp) {
	      *style++ = 'G';
	      text ++;
	      length --;
	      col ++;
	    }

	    text --;
	    length ++;
	    last = 1;
	    continue;
	  }
	}
      }
    } else if (current == 'C' && strncmp(text, "*/", 2) == 0) {
      // Close a C comment...
      *style++ = current;
      *style++ = current;
      text ++;
      length --;
      current = 'A';
      col += 2;
      continue;
    } else if (current == 'D') {
      // Continuing in string...
      if (strncmp(text, "\\\"", 2) == 0) {
        // Quoted end quote...
	*style++ = current;
	*style++ = current;
	text ++;
	length --;
	col += 2;
	continue;
      } else if (*text == '\"') {
        // End quote...
	*style++ = current;
	col ++;
	current = 'A';
	continue;
      }
    }

    // Copy style info...
    if (current == 'A' && (*text == '{' || *text == '}')) *style++ = 'G';
    else *style++ = current;
    col ++;

    last = isalnum((*text)&255) || *text == '_' || *text == '.';

    if (*text == '\n') {
      // Reset column and possibly reset the style
      col = 0;
      if (current == 'B' || current == 'E') current = 'A';
    }
  }
}

void QueryEditor::style_init(void) {
  char *style = new char[_textbuffer.length() + 1];
  char *text = _textbuffer.text();

  memset(style, 'A', _textbuffer.length());
  style[_textbuffer.length()] = '\0';

  //todo if (!_stylebuffer) _stylebuffer = *(new Fl_Text_Buffer(_textbuffer.length()));

  style_parse(text, style, _textbuffer.length());

  _stylebuffer.text(style);
  delete[] style;
  free(text);
}

void QueryEditor::static_style_update(int        pos,		// I - Position of update
             int        nInserted,	// I - Number of inserted chars
	     int        nDeleted,	// I - Number of deleted chars
             int        /*nRestyled*/,	// I - Number of restyled chars
	     const char * /*deletedText*/,// I - Text that was deleted
             void       *cbArg)           // I - Callback data
{	

    ((QueryEditor*)cbArg)->style_update( pos, nInserted, nDeleted, -1, 0 );
}

void QueryEditor::style_update(int pos,		// I - Position of update
             int        nInserted,	// I - Number of inserted chars
	     int        nDeleted,	// I - Number of deleted chars
             int        /*nRestyled*/,	// I - Number of restyled chars
	     const char * /*deletedText*/ )           // I - Callback data
{	
  int	start,				// Start of text
	end;				// End of text
  char	last,				// Last style on line
	*style,				// Style data
	*text;				// Text data


  // If this is just a selection change, just unselect the style buffer...
  if (nInserted == 0 && nDeleted == 0) {
    _stylebuffer.unselect();
    return;
  }

  // Track changes in the text buffer...
  if (nInserted > 0) {
    // Insert characters into the style buffer...
    style = new char[nInserted + 1];
    memset(style, 'A', nInserted);
    style[nInserted] = '\0';

    _stylebuffer.replace(pos, pos + nDeleted, style);
    delete[] style;
  } else {
    // Just delete characters in the style buffer...
    _stylebuffer.remove(pos, pos + nDeleted);
  }

  // Select the area that was just updated to avoid unnecessary
  // callbacks...
  _stylebuffer.select(pos, pos + nInserted - nDeleted);

  // Re-parse the changed region; we do this by parsing from the
  // beginning of the previous line of the changed region to the end of
  // the line of the changed region...  Then we check the last
  // style character and keep updating if we have a multi-line
  // comment character...
  start = _textbuffer.line_start(pos);
//  if (start > 0) start = textbuf->line_start(start - 1);
  end   = _textbuffer.line_end(pos + nInserted);
  text  = _textbuffer.text_range(start, end);
  style = _stylebuffer.text_range(start, end);
  if (start==end)
    last = 0;
  else
    last  = style[end - start - 1];

//  printf("start = %d, end = %d, text = \"%s\", style = \"%s\", last='%c'...\n",
//         start, end, text, style, last);

  style_parse(text, style, end - start);

//  printf("new style = \"%s\", new last='%c'...\n",
//         style, style[end - start - 1]);

  _stylebuffer.replace(start, end, style);
  redisplay_range(start, end);

  if (start==end || last != style[end - start - 1]) {
//    printf("Recalculate the rest of the buffer style\n");
    // Either the user deleted some text, or the last character
    // on the line changed styles, so reparse the
    // remainder of the buffer...
    free(text);
    free(style);

    end   = _textbuffer.length();
    text  = _textbuffer.text_range(start, end);
    style = _stylebuffer.text_range(start, end);

    ///style_parse(text, style, end - start);

    _stylebuffer.replace(start, end, style);
    redisplay_range(start, end);
  }

  free(text);
  free(style);
}



void QueryEditor::style_unfinished_cb( int, void* ) {
}

void QueryEditor::changed_cb(int, int nInserted, int nDeleted,int, const char*, void* v) {
//  if ((nInserted || nDeleted) && !loading) changed = 1;
//  EditorWindow *w = (EditorWindow *)v;
//  set_title(w);
//  if (loading) w->editor->show_insert_position();
}

QueryEditor::QueryEditor(  int x, int y, int w, int h, const char* pTitle ) 
: Fl_Text_Editor( x, y, w, h, pTitle )
, _textbuffer( *(new Fl_Text_Buffer() ) )
{
    Fl_Text_Editor::Style_Table_Entry _styles[1];
    textfont(FL_COURIER);
    textsize(TS);
  //w->editor->wrap_mode(Fl_Text_Editor::WRAP_AT_BOUNDS, 250);
    buffer( &_textbuffer );
    end();
    
    style_init();
    highlight_data( &_stylebuffer, styletable,
                              sizeof(styletable) / sizeof(styletable[0]),
			      'A', style_unfinished_cb, 0);
   
  _textbuffer.add_modify_callback(static_style_update, this );
  _textbuffer.add_modify_callback(changed_cb, this );
  _textbuffer.call_modify_callbacks();
     
}


QueryEditor::~QueryEditor() {
}

