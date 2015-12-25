#pragma once

struct http_request
{
    std::string verb;
    std::string body;
    std::string url;
};
class http_client
{
public:
    virtual std::string Do(http_request req) = 0;
};
