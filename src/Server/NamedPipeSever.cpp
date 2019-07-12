//
// Created by Piade on 7/11/19.
//

#include "NamedPipeServer.hpp"


NamedPipeServer::NamedPipeServer(const std::string &pipe_name, const std::size_t max_message_size) {
    pipe_name_ = pipe_name;
    max_message_size_ = max_message_size;

    const int error_code = mkfifo(pipe_name_.c_str(), S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    // on file masks : https://www.gnu.org/software/libc/manual/html_node/Permission-Bits.html
    if (error_code > 0) {
        throw "function mkfifo returned a non-zero value";
    }
}

NamedPipeServer::~NamedPipeServer() {
    remove(pipe_name_.c_str());
}

std::string NamedPipeServer::listen() {
    // Open FIFO, and read from it, then close the file.
    int fifo_file = open(pipe_name_.c_str(), O_RDONLY);
    std::unique_ptr<char> answer(new char[max_message_size_ + zero_byte_end_str_]);
    read(fifo_file, answer.get(), max_message_size_ + zero_byte_end_str_);
    close(fifo_file);

    return std::string(answer.get());
}

bool NamedPipeServer::answer(const std::string &message) {
    const size_t message_size = message.size() * sizeof(char);
    if (message_size > max_message_size_) {
        throw R"mmm(Message size is bigger than the maximum
                        message size passes to the constructor.
                        Message was ignored!!!)mmm";
    } else {

        int fifo_file;
        fifo_file = open(pipe_name_.c_str(), O_WRONLY);

        // Write the message into the FIFO, and close the file.
        const ssize_t bytes_wrote
                = write(fifo_file, message.c_str(), message_size + zero_byte_end_str_);
        close(fifo_file);
        return bytes_wrote >= 0;
    }
}
