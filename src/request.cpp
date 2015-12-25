#include <request.h>

request::request( http_client *client,std::string verb, std::string base_url )
    :_client(client),_verb(verb),_base_url(base_url)
{
    
}

std::string request::do_request()
{
    // some sanity check
    http_request req = {_verb,_body,url()};
    std::string result = _client->Do(req);
    return result;
}

void request::watch()
{

    std::thread t([this](){
        http_request req = {_verb,_body,url()};
        _client->Do(req);
    });
}

std::string url()
{   // _base_url include ports
    return _base_url + _path + _resource + _resource_name;
}

