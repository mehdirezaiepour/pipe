//
// Created by Piade on 7/12/19.
//

#ifndef NAMEDPIPEPIPECLIENT_H
#define NAMEDPIPEPIPECLIENT_H


#include <sys/stat.h>       // S_IRUSR, S_IWUSR, S_IRGRP, S_IROTH, mkfifo
#include <fcntl.h>          // O_RDONLY, O_WRONLY,
#include <string>           // std::string,
#include <unistd.h>         // write, read, close,
#include <memory>           // std::unique_ptr,

class NamedPipeClient
{
public:

    NamedPipeClient() = delete;
    NamedPipeClient(const std::string pipe_name, const std::size_t max_message_size);
    ~NamedPipeClient() = default;
    std::string ask(const std::string &message);

private:
    std::string pipe_name_;
    std::size_t max_message_size_;
    const std::size_t zero_byte_end_str_ = 1;


};




#endif //NAMEDPIPEPIPECLIENT_H
