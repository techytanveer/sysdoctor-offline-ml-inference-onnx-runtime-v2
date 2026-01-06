#ifndef SYSTEM_METRICS_H
#define SYSTEM_METRICS_H

struct SystemMetrics {
    double cpu_usage;
    double ram_usage;
    double cpu_temp;

    double load_1min;
    double disk_usage;
    double uptime_hours;
};

SystemMetrics collect_metrics();

#endif

