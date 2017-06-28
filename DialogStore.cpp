/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DialogStore.cpp
 * Author: martin
 * 
 * Created on 24. Juni 2017, 11:09
 */

#include "DialogStore.h"
#include "MruStore.h"
#include "Action.h"

using namespace std;

DialogStore *DialogStore::_pThis = 0;

DialogStore::DialogStore() {
}

DialogStore& DialogStore::instance() {
    if( !_pThis ) {
        _pThis = new DialogStore();
    }
    return *_pThis;
}

FastSqlDialog& DialogStore::addDialog( int x, int y, int w, int h ) {
    int n = getDialogCount() + 1;
    string title = "FastSql #";
    title.append( to_string( n ) );
    FastSqlDialog *pDlg = new FastSqlDialog( x, y, w, h, title.c_str() );
    pDlg->callback( staticOnDialogClose, pDlg );
    pDlg->show();
   
    setMruList( *pDlg );
    _dlgs.push_back( pDlg );
    return *pDlg;
}

FastSqlDialog& DialogStore::addDialog( FastSqlDialog& refDlg ) {
    int x = refDlg.x() + refDlg.w();
    int y = refDlg.y() - 28;
    int w = refDlg.w();
    int h = refDlg.h();
    
    return addDialog( x, y, w, h );
}

void DialogStore::staticOnDialogClose( Fl_Widget *pW, void *pDlg ) {
    fprintf( stderr, "closing %s\n", ((FastSqlDialog*)pDlg)->label() );
    delete (FastSqlDialog*)pDlg;
}

void DialogStore::staticOnMenuButtonClick( Fl_Widget *pBtn, void *pDlg ) {
      Fl_Button *pMenuBtn = (Fl_Button*)pBtn;
      Action action = (Action)(unsigned char)(pBtn->type());
      FastSqlDialog *pThis = (FastSqlDialog*)pDlg;
      switch( action ) {
          case Action::ADD_DIALOG:
              DialogStore::instance().addDialog( *pThis );
              break;
          case Action::DELETE_DIALOG:
              DialogStore::instance().deleteDialog( *pThis );
              break;
          case Action::DELETE_ALL:
              DialogStore::instance().deleteAllDialogs();
              break;
          default:
              break;
      }
  }

void DialogStore::setMruList( FastSqlDialog& dlg ) const {
    const MruList &mruList = MruStore::instance().getMruList();
    dlg.setMruList( mruList );
}

void DialogStore::deleteDialog( FastSqlDialog &dlg ) {
     for( auto itr = _dlgs.begin(); itr != _dlgs.end(); itr++ ) {
         if( *itr == &dlg ) {
             _dlgs.erase( itr );
             delete &dlg;
             break;
         }
     }
 }
 
void DialogStore::deleteAllDialogs() {
    for_each( _dlgs.begin(), _dlgs.end(), [] (FastSqlDialog* pDlg ) {
        
        delete pDlg;
    });
}

DialogStore::~DialogStore() {
}

