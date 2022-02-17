#pragma once

#include "mqtt_client.h"
#include "sdkconfig.h"
#undef LOG_LOCAL_LEVEL
#define LOG_LOCAL_LEVEL ESP_LOG_INFO
#include <esp_log.h>

#include <string>


class MqttManager
{

public:
    static MqttManager *GetInstance();
    static void Start();
    bool Publish(std::string topic, std::string msg);
protected:
    static MqttManager* s_instance;
    static void onMqttEvent(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data);
    void Initialize();
    MqttManager();
    esp_mqtt_client_handle_t m_mqttClient;
};