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

    // Devices to reach comma separated
    std::string deviceId = "bfaef501e3f539ca8fvmou";

    // Start to talk with Tuya API

    // Handshake
    if (tuyaApiWrapper.getAccessTokenSimpleMode() == 1)
    {
        std::cerr << "Error: Could not get access token" << std::endl;
        return;
    }

    // Go through the list of api endpoints
    std::string deviceControllResponse;
    if (tuyaApiWrapper.deviceControll(deviceId, deviceControllResponse) == 0)
        // std::cout << "Device status: " << deviceControllResponse << std::endl;
        ;
    else std::cerr << "Error: Could not get device status" << std::endl;
}
