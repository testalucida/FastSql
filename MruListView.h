/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MruListView.h
 * Author: martin
 *
 * Created on 25. Juni 2017, 21:23
 */

#ifndef MRULISTVIEW_H
#define MRULISTVIEW_H

#include <FL/Fl_Menu_Button.H>
#include "std.h"
#include "Mru.h"

class MruListView : public Fl_Menu_Button {
public:
    MruListView( int x, int y, int w, int h );
    
    void setMruList( const MruList& );
    
    virtual ~MruListView();
private:
    MruList _mruList;
};

#endif /* MRULISTVIEW_H */

