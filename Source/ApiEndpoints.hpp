#ifndef __APIENDPOINTS_H__
#define __APIENDPOINTS_H__

#include <iostream>
#include <map>
#include <string>
#include <vector>

class ApiEndpoints
{
  public:
    ApiEndpoints();
    ~ApiEndpoints();

  private:
    struct ApiOperation
    {
        std::string name;
        std::string url;
    };

    using ApiCategory = std::map<std::string, std::vector<ApiOperation>>;

  public:
    ApiCategory apiData;
};

#endif // __APIENDPOINTS_H__