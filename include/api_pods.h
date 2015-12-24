
// help class for manipulating pods in kubernetes
class api_pods
{
    
    json create_pod(json pod);
    bool delete_pod(json pod);
    void watch_pod();
private:
    http_client  *_client;
    std::string _ns;
    std::string _server_addr;
}
