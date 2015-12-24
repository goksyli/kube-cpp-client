#include <iostream>
#include <string>
// class for making request string
class request
{
public:
    request( http_client *client,std::string verb,std::string base_url );
    void watch();
    std::string do_request();
    std::string url();
    request &set_ns(std::string ns){ _namespace=ns;return *this;}
    request &set_res(std::string res){ _resource=res;return *this;} 
    request &set_body(std::string body){_body=body;return *this;}
    request &set_name(std::string name){_resource_name=name;return *this;}

    typedef std::unordered_map<std::string,std::string> param_map;
    http_client     *_client;
    std::string     _verb;
    std::string     _base_url;
    std::stirng     _path;
    param_map       _params;
    std::string     _namespace;
    std::string     _resource;
    std::string     _resource_name;
    std::string     _body;
};

struct http_request
{
    std::string verb;
    std::string body;
    std::string url;
};
