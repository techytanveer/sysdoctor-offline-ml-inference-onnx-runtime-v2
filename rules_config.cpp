#include "../include/rules_config.h"
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

RulesConfig load_rules_config(const char* path) {
    std::ifstream file(path);
    json j;
    file >> j;

    RulesConfig cfg{};
    cfg.cpu_temp_critical     = j.value("cpu_temp_critical", 85.0);
    cfg.cpu_usage_high        = j.value("cpu_usage_high", 80.0);
    cfg.ram_usage_high        = j.value("ram_usage_high", 85.0);
    cfg.disk_usage_high       = j.value("disk_usage_high", 80.0);
    cfg.disk_usage_critical   = j.value("disk_usage_critical", 95.0);
    cfg.load_avg_high         = j.value("load_avg_high", 4.0);
    cfg.uptime_reboot_hours   = j.value("uptime_reboot_hours", 720.0);

    return cfg;
}

