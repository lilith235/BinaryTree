#ifndef ERRORINFO_H
#define ERRORINFO_H
#include <iostream>
#include <string>

class illegalParameterValue
{
public:
    illegalParameterValue() :
        message("Illegal parameter value") { }
    illegalParameterValue(const std::string theMessage) { message = theMessage; }
    void outputMessage() { std::cout << message << std::endl; }

private:
    std::string message;
};

class stackEmpty
{
public:
    stackEmpty() :
        message("Stack is empty") { }
    void outputMessage() { std::cout << message << std::endl; }
private:
    std::string message;
};

class queueEmpty
{
public:
    queueEmpty() :
        message("Queue is empty") { }
    void outputMessage() { std::cout << message << std::endl; }
private:
    std::string message;
};

class fileOpenError
{
public:
    fileOpenError() :
        message("File open failed") { }
    void outputMessage() { std::cout << message << std::endl; }
private:
    std::string message;
};

class fileEmpty
{
public:
    fileEmpty() :
        message("File is empty") { }
    void outputMessage() { std::cout << message << std::endl; }
private:
    std::string message;
};

class invalidSequence
{
public:
    invalidSequence() :
        message("Sequence is invalid") { }
    void outputMessage() { std::cout << message << std::endl; }
private:
    std::string message;
};


#endif // ERRORINFO_H
