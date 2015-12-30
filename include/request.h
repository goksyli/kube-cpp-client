#pragma once
#include <iostream>
#include <string>
#include <http_client.h>
#include <unordered_map>
// class for making request string
class request
{
public:
    request( http_client *client,std::string verb,std::string base_url);
    void watch();
    std::string do_request();
    std::string url();
    request &set_ns(std::string ns){ _namespace=ns;return *this;}
    request &set_res(std::string res){ _resource=res;return *this;} 
    request &set_body(std::string body){_body=body;return *this;}
    request &set_name(std::string name){_resource_name=name;return *this;}
    request &set_prefix(std::string prefix){ _path = prefix + _path;return *this;} 

    using param_map = std::unordered_map<std::string,std::string>;
    http_client     *_client;
    std::string     _verb;
    std::string     _base_url;
    std::string     _path;
    param_map       _params;
    std::string     _namespace;
    std::string     _resource;
    std::string     _resource_name;
    std::string     _body;
};

