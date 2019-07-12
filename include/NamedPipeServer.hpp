//
// Created by Piade on 7/11/19.
//

#ifndef NAMEDPIPEPIPESEVER_H
#define NAMEDPIPEPIPESEVER_H


#include <sys/stat.h>       // S_IRUSR, S_IWUSR, S_IRGRP, S_IROTH, mkfifo
#include <fcntl.h>          // O_RDONLY, O_WRONLY,
#include <string>           // std::string,
#include <unistd.h>         // write, read, close,
#include <memory>           // std::unique_ptr,

class NamedPipeServer
{
public:

    NamedPipeServer() = delete;
    NamedPipeServer(const std::string &pipe_name, const std::size_t max_message_size);
    ~NamedPipeServer();
    std::string listen();
    bool answer(const std::string &message);

private:
    std::string pipe_name_;
    std::size_t max_message_size_;
    const std::size_t zero_byte_end_str_ = 1;

};



#endif //NAMEDPIPEPIPESEVER_H
