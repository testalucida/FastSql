/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FileIO.h
 * Author: martin
 *
 * Created on 25. Juni 2017, 09:39
 */

#ifndef FILEIO_H
#define FILEIO_H

#include "std.h"

class FileIO {
public:
    
    static FileIO& instance();

    /**Methode stellt sicher, dass path mit "/" endet */
    void getPathNormalized( std::string path ) const;
    
    bool readFile( const std::string &pathnfile, std::vector<std::string>& lines ) const;
    
    bool writeFile( const std::string &pathnfile, const std::vector<std::string>& lines ) const;
    
    virtual ~FileIO();
    
private:
    FileIO();
       
private:
    static FileIO *_pThis;
};

#endif /* FILEIO_H */

