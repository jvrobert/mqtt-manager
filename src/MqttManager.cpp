#include "MqttManager.h"

static const char *TAG = "MqttManager";

MqttManager *MqttManager::s_instance = nullptr;

MqttManager* MqttManager::GetInstance()
{
    if (s_instance == nullptr)
    {
        s_instance = new MqttManager();
    }
    return s_instance;
}

MqttManager::MqttManager()
{
}

void MqttManager::Start()
{
    GetInstance()->Initialize();
}

void MqttManager::Initialize()
{
    esp_mqtt_client_config_t mqtt_cfg = {
        .uri = CONFIG_MQTT_MANAGER_SERVER,
        .username = CONFIG_MQTT_MANAGER_LOGIN,
        .password = CONFIG_MQTT_MANAGER_PASSWORD
        };
    m_mqttClient = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_register_event(m_mqttClient, MQTT_EVENT_ANY, MqttManager::onMqttEvent, NULL);
    esp_mqtt_client_start(m_mqttClient);
    // std::string me = "beaconscanner/" + m_hostname;
    // int rc = esp_mqtt_client_publish(m_mqttClient, me.c_str(), "{\"starting\": \"true\"}", 0, 0, 0);
    // if (rc < 0)
    // {
    //     ESP_LOGE(TAG, "MQTT failed to announce, rc=%d", rc);
    // }
}

void MqttManager::onMqttEvent(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data)
{
    esp_mqtt_event_handle_t event = static_cast<esp_mqtt_event_handle_t>(event_data);
    //esp_mqtt_client_handle_t client = event->client;
    //int msg_id;
    //auto inst = GetInstance();
    std::string topic(event->topic, event->topic_len);
    switch ((esp_mqtt_event_id_t)event_id)
    {
    case MQTT_EVENT_CONNECTED:
        ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
        // msg_id = esp_mqtt_client_subscribe(client, me.c_str(), 0);
        // msg_id = esp_mqtt_client_subscribe(client, "beaconscanner/update_fw", 0);
        // ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);
        break;
    case MQTT_EVENT_DATA:
        // if (topic == me || topic == "beaconscanner/update_fw")
        // {
        //     inst->UpdateFirmware(std::string(event->data, event->data_len));
        // }
        break;
    default:
        break;
    }
}

bool MqttManager::Publish(std::string topic, std::string msg)
{
    int rc = esp_mqtt_client_publish(m_mqttClient, topic.c_str(), msg.c_str(), 0, 0, 0);
    if (rc < 0)
    {
        ESP_LOGE(TAG, "MQTT failed to publish to %s, rc=%d", topic.c_str(), rc);
        return false;
    }
    return true;
}