/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   QueryIOController.h
 * Author: martin
 *
 * Created on 25. Juni 2017, 19:20
 */

#ifndef QUERYIOCONTROLLER_H
#define QUERYIOCONTROLLER_H

class QueryIOController {
public:
    static QueryIOController& instance();
    
    virtual ~QueryIOController();
private:
    QueryIOController();
private:
    static QueryIOController *_pThis;
};

#endif /* QUERYIOCONTROLLER_H */

