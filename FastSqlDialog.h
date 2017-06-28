/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FastSqlDialog.h
 * Author: martin
 *
 * Created on 23. Juni 2017, 13:14
 */

#ifndef FASTSQLDIALOG_H
#define FASTSQLDIALOG_H

#include <FL/Fl_Double_Window.H>
#include "std.h"
#include "Action.h"

class Fl_Button;
class MruListView;
class Fl_Widget;
struct MruList;

class FastSqlDialog : public Fl_Double_Window {
public:
    FastSqlDialog( int x, int y, int w, int h, const char *pTitle );
    
    void setMruList( const MruList& );
    
    void addMru( std::string );
    
    virtual ~FastSqlDialog();
public:
    
private:
    Fl_Button*
    createMenuButton( int x, int y, const char** ppIcon, const char *pTooltip, Action action );
    static void staticOnMenuButtonClick( Fl_Widget*, void* );
    static void staticOnMruListClick( Fl_Widget*, void* );
    void onMruListClick();
private:
    MruListView *_pMru;
};

#endif /* FASTSQLDIALOG_H */

