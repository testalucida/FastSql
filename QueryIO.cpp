/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   QueryIOController.cpp
 * Author: martin
 * 
 * Created on 25. Juni 2017, 19:20
 */

#include "QueryIO.h"

QueryIOController *QueryIOController::_pThis = 0;

QueryIOController& QueryIOController::instance() {
    if( !_pThis ) {
        _pThis = new QueryIOController();
    }
    return *_pThis;
}

QueryIOController::QueryIOController() {
}


QueryIOController::~QueryIOController() {
}

