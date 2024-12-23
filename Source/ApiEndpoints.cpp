#include "ApiEndpoints.hpp"

ApiEndpoints::ApiEndpoints()
{
    // ----------------------------------------------------------------
    // Device Control(Standard Instruction Set) 
    // ----------------------------------------------------------------

    // Get the specifications and properties of the device	GET:/v1.0/iot-03/devices/{device_id}/specification
    this->addEndpoint(
        "Device Control(Standard Instruction Set)",
        "Get the specifications and properties of the device",
        "GET:/v1.0/iot-03/devices/{device_id}/specification"
    );

    // Get the instruction set of the device	GET:/v1.0/iot-03/devices/{device_id}/functions
    this->addEndpoint(
        "Device Control(Standard Instruction Set)",
        "Get the instruction set of the device",
        "GET:/v1.0/iot-03/devices/{device_id}/functions"
    );

    // Get the instruction set of the category	GET:/v1.0/iot-03/categories/{category}/functions
    this->addEndpoint(
        "Device Control(Standard Instruction Set)",
        "Get the instruction set of the category",
        "GET:/v1.0/iot-03/categories/{category}/functions"
    );

    // Send commands    POST:/v1.0/iot-03/devices/{device_id}/commands
    this->addEndpoint(
        "Device Control(Standard Instruction Set)",
        "Send commands",
        "POST:/v1.0/iot-03/devices/{device_id}/commands"
    );

    // Get Category List	GET:/v1.0/iot-03/device-categories
    this->addEndpoint(
        "Device Control(Standard Instruction Set)",
        "Get Category List",
        "GET:/v1.0/iot-03/device-categories"
    );

    // Get the status of a single device	GET:/v1.0/iot-03/devices/{device_id}/status
    this->addEndpoint(
        "Device Control(Standard Instruction Set)",
        "Get the status of a single device",
        "GET:/v1.0/iot-03/devices/{device_id}/status"
    );

    // Get the latest status of multiple devices	GET:/v1.0/iot-03/devices/status
    this->addEndpoint(
        "Device Control(Standard Instruction Set)",
        "Get the latest status of multiple devices",
        "GET:/v1.0/iot-03/devices/status"
    );

    // Get Status Set	GET:/v1.0/iot-03/categories/{category}/status
    this->addEndpoint(
        "Device Control(Standard Instruction Set)",
        "Get Status Set",
        "GET:/v1.0/iot-03/categories/{category}/status"
    );
}

ApiEndpoints::~ApiEndpoints() {}