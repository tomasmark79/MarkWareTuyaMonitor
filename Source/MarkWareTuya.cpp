#include "MarkWareTuya/MarkWareTuya.hpp"
#include <markwaretuya/version.h>

#include <EmojiTools/EmojiTools.hpp>

#include <TuyaApiWrapper.hpp>

#include <iostream>

MarkWareTuya::~MarkWareTuya()
{
    std::cout << "--- MarkWareTuya uninstantiated ---" << std::endl;
}

MarkWareTuya::MarkWareTuya()
{
    std::cout << "--- MarkWareTuya v." << MARKWARETUYA_VERSION << " instantiated ---" << std::endl;

    // Tuya API Wrapper by MarkWare (MIT License)
    TuyaApiWrapper tuyaApiWrapper;

    std::string deviceIds = "bfaef501e3f539ca8fvmou";
    std::string deviceStatusResponse;

    // Start to talk with Tuya API

    if (tuyaApiWrapper.getAccessTokenSimpleMode() == 1)
    {
        std::cerr << "Error: Could not get access token" << std::endl;
        return;
    }

    if (tuyaApiWrapper.processAPIRequest(
            "Device Control", "Get the status of a single device", deviceIds, deviceStatusResponse
        ) == 1)
    {
        std::cerr << "Error: processAPIRequest" << std::endl;
        return;
    }
}
