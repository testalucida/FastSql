/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FastSqlDialog.cpp
 * Author: martin
 * 
 * Created on 23. Juni 2017, 13:14
 */

#include "FastSqlDialog.h"
#include <FL/Fl_Tile.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Menu.H>
#include <FL/Fl_Menu_Button.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_XPM_Image.H>
#include <FL/Fl_Pixmap.H>
#include "pixmap/new.xpm"
#include "pixmap/open.xpm"
#include "pixmap/delete.xpm"
#include "pixmap/delete_all.xpm"
#include "pixmap/save.xpm"
#include "pixmap/saveas.xpm"
#include "pixmap/run.xpm"
#include "MruListView.h"
#include "QueryEditor.h"
#include "ResultTable.h"
#include "DialogStore.h"

using namespace std;

FastSqlDialog::FastSqlDialog( int x, int y, int w, int h, const char *pTitle ) 
: Fl_Double_Window( x, y, w, h, pTitle )
{
    int hspace = 2, vspace = 2;
    Fl_Group *pMenu = new Fl_Group( 0, 0, w, 30 + 2*vspace );
    
    Fl_Widget *pBtn = createMenuButton( hspace, vspace, new_xpm, 
                                        "Neues FastSql-Fenster erzeugen", 
                                        Action::ADD_DIALOG );
    
    pBtn = new MruListView( pBtn->x() + pBtn->w() + hspace, vspace+3, 140, 24 );
    _pMru = (MruListView*)pBtn;
    _pMru->callback( staticOnMruListClick, this );
   
    pBtn = createMenuButton( pBtn->x() + pBtn->w() + hspace, vspace, open_xpm,
                             "Query öffnen",
                             Action::OPEN_QUERY );

    pBtn = createMenuButton( pBtn->x() + pBtn->w() + hspace, vspace, save_xpm,
                             "Query speichern",
                             Action::SAVE_QUERY );
    
    pBtn = createMenuButton( pBtn->x() + pBtn->w() + hspace, vspace, saveas_xpm,
                             "Query unter anderem Namen speichern",
                             Action::SAVE_QUERY_AS );
    
    pBtn = createMenuButton( pBtn->x() + pBtn->w() + hspace,
                             vspace, run_xpm,
                             "Query ausführen",
                             Action::RUN_QUERY );
    
    
    pBtn = createMenuButton( w - 30 - hspace, vspace, delete_all_xpm, 
                             "FastSql beenden",
                             Action::DELETE_ALL );
    
    
    pMenu->end();
    
    int y2 = pMenu->y() + pMenu->h();
    
    Fl_Tile *pTile = new Fl_Tile( 0, y2, w, h - y2 - 25 );
    int upperH = pTile->h() / 2;
    int lowerH = pTile->h() - upperH;
    QueryEditor *pEdi = new QueryEditor( pTile->x(), pTile->y(), pTile->w(), upperH );
    
    y2 = pEdi->y() + pEdi->h();
    int h2 = pTile->h() - pEdi->h();
    ResultTable *pTbl = new ResultTable( pTile->x(), y2, pTile->w(), h2 );
    pTile->end();
    
    y2 = pTile->y() + pTile->h();
    Fl_Group *pMessage = new Fl_Group( pTbl->x(), y2, pTile->w(), 25 );
    pMessage->end();
    
    end();
}

void FastSqlDialog::setMruList( const MruList& mruList ) {
    _pMru->clear();
//    for_each( mruList.begin(), mruList.end(), [&]( string mru ) {
//        _pMru->add( mru.c_str() );
//    });
}
    
void FastSqlDialog::addMru( std::string mru ) {
    _pMru->add( mru.c_str() );
}


 Fl_Button* FastSqlDialog::createMenuButton( int x, int y, const char** ppIcon, const char *pTooltip, Action action )
 {
     Fl_Button *pBtn = new Fl_Button( x, y, 30, 30 );
     pBtn->box( FL_FLAT_BOX );
     pBtn->down_box( FL_DOWN_BOX );
     Fl_Pixmap *pPixmap = new Fl_Pixmap( ppIcon );
     pBtn->image( pPixmap );
     pBtn->tooltip( pTooltip );
     pBtn->visible_focus( 0 );
     pBtn->type( (unsigned char)action );
     pBtn->callback( DialogStore::staticOnMenuButtonClick, this );
 }
 
  
  void FastSqlDialog::staticOnMruListClick( Fl_Widget *pBtn, void *pDlg ) {
      ((FastSqlDialog*)pDlg)->onMruListClick();
  }
  
  void FastSqlDialog::onMruListClick() {
      fprintf( stderr, "%s\n", _pMru->text() );
  }

FastSqlDialog::~FastSqlDialog() {
    //egal, ob ein Dialog über die Schließebox oder den Menübutton XX geschlossen
    //wird, hier kommt der Thread rein.
    //'==> prüfen, ob eine Query noch nicht gespeichert ist und Sicherheitsabfrage.
    //fprintf( stderr, "destructor %s\n", this->label() );
}

