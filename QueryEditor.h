/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   QueryEditor.h
 * Author: martin
 *
 * Created on 25. Juni 2017, 18:37
 */

#ifndef QUERYEDITOR_H
#define QUERYEDITOR_H

#include <FL/Fl_Text_Editor.H>
#include <FL/Fl_Text_Buffer.H>

#include "std.h"

class QueryEditor : public Fl_Text_Editor {
public:
    QueryEditor( int x, int y, int w, int h, const char* pTitle = 0 );
    
    virtual ~QueryEditor();
private:
    void style_init(void);
    static void static_style_update( int pos,		// I - Position of update
             int        nInserted,	// I - Number of inserted chars
	     int        nDeleted,	// I - Number of deleted chars
             int        /*nRestyled*/,	// I - Number of restyled chars
	     const char * /*deletedText*/,// I - Text that was deleted
             void       *cbArg);         // I - Callback data
    
    void style_update( int pos,		// I - Position of update
             int        nInserted,	// I - Number of inserted chars
	     int        nDeleted,	// I - Number of deleted chars
             int        /*nRestyled*/,	// I - Number of restyled chars
	     const char * /*deletedText*/ );   
    
    static void style_unfinished_cb( int, void* );
    static void changed_cb(int, int nInserted, int nDeleted,int, const char*, void* v) ;
private:
    Fl_Text_Buffer &_textbuffer;
    Fl_Text_Buffer _stylebuffer;
};

#endif /* QUERYEDITOR_H */

