#ifndef __TUYAAPIWRAPPER_H__
#define __TUYAAPIWRAPPER_H__

#include <curl/curl.h>
#include <map>
#include <string>
class TuyaApiWrapper
{

  public:
    TuyaApiWrapper();
    ~TuyaApiWrapper();

    int getAccessTokenSimpleMode();
    int getDeviceStatus(std::string &deviceIds, std::string &deviceStatus);

  private:
    std::map<std::string, std::string> dataCenters = {
        {          "China Data Center",      "https://openapi.tuyacn.com"},
        {"Western America Data Center",      "https://openapi.tuyaus.com"},
        {"Eastern America Data Center", "https://openapi-ueaz.tuyaus.com"},
        { "Central Europe Data Center",      "https://openapi.tuyaeu.com"},
        { "Western Europe Data Center", "https://openapi-weaz.tuyaeu.com"},
        {          "India Data Center",      "https://openapi.tuyain.com"}
    };

    std::string accessToken;

    std::string refreshToken; // oauth2.0
    int         expiredIn;    // oauth2.0

    std::string   getDataCenterUrl(const std::string &dataCenterName);
    std::string   hmac_sha256(const std::string &key, const std::string &data);
    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
    int           getCredentials(std::string &clientId, std::string &clientSecret);
    std::string   getTimestamp();

    CURL       *curl;
    CURLcode    res;
    std::string readBuffer;

    const std::string emptyBodyEncoded =
        "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855";

    std::string clientId;
    std::string clientSecret;
};

#endif // __TUYAAPIWRAPPER_H__