#include "../include/system_metrics.h"
#include <fstream>
#include <sys/statvfs.h>
#include <string>
#include <thread>
#include <chrono>

/* Existing functions unchanged */
static double get_cpu_usage();
static double get_ram_usage();
static double get_cpu_temp();

/* New metrics */

static double get_load_average() {
    std::ifstream file("/proc/loadavg");
    double load;
    file >> load;
    return load;
}

static double get_disk_usage() {
    struct statvfs fs;
    statvfs("/", &fs);

    double total = fs.f_blocks * fs.f_frsize;
    double available = fs.f_bavail * fs.f_frsize;

    return 100.0 * (1.0 - available / total);
}

static double get_uptime_hours() {
    std::ifstream file("/proc/uptime");
    double seconds;
    file >> seconds;
    return seconds / 3600.0;
}

/* ---------- EXISTING IMPLEMENTATIONS ---------- */

static double get_cpu_usage() {
    long long user, nice, system, idle;
    std::ifstream file("/proc/stat");
    std::string cpu;

    file >> cpu >> user >> nice >> system >> idle;
    long long idle1 = idle;
    long long total1 = user + nice + system + idle;

    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    file.clear();
    file.seekg(0);
    file >> cpu >> user >> nice >> system >> idle;
    long long idle2 = idle;
    long long total2 = user + nice + system + idle;

    return 100.0 * (1.0 - (double)(idle2 - idle1) / (double)(total2 - total1));
}

static double get_ram_usage() {
    std::ifstream file("/proc/meminfo");
    std::string key;
    long long total = 0, available = 0;

    while (file >> key) {
        if (key == "MemTotal:") file >> total;
        else if (key == "MemAvailable:") {
            file >> available;
            break;
        }
    }
    return 100.0 * (1.0 - (double)available / (double)total);
}

static double get_cpu_temp() {
    std::ifstream file("/sys/class/thermal/thermal_zone0/temp");
    double temp = 0;
    file >> temp;
    return temp / 1000.0;
}

SystemMetrics collect_metrics() {
    return {
        get_cpu_usage(),
        get_ram_usage(),
        get_cpu_temp(),
        get_load_average(),
        get_disk_usage(),
        get_uptime_hours()
    };
}

