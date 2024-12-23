#ifndef __APIENDPOINTS_H__
#define __APIENDPOINTS_H__

#include <iostream>
#include <map>
#include <string>

class ApiEndpoints
{
  public:
    ApiEndpoints();
    ~ApiEndpoints();

    void
    addEndpoint(const std::string &domain, const std::string &action, const std::string &endpoint)
    {
        endpoints[domain][action] = endpoint;
    }

    std::string getEndpoint(const std::string &domain, const std::string &action) const
    {
        auto domainIt = endpoints.find(domain);
        if (domainIt != endpoints.end())
        {
            auto actionIt = domainIt->second.find(action);
            if (actionIt != domainIt->second.end())
            {
                return actionIt->second;
            }
        }
        return "";
    }

  private:
    std::map<std::string, std::map<std::string, std::string>> endpoints;
};

#endif // __APIENDPOINTS_H__