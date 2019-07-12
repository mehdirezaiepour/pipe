//
// Created by Piade on 7/12/19.
//

#include "NamedPipeClient.hpp"

NamedPipeClient::NamedPipeClient(const std::string pipe_name, const std::size_t max_message_size) {
    pipe_name_ = pipe_name;
    max_message_size_ = max_message_size;
    struct stat file_stat;
    stat(pipe_name_.c_str(), &file_stat);
    const int is_the_pipe_there = S_ISFIFO(file_stat.st_mode);
    // on file masks : https://www.gnu.org/software/libc/manual/html_node/Permission-Bits.html
    if (is_the_pipe_there == 0) {
        throw "There is no pipe with the name '" + pipe_name_ + "'."
              + " Check whether server is running or not.";
    }
}

std::string NamedPipeClient::ask(const std::string &message) {
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
        if(bytes_wrote >= 0){

            // Open FIFO, and read from it, then close the file.
            fifo_file = open(pipe_name_.c_str(), O_RDONLY);
            std::unique_ptr<char> answer(new char[max_message_size_ + zero_byte_end_str_]);
            read(fifo_file, answer.get(), max_message_size_ + zero_byte_end_str_);
            close(fifo_file);

            return std::string(answer.get());
        } else {
            throw "Error while trying to write into the FIFO file.";
        }
    }
}
