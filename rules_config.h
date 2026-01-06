#ifndef RULES_CONFIG_H
#define RULES_CONFIG_H

struct RulesConfig {
    double cpu_temp_critical;
    double cpu_usage_high;
    double ram_usage_high;

    double disk_usage_high;
    double disk_usage_critical;

    double load_avg_high;
    double uptime_reboot_hours;
};

RulesConfig load_rules_config(const char* path);

#endif

