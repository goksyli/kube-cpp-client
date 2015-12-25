#pragma once
#include <json.hpp>
#include <http_client.h>
// help class for manipulating pods in kubernetes
using json = nlohmann::json;
class api_pods
{
    
    json create_pod(json pod);
    bool delete_pod(json pod);
    void watch_pod();
private:
    http_client  *_client;
    std::string _ns;
    std::string _server_addr;
};
