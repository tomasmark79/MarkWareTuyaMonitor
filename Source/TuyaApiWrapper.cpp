#include "TuyaApiWrapper.hpp"

#include <nlohmann/json.hpp>
#include <openssl/hmac.h>
using json = nlohmann::json;

#include <fstream>
#include <iostream>
#include <memory>

#define CREDENTIALS_FILE "/home/tomas/.tuya_credentials.txt"

#define DEBUG bool(true)

TuyaApiWrapper::TuyaApiWrapper()
{
    if (getCredentials(clientId, clientSecret))
        std::cerr << "Error: Could not get credentials" << std::endl;
}

TuyaApiWrapper::~TuyaApiWrapper() {}

std::string TuyaApiWrapper::getDataCenterUrl(const std::string &dataCenterName)
{
    auto it = dataCenters.find(dataCenterName);
    if (it != dataCenters.end())
    {
        return it->second;
    }
    else
    {
        return "Data center not found";
    }
}

std::string TuyaApiWrapper::hmac_sha256(const std::string &key, const std::string &data)
{
    unsigned char *digest;
    digest = HMAC(
        EVP_sha256(),
        key.c_str(),
        key.length(),
        (unsigned char *)data.c_str(),
        data.length(),
        NULL,
        NULL
    );
    char mdString[65];
    for (int i = 0; i < 32; i++)
        sprintf(&mdString[i * 2], "%02x", (unsigned int)digest[i]);
    return std::string(mdString);
}

size_t TuyaApiWrapper::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}

std::string TuyaApiWrapper::getTimestamp()
{
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

    std::cout << "Timestamp:\t" << milliseconds << std::endl;
    return std::to_string(milliseconds);
}

int TuyaApiWrapper::getCredentials(std::string &clientId, std::string &clientSecret)
{
    std::ifstream file(CREDENTIALS_FILE);

    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file home_profile.txt" << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(file, line))
    {
        if (line.find("clientId") != std::string::npos)
        {
            clientId = line.substr(line.find(":") + 1);
        }
        else if (line.find("clientSecret") != std::string::npos)
        {
            clientSecret = line.substr(line.find(":") + 1);
        }
    }

    file.close();

    if (clientId.empty() || clientSecret.empty())
    {
        std::cerr << "Error: Could not find clientId or clientSecret in home_profile.txt"
                  << std::endl;
        return 1;
    }

    return 0;
}

/// @brief request access token
/// @return 0 if success
int TuyaApiWrapper::getAccessTokenSimpleMode()
{
    std::cout << std::endl << "--- Getting access token ..." << std::endl;

    // URL POSTFIX
    const std::string urlPostfix = "/v1.0/token?grant_type=1";

    // TIMESTAMP
    const std::string timestamp = getTimestamp().c_str();

    // STRING TO SIGN
    const std::string stringToSign = "GET\n" + emptyBodyEncoded + "\n\n" + urlPostfix;
    std::cout << "stringToSign:\t\t" << stringToSign << std::endl;

    // NONCE OPTIONAL
    const std::string nonceOptional = "";

    // STR
    const std::string str = clientId + timestamp + nonceOptional + stringToSign;
    std::cout << "str:\t\t" << str << std::endl;

    // ACCESS TOKEN SIGN
    std::string requestTokenSigned = hmac_sha256(clientSecret, str);
    std::transform(
        requestTokenSigned.begin(), requestTokenSigned.end(), requestTokenSigned.begin(), ::toupper
    );
    std::cout << "requestTokenSigned:\t" << requestTokenSigned << std::endl;

    // CURL
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    {
        std::unique_ptr<curl_slist, decltype(&curl_slist_free_all)> headers(
            nullptr, &curl_slist_free_all
        );

        headers.reset(curl_slist_append(headers.release(), "sign_method: HMAC-SHA256"));
        headers.reset(curl_slist_append(headers.release(), ("client_id: " + clientId).c_str()));
        headers.reset(curl_slist_append(headers.release(), ("t: " + timestamp).c_str()));
        headers.reset(curl_slist_append(headers.release(), "mode: cors"));
        headers.reset(curl_slist_append(headers.release(), "Content-Type: application/json"));
        headers.reset(curl_slist_append(headers.release(), ("sign: " + requestTokenSigned).c_str())
        );

        curl_easy_setopt(
            curl, CURLOPT_URL, (getDataCenterUrl("Central Europe Data Center") + urlPostfix).c_str()
        );
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers.get());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        // curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            return 1;
        }
        if (DEBUG)
            std::cout << "received:\t" << this->readBuffer << std::endl;

        // PARSE RECEIVED JSON
        json j = json::parse(readBuffer);
        if (j["success"] != true)
        {
            std::cerr << "Error: " << j["msg"] << std::endl;
            return 1;
        }
        this->accessToken = j["result"]["access_token"];
        this->refreshToken = j["result"]["refresh_token"];
        this->expiredIn = j["result"]["expire_time"];

        if (DEBUG)
        {
            std::cout << "received Access token:\t" << this->accessToken << std::endl;
            std::cout << "received Refresh token:\t" << this->refreshToken << std::endl;
        }

        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    /* CURL END */

    return 0;
}

int TuyaApiWrapper::deviceControll(
    std::string &deviceIds, std::string action, std::string &deviceControllResponse
)
{
    std::cout << std::endl << "--- Getting device status ..." << std::endl;

    // URL POSTFIX
    const std::string urlPostfix = "/v1.0/iot-03/devices/status?device_ids=" + deviceIds;

    // TIMESTAMP
    const std::string timestamp = getTimestamp();

    // STRING TO SIGN
    const std::string stringToSign = "GET\n" + emptyBodyEncoded + "\n\n" + urlPostfix;
    std::cout << "stringToSign:\t\t" << stringToSign << std::endl;

    // NONCE OPTIONAL
    const std::string nonceOptional = "";

    // STR
    const std::string str = clientId + accessToken + timestamp + nonceOptional + stringToSign;

    // GET DEVICE STATUS SIGN
    std::string requestGetDeviceSign = hmac_sha256(clientSecret, str);
    std::transform(
        requestGetDeviceSign.begin(),
        requestGetDeviceSign.end(),
        requestGetDeviceSign.begin(),
        ::toupper
    );
    std::cout << "requestGetDeviceSign:\t" << requestGetDeviceSign << std::endl;

    /* CURL */
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl)
    {
        std::unique_ptr<curl_slist, decltype(&curl_slist_free_all)> headers(
            nullptr, &curl_slist_free_all
        );
        headers.reset(curl_slist_append(headers.release(), "sign_method: HMAC-SHA256"));
        headers.reset(curl_slist_append(headers.release(), ("client_id: " + clientId).c_str()));
        headers.reset(curl_slist_append(headers.release(), ("t: " + timestamp).c_str()));
        headers.reset(curl_slist_append(headers.release(), "mode: cors"));
        headers.reset(curl_slist_append(headers.release(), "Content-Type: application/json"));
        headers.reset(
            curl_slist_append(headers.release(), ("sign: " + requestGetDeviceSign).c_str())
        );
        headers.reset(curl_slist_append(headers.release(), ("access_token: " + accessToken).c_str())
        );

        curl_easy_setopt(
            curl, CURLOPT_URL, (getDataCenterUrl("Central Europe Data Center") + urlPostfix).c_str()
        );
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers.get());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        // curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        res = curl_easy_perform(curl); // Perform the request, res will get the return code

        if (res != CURLE_OK)
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;

        deviceControllResponse = this->readBuffer;

        if (DEBUG)
            std::cout << "getDeviceStatusResponse:\t" << this->readBuffer << std::endl;

        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    /* CURL END */

    return 0;
}

/// @brief Will parse JSON results objects and print them to stdout
/// @param json_buffer 
/// @return 0 if success
int TuyaApiWrapper::parseJsonResults(const std::string &json_buffer)
{
    size_t start = 0;

    while (start < json_buffer.size()) // find all JSON blocks
    {
        try
        {
            size_t      end = json_buffer.find("}{", start);
            std::string json_block = (end == std::string::npos)
                ? json_buffer.substr(start) // last block
                : json_buffer.substr(start, end - start + 1);

            nlohmann::json json_obj = nlohmann::json::parse(json_block);

            if (json_obj.contains("result"))
            {
                std::cout << json_obj["result"].dump(4) << std::endl; // pretty print
            }

            start = (end == std::string::npos) ? json_buffer.size() : end + 1;
        }
        catch (const nlohmann::json::parse_error &e)
        {
            std::cerr << "Chyba parsování JSON: " << e.what() << std::endl;
            break;
        }
    }

    return 0;
}

int TuyaApiWrapper::processAPIRequest(
    std::string  category,
    std::string  action,
    std::string &deviceIds,
    std::string &processAPIRequestResponse
)
{
    std::cout << std::endl << "--- processAPIRequest ..." << std::endl;

    std::string urlPostfix = apiEndpoints.apiData[category].at(0).url;

    // PLACEHOLDERS
    size_t pos;

    pos = urlPostfix.find("{device_id}");
    if (pos != std::string::npos)
        urlPostfix.replace(pos, std::string("{device_id}").length(), deviceIds);

    pos = urlPostfix.find("{category}");
    if (pos != std::string::npos)
        urlPostfix.replace(pos, std::string("{category}").length(), "");

    pos = urlPostfix.find("GET:");
    if (pos != std::string::npos)
        urlPostfix.replace(pos, std::string("GET:").length(), "");

    // TIMESTAMP
    const std::string timestamp = getTimestamp();

    // STRING TO SIGN
    const std::string stringToSign = "GET\n" + emptyBodyEncoded + "\n\n" + urlPostfix;
    std::cout << "stringToSign:\t\t" << stringToSign << std::endl;

    // NONCE OPTIONAL
    const std::string nonceOptional = "";

    // STR
    const std::string str = clientId + accessToken + timestamp + nonceOptional + stringToSign;

    // GET DEVICE STATUS SIGN
    std::string requestGetDeviceSign = hmac_sha256(clientSecret, str);
    std::transform(
        requestGetDeviceSign.begin(),
        requestGetDeviceSign.end(),
        requestGetDeviceSign.begin(),
        ::toupper
    );
    std::cout << "requestGetDeviceSign:\t" << requestGetDeviceSign << std::endl;

    /* CURL */
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (curl)
    {
        std::unique_ptr<curl_slist, decltype(&curl_slist_free_all)> headers(
            nullptr, &curl_slist_free_all
        );
        headers.reset(curl_slist_append(headers.release(), "sign_method: HMAC-SHA256"));
        headers.reset(curl_slist_append(headers.release(), ("client_id: " + clientId).c_str()));
        headers.reset(curl_slist_append(headers.release(), ("t: " + timestamp).c_str()));
        headers.reset(curl_slist_append(headers.release(), "mode: cors"));
        headers.reset(curl_slist_append(headers.release(), "Content-Type: application/json"));
        headers.reset(
            curl_slist_append(headers.release(), ("sign: " + requestGetDeviceSign).c_str())
        );
        headers.reset(curl_slist_append(headers.release(), ("access_token: " + accessToken).c_str())
        );

        curl_easy_setopt(
            curl, CURLOPT_URL, (getDataCenterUrl("Central Europe Data Center") + urlPostfix).c_str()
        );
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers.get());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        // curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        res = curl_easy_perform(curl); // Perform the request, res will get the return code

        if (res != CURLE_OK)
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;

        processAPIRequestResponse = this->readBuffer;

        if (DEBUG)
            parseJsonResults(this->readBuffer);

        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    /* CURL END */

    return 0;
}

