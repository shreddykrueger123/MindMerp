//It lacks a few features presently but I plan on evolving it a bit in the future
//until it's perfect and capable for all situations.
//Why would I do this instead of just using what's already there?
//I guess I just enjoy reinventing wheels like any C++er worth their weight
//in old man's beard.

#include <iostream>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include "globals.h"

using namespace std;


FileIO::FileIO(){
this->file=NULL;
}


bool FileIO::readProc(const char* progName){
FILE* file=popen(progName, "r");
char buffer[100];
int status;
this->output="";

    while(fgets(buffer, 100, file)){
    this->output+=buffer;
    }

status=pclose(file);

    if(!WEXITSTATUS(status))
    return 1;

this->error="Executable: ";
this->error+=progName;
this->error+=" could not be executed, probably doesn't exist";
return 0;
}


bool FileIO::getUser(){
return this->readProc("whoami");
}


off_t FileIO::filesize(const char* filename){
struct stat st;

    if(stat(filename, &st)==0){
    return st.st_size;
    }

this->error="File ";
this->error+=filename;
this->error+=" could not be sized, probably doesn't exist";
return 0;
return -1;
}


bool FileIO::readfile(const char* filename, bool mode){
FILE* file=NULL;

    if(!mode)
    file=fopen(filename, "r");
    else
    file=fopen(filename, "rb");

    if(file!=NULL){
    off_t size=this->filesize(filename);
    char buffer[size];
    buffer[fread(buffer, sizeof(char), size, file)]='\0';
    this->output=buffer;
    fclose(file);
    return 1;
    }

this->error="File: ";
this->error+=filename;
this->error+=" could not be opened, probably doesn't exist";
return 0;
}


bool FileIO::writefile(const char* filename, const char* data, off_t size, bool mode){

    if(!mode)
    file=fopen(filename, "w");
    else
    file=fopen(filename, "wb");

    if(file!=NULL){
    fwrite(data, sizeof(char), size, file);
    fclose(file);
    return 1;
    }

this->error="File: ";
this->error+=filename;
this->error+=" could not be opened, probably doesn't exist";
return 0;
}


bool FileIO::writefile(const char* filename, const string& data){
file=fopen(filename, "w");

    if(file!=NULL){
    fwrite(data.c_str(), sizeof(char), data.length(), file);
    fclose(file);
    return 1;
    }

this->error="File: ";
this->error+=filename;
this->error+=" could not be opened, probably doesn't exist";
return 0;
}

//I disagree with your opinion that reading/writing to/from files
//isn't way cooler and better looking when done this way.
bool FileIO::open(const char* filename, bool mode){

    if(!mode)
    this->file=fopen(filename, "rb");
    else
    this->file=fopen(filename, "wb");

this->filemode=mode;

    if(this->file!=NULL)
    return 1;

this->error="File: ";
this->error+=filename;
this->error+=" could not be opened, probably doesn't exist";
return 0;
}

//dummyRes only exists because the compiler annoyingly warns against ignoring the
//return value of fread and fwrite, which was not needed here.
FileIO FileIO::operator[](char* v){

    if(!this->filemode)
    this->dummyRes=fread(v, sizeof(*v), 1, this->file);

return *this;
}


FileIO FileIO::operator[](char v){

    if(this->filemode)
    this->dummyRes=fwrite(&v, sizeof(v), 1, this->file);

return *this;
}


FileIO FileIO::operator[](short* v){

    if(!this->filemode)
    this->dummyRes=fread(v, sizeof(*v), 1, this->file);

return *this;
}


FileIO FileIO::operator[](short v){

    if(this->filemode)
    this->dummyRes=fwrite(&v, sizeof(v), 1, this->file);

return *this;
}


FileIO FileIO::operator[](int* v){

    if(!this->filemode)
    this->dummyRes=fread(v, sizeof(*v), 1, this->file);

return *this;
}


FileIO FileIO::operator[](int v){

    if(this->filemode)
    this->dummyRes=fwrite(&v, sizeof(v), 1, this->file);

return *this;
}


FileIO FileIO::operator[](float* v){

    if(!this->filemode)
    this->dummyRes=fread(v, sizeof(*v), 1, this->file);

return *this;
}


FileIO FileIO::operator[](float v){

    if(this->filemode)
    this->dummyRes=fwrite(&v, sizeof(v), 1, this->file);

return *this;
}


FileIO FileIO::operator[](const string& v){

    if(this->filemode)
    this->dummyRes=fwrite(v.c_str(), sizeof(char), v.length(), this->file);

return *this;
}

//As it turns out, ya can't have multiple parameters with operator[]
//so I went with operator() in this specific circumstance.
FileIO FileIO::operator()(string& v, size_t size){

    if(!this->filemode){
    char buffer[size];
    buffer[fread(buffer, sizeof(char), size, this->file)]='\0';
    v=buffer;
    }

return *this;
}


void FileIO::close(){
fclose(this->file);
this->file=NULL;
}


bool FileIO::listFiles(const char* path, vector<string>& files, vector<string>& folders){
DIR *dir;
dirent *ent;

    if((dir=opendir(path))!=NULL){

        while((ent=readdir(dir))!=NULL){
        struct stat status;
        string spath=path;

            if(spath[spath.length()-1]!='/')
            spath+="/";

        spath+=ent->d_name;

            if(stat(spath.c_str(), &status)==-1){
            this->error="stat error on: "+spath;
            return 0;
            }

            if(S_ISDIR(status.st_mode))
            folders.push_back(ent->d_name);
            else
            files.push_back(ent->d_name);

        }

    closedir(dir);
    return 1;
    }

this->error="could not open directory: "+(string)path;
return 0;
}

