//
// Created by alin on 12/21/16.
//
#pragma once
#include "FileWriter.h"
#include "Cacher.h"
#include <fstream>
using namespace std;

void FileWriter::createEmptyFile() {
    file = new ofstream(path,ios :: out | ios::binary);
}
void FileWriter::append(const char* buffer,int count)
{
    file->write(buffer,count);
}
void FileWriter::finish()
{
    file->close();
    delete file;

    Cacher *cacher = Cacher::getInstance();
    cacher->registerNewFile(fileDescription,path);
}

FileWriter::FileWriter(char *path, FileDescription fileDescription) {
    this->path = path;
    this->fileDescription = fileDescription;

}
