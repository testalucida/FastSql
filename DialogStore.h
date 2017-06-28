/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DialogStore.h
 * Author: martin
 *
 * Created on 24. Juni 2017, 11:09
 */

#ifndef DIALOGSTORE_H
#define DIALOGSTORE_H

#include "std.h"
#include "FastSqlDialog.h"

class DialogStore {
public:
    
    static DialogStore& instance();
    
    FastSqlDialog& addDialog( FastSqlDialog& );
    
    FastSqlDialog& addDialog( int x, int y, int w = 500, int h = 400 );
    
    
    static void staticOnDialogClose( Fl_Widget*, void* );
    
    static void staticOnMenuButtonClick( Fl_Widget *pBtn, void *pDlg );
    
     void deleteDialog( FastSqlDialog & );
    
    void deleteAllDialogs();
    
    int getDialogCount() const {
        return _dlgs.size();
    }
    
    virtual ~DialogStore();
private:
    DialogStore();
    void setMruList( FastSqlDialog& ) const;
private:
    static DialogStore *_pThis;
    std::vector<FastSqlDialog*> _dlgs;
};

#endif /* DIALOGSTORE_H */

