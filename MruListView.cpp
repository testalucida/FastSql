/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MruListView.cpp
 * Author: martin
 * 
 * Created on 25. Juni 2017, 21:23
 */

#include "MruListView.h"

using namespace std;

MruListView::MruListView(  int x, int y, int w, int h ) 
: Fl_Menu_Button( x, y, w, h, "Zuletzt verwendet" )
{
    box( FL_FRAME );
    visible_focus( 0 );
    tooltip( "Zuletzt verwendete Queries" );
}

void MruListView::setMruList( const MruList& mruList ) {
    _mruList.path = mruList.path;
    _mruList.queries.clear();
    this->clear();
    for_each( mruList.queries.begin(), mruList.queries.end(), [&]( const Mru& mru ) {
        _mruList.queries.push_back( mru );
        this->add( mru.queryname.c_str() );
    });
}

MruListView::~MruListView() {
}

