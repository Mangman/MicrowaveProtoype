//  Created by Stepan on 29.04.16.

#ifndef my_exception_h
#define my_exception_h
#include <stdio.h>
#include <string.h>

struct place
{
    char* file_;
    int line_;
    char* function_;
    
    place (const char* file, int line, const char* function):
        file_((char*)""), line_(-5), function_((char*)"")
    {
        if (file == nullptr || function == nullptr)
        {
            
        }
        else
        {
            file_ = new char [strlen(file)];
            function_ = new char [strlen(function)];
            std::strcpy(file_, file);
            std::strcpy(function_, function);
            line_ = line;
        }
    }
    
    ~place() {
        if (!file_) {
            delete file_;
        }
        if (!function_){
            delete function_;
        }
    }
};

struct my_exception : std::exception
{
    //MARK: Parameters
    
    std::string text;
    my_exception* parent_pointer;
    place pos;
    
    //MARK: Setup
    
    my_exception(std::string text, my_exception* parent_pointer, place pos):
        text(text), parent_pointer(parent_pointer), pos(pos)
    {}
    
    //MARK: Methods
    
    const char* what();
};



const char* my_exception::what()
{
    std::string message = (std::string("\n\n---------\nerror in:\nfile - ")+
                           std::string(pos.file_)+
                           std::string("\n")+
                           std::string("line - ")+
                           std::to_string(pos.line_)+
                           std::string("\n")+
                           std::string("function - ")+
                           std::string(pos.function_)+
                           std::string("\n")+
                           std::string("message - \"")+
                           text+
                           std::string("\"\n---------\n\n"));
    if (parent_pointer == nullptr) {
        return (message.c_str());
    }
    else {
        return ((message+std::string("\nbecause of:\n")+
                         std::string(parent_pointer->what())).c_str());
    }
}

#endif
