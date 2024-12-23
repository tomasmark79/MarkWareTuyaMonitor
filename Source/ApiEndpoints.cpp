#include "ApiEndpoints.hpp"

// https://developer.tuya.com/en/docs/cloud/device-connection-service?id=Kb0b8geg6o761

ApiEndpoints::ApiEndpoints()
{
    // --- IoT Core API Start ---

    apiData["Space Management"] = {
        {                   "Delete Space",       "DELETE:/v2.0/cloud/space/{space_id}"},
        {       "Query Resources in Space", "GET:/v2.0/cloud/space/{space_id}/resource"},
        {                   "Create Space",           "POST:/v2.0/cloud/space/creation"},
        {                    "Query Space",          "GET:/v2.0/cloud/space/{space_id}"},
        {               "Query Space List",               "GET:/v2.0/cloud/space/child"},
        {       "Modify Space Information",          "PUT:/v2.0/cloud/space/{space_id}"},
        {"Query Parent-Child Relationship",            "GET:/v2.0/cloud/space/relation"}
    };

    apiData["Device Management"] = {
        {         "Get Status Reporting Log",                 "GET:/v2.0/cloud/thing/{device_id}/report-logs"},
        {              "Get Update Progress", "GET:/v2.0/cloud/thing/{device_id}/firmware/{channel}/progress"},
        {     "Query Device Details in Bulk",                                   "GET:/v2.0/cloud/thing/batch"},
        {                    "Delete Device",                          "DELETE:/v2.0/cloud/thing/{device_id}"},
        {           "Get Update Information",                    "GET:/v2.0/cloud/thing/{device_id}/firmware"},
        {             "Query Device Details",                             "GET:/v2.0/cloud/thing/{device_id}"},
        {          "Confirm Start of Update",         "POST:/v2.0/cloud/thing/{device_id}/firmware/{channel}"},
        {                 "Get Device State",                       "GET:/v2.0/cloud/thing/{device_id}/state"},
        {                "Get Operation Log",                        "GET:/v2.0/cloud/thing/{device_id}/logs"},
        {          "Modify Basic Properties",                  "POST:/v2.0/cloud/thing/{device_id}/attribute"},
        {           "Freeze/Unfreeze Device",                     "POST:/v2.0/cloud/thing/{device_id}/freeze"},
        {                  "Transfer Device",                   "POST:/v2.0/cloud/thing/{device_id}/transfer"},
        {         "Restore Factory Defaults",                      "POST:/v2.0/cloud/thing/{device_id}/reset"},
        {           "Query Devices in Space",                            "GET:/v2.0/cloud/thing/space/device"},
        {         "Query Devices in Project",                                  "GET:/v2.0/cloud/thing/device"},
        {"Send Signal Detection Instruction",                 "POST:/v2.0/cloud/thing/signal/detection/issue"},
        {            "Query Signal Strength",        "GET:/v2.0/cloud/thing/{device_id}/{device_type}/signal"},
        {         "Get Status Reporting Log",                 "GET:/v2.1/cloud/thing/{device_id}/report-logs"}
    };

    apiData["Device Control"] = {
        {            "Send Actions",            "POST:/v2.0/cloud/thing/{device_id}/shadow/actions"},
        {        "Query Properties",          "GET:/v2.0/cloud/thing/{device_id}/shadow/properties"},
        {       "Modify Properties",         "POST:/v2.0/cloud/thing/{device_id}/shadow/properties"},
        {"Query Desired Properties",  "GET:/v2.0/cloud/thing/{device_id}/shadow/properties/desired"},
        {           "Send Property",   "POST:/v2.0/cloud/thing/{device_id}/shadow/properties/issue"},
        {    "Set Desired Property", "POST:/v2.0/cloud/thing/{device_id}/shadow/properties/desired"},
        { "Query Things Data Model",                      "GET:/v2.0/cloud/thing/{device_id}/model"}
    };

    apiData["Scene Linkage Rules"] = {
        { "Get Linkage Rule Details",                  "GET:/v2.0/cloud/scene/rule/{rule_id}"},
        {      "Query Linkage Rules",                            "GET:/v2.0/cloud/scene/rule"},
        {      "Delete Linkage Rule",                         "DELETE:/v2.0/cloud/scene/rule"},
        {       "Trigger Tap-to-Run", "POST:/v2.0/cloud/scene/rule/{rule_id}/actions/trigger"},
        {      "Modify Linkage Rule",                  "PUT:/v2.0/cloud/scene/rule/{rule_id}"},
        {"Enable/Disable Automation",                      "PUT:/v2.0/cloud/scene/rule/state"},
        {         "Add Linkage Rule",                           "POST:/v2.0/cloud/scene/rule"}
    };

    apiData["Device Control"] = {
        {"Get the specifications and properties of the device",
         "GET:/v1.0/iot-03/devices/{device_id}/specification"                                                   },
        {              "Get the instruction set of the device", "GET:/v1.0/iot-03/devices/{device_id}/functions"},
        {            "Get the instruction set of the category",
         "GET:/v1.0/iot-03/categories/{category}/functions"                                                     },
        {                                      "Send commands", "POST:/v1.0/iot-03/devices/{device_id}/commands"},
        {                                  "Get Category List",             "GET:/v1.0/iot-03/device-categories"},
        {                  "Get the status of a single device",    "GET:/v1.0/iot-03/devices/{device_id}/status"},
        {          "Get the latest status of multiple devices",                "GET:/v1.0/iot-03/devices/status"},
        {                                     "Get Status Set",  "GET:/v1.0/iot-03/categories/{category}/status"}
    };

    apiData["Device Group"] = {
        {   "Query Group Properties",     "GET:/v2.1/cloud/thing/group/{group_id}/properties"},
        {      "Get Groups in Space",                           "GET:/v2.1/cloud/thing/group"},
        {              "Add Devices",        "PUT:/v2.1/cloud/thing/group/{group_id}/devices"},
        {             "Create Group",                          "POST:/v2.1/cloud/thing/group"},
        {         "Get Device Group",        "GET:/v2.1/cloud/thing/group/device/{device_id}"},
        {"Query Group Task Progress", "GET:/v2.1/cloud/thing/group/task/{group_id}/{task_id}"},
        {       "Query Group Status",     "GET:/v2.1/cloud/thing/group/{group_id}/status-set"},
        {           "Remove Devices",     "DELETE:/v2.1/cloud/thing/group/{group_id}/devices"},
        {             "Delete Group",             "DELETE:/v2.1/cloud/thing/group/{group_id}"},
        {      "Query Group Devices",        "GET:/v2.1/cloud/thing/group/{group_id}/devices"},
        { "Modify Group Information",                "PUT:/v2.1/cloud/thing/group/{group_id}"},
        {    "Send Group Properties",    "POST:/v2.1/cloud/thing/group/{group_id}/properties"},
        {      "Query Group Details",                "GET:/v2.1/cloud/thing/group/{group_id}"}
    };

    // --- Advanced Device Servicess ---

    apiData["Geographical Fence"] = {
        {                        "Query Geofence Alert",              "GET:/v2.0/iot-01/fences/warn/list"},
        {                      "Get Device Track Point",                 "GET:/v2.0/iot-01/tracks/detail"},
        {                    "Get Device Track Segment",               "GET:/v2.0/iot-01/tracks/segments"},
        {                     "Add Devices in Geofence",     "POST:/v2.0/iot-01/fences/{fence_id}/entity"},
        {                   "Create Polygonal Geofence",               "POST:/v2.0/iot-01/fences/polygon"},
        {                   "Modify Polygonal Geofence",     "PUT:/v2.0/iot-01/fences/polygon/{fence_id}"},
        {                   "Query Objects in Geofence",      "GET:/v2.0/iot-01/fences/{fence_id}/entity"},
        {                         "Query All Geofences",                   "GET:/v2.0/iot-01/fences/list"},
        {                    "Create Circular Geofence",                "POST:/v2.0/iot-01/fences/circle"},
        {                  "Enable or Disable Geofence",        "PUT:/v2.0/iot-01/fences/{fence_id}/open"},
        {            "Query Multiple Private Geofences",          "GET:/v2.0/iot-01/fences/private/batch"},
        {             "Save Circular Private Geofences",  "POST:/v2.0/iot-01/fences/circle/private/batch"},
        {                    "Modify Circular Geofence",      "PUT:/v2.0/iot-01/fences/circle/{fence_id}"},
        {               "Query Geofence by Geofence ID",                  "GET:/v2.0/iot-01/fences/batch"},
        {            "Save Polygonal Private Geofences", "POST:/v2.0/iot-01/fences/polygon/private/batch"},
        {"Query Real-time Location of Multiple Devices",               "GET:/v2.0/iot-01/tracks/location"}
    };

    apiData["Device Timer"] = {
        {"Enable/Disable Scheduled Task",    "PUT:/v2.0/cloud/timer/device/{device_id}/state"},
        {         "Query Scheduled Task",          "GET:/v2.0/cloud/timer/device/{device_id}"},
        {           "Add Scheduled Task",         "POST:/v2.0/cloud/timer/device/{device_id}"},
        {        "Modify Scheduled Task",          "PUT:/v2.0/cloud/timer/device/{device_id}"},
        {  "Bulk Delete Scheduled Tasks", "DELETE:/v2.0/cloud/timer/device/{device_id}/batch"},
        {        "Clear Scheduled Tasks",       "DELETE:/v2.0/cloud/timer/device/{device_id}"}
    };

    apiData["IoT Video Live Stream"] = {
        {"Get WebRTC Configurations of the Device",           "GET:/v1.0/devices/{device_id}/webrtc-configs"},
        {             "Get Live Streaming Address", "POST:/v1.0/devices/{device_id}/stream/actions/allocate"}
    };

    apiData["Video Cloud Storage"] = {
        { "Get Resources of Video Clip",
         "GET:/v1.0/users/{uid}/devices/{device_id}/storage/stream/hls"                               },
        {"Get Start Time of Video Clip",
         "GET:/v1.0/users/{uid}/devices/{device_id}/storage/stream/timeline"                          },
        {       "Get Key of Video File", "GET:/v1.0/users/{uid}/devices/{device_id}/storage/stream/ke"}
    };

    // Debugging
    // for (const auto &category : apiData)
    // {
    //     std::cout << "Category: " << category.first << '\n';
    //     for (const auto &operation : category.second)
    //     {
    //         std::cout << "  API Name: " << operation.name << '\n';
    //         std::cout << "  URL: " << operation.url << '\n';
    //     }
    // }
}

ApiEndpoints::~ApiEndpoints() {}