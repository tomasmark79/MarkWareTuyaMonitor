#include "MarkWareTuya/MarkWareTuya.hpp"
#include <markwaretuya/version.h>

#include <EmojiTools/EmojiTools.hpp>
#include <TuyaApiWrapper.hpp>

#include <iostream>

MarkWareTuya::MarkWareTuya()
{
    std::cout << "--- MarkWareTuya v." << MARKWARETUYA_VERSION << " instantiated ---" << std::endl;

    // Tuya API Wrapper by MarkWare (MIT License)
    TuyaApiWrapper tuyaApiWrapper;

    // Devices to reach comma separated
    std::string deviceId = "bfaef501e3f539ca8fvmou";

    // Device status as a json
    std::string deviceStatus;

    // Start to tal with Tuya API
    if (tuyaApiWrapper.getAccessToken() == 0)
        if (tuyaApiWrapper.getDeviceStatus(deviceId, deviceStatus) == 0)
            std::cout << "Device status: " << deviceStatus << std::endl;
        else
            std::cerr << "Error: Could not get device status" << std::endl;
}

MarkWareTuya::~MarkWareTuya()
{
    std::cout << "--- MarkWareTuya uninstantiated ---" << std::endl;
}
