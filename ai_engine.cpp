#include "../include/ai_engine.h"
#include "../include/onnx_engine.h"

std::vector<Diagnosis> run_ai_engine(
    const SystemMetrics& m,
    const RulesConfig& r
) {
    std::vector<Diagnosis> results;

    /* -------- RULE-BASED AI (Option A) -------- */

    if (m.cpu_temp > r.cpu_temp_critical) {
        results.push_back({
            "CPU Overheating",
            "CPU temperature exceeds configured threshold",
            "Clean fan, replace thermal paste, improve airflow"
        });
    }

    if (m.cpu_usage > r.cpu_usage_high && m.cpu_temp <= r.cpu_temp_critical) {
        results.push_back({
            "High CPU Usage",
            "CPU usage above configured limit",
            "Check background processes using top or htop"
        });
    }

    if (m.ram_usage > r.ram_usage_high) {
        results.push_back({
            "High Memory Usage",
            "RAM usage above configured limit",
            "Restart heavy apps or investigate memory leaks"
        });
    }

    if (m.disk_usage > r.disk_usage_critical) {
        results.push_back({
            "Critical Disk Space",
            "Disk usage exceeds critical threshold",
            "Free disk space immediately to avoid instability"
        });
    } else if (m.disk_usage > r.disk_usage_high) {
        results.push_back({
            "High Disk Usage",
            "Disk usage above configured limit",
            "Clean logs, remove unused files, or expand disk"
        });
    }

    if (m.load_1min > r.load_avg_high) {
        results.push_back({
            "High System Load",
            "Load average above configured limit",
            "Reduce running services or investigate load spikes"
        });
    }

    if (m.uptime_hours > r.uptime_reboot_hours) {
        results.push_back({
            "Long System Uptime",
            "System uptime exceeds configured reboot interval",
            "Consider rebooting to apply updates and clear resources"
        });
    }

    if (results.empty()) {
        results.push_back({
            "System Healthy",
            "All metrics within configured limits",
            "No action required"
        });
    }

    /* -------- ONNX ML ADVISORY (Option B) -------- */

int ml_result = run_onnx_inference(m);

switch (ml_result) {
    case 1:
        results.push_back({
            "ML Advisory: High Load Pattern",
            "ML model detected sustained system load",
            "Investigate services and reduce concurrent workloads"
        });
        break;

    case 2:
        results.push_back({
            "ML Advisory: Overheating Risk",
            "ML model predicts overheating trend",
            "Improve cooling and monitor temperatures"
        });
        break;

    case 3:
        results.push_back({
            "ML Advisory: Disk Pressure",
            "ML model predicts disk-related performance issues",
            "Clean disk space and monitor IO activity"
        });
        break;

    default:
        break;
}


    return results;
}

