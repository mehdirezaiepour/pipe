#include "NamedPipeServer.hpp"
#include "NamedPipeClient.hpp"
//------
#include <iostream>
#include <thread>           // std::thread, std::this_thread::sleep_for,
#include <chrono>           // std::chrono::seconds,


bool server_thread_tasks(){
    const std::string pipe_name = "my_pipe_name";
    NamedPipeServer server(pipe_name, 21);
    std::string q = server.listen();
    std::cout << "\n@ server: Question is: " << q << std::endl;
    server.answer("I don't know!");
    return true;
}


bool client_thread_tasks(){
    const std::string pipe_name = "my_pipe_name";
    NamedPipeClient client(pipe_name, 21);
    std::string ans = client.ask("Are you the server?");
    std::cout << "\n@ client: Answer is: " << ans << std::endl;
    return true;
}


int main() {

    std::thread server_thread(server_thread_tasks);

    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::thread client_thread(client_thread_tasks);

    client_thread.join();
    server_thread.join();

    return 0;
}