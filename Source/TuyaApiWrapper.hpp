#ifndef __TUYAAPIWRAPPER_H__
#define __TUYAAPIWRAPPER_H__

#include <curl/curl.h>
#include <string>

class TuyaApiWrapper
{
  public:
    TuyaApiWrapper();
    ~TuyaApiWrapper();

    int getAccessToken();
    int getDeviceStatus(std::string &deviceIds, std::string &deviceStatus);

  private:
    std::string accessToken;
    std::string refreshToken;

    std::string   hmac_sha256(const std::string &key, const std::string &data);
    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
    int           getCredentials(std::string &clientId, std::string &clientSecret);
    std::string   getTimestamp();

    CURL       *curl;
    CURLcode    res;
    std::string readBuffer;

    const std::string baseUrl = "https://openapi.tuyaeu.com";
    const std::string emptyBodyEncoded =
        "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855";

    std::string clientId;
    std::string clientSecret;
};

#endif // __TUYAAPIWRAPPER_H__