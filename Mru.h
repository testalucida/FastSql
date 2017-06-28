/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MruList.h
 * Author: martin
 *
 * Created on 24. Juni 2017, 22:57
 */

#ifndef MRULIST_H
#define MRULIST_H

#include "std.h"

struct Mru {
    std::string querypath;
    std::string queryname;
    std::string appendix; // .sql
};

struct MruList {
    std::string path; //Verzeichnis, aus dem die MRU-Liste gelesen wurde
    std::vector<Mru> queries; 
};

#endif /* MRULIST_H */

