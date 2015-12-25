#include <api_pods.h>
#include <request.h>
json api_pods::create_pod(json pod)
{
    request req(_client,"POST",_server_addr);
    json result = json::parse(req.set_ns(_ns).set_res("pods").set_body(pod.dump()).do_request());
    return result;
}

bool api_pods::delete_pod(json pod)
{
    request req(_client,"DELETE",_server_addr);
    json result = json::parse(req.set_ns(_ns).set_res("pods").set_name(pod["meta"]["name"]).do_request());
    return result["status"] != "Failure";
}
void api_pods::watch_pod()
{
    request req(_client,"GET",_server_addr);
    req.set_prefix("watch").set_ns(_ns).set_res("pods").watch();
}
