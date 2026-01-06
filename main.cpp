#include <iostream>
#include "../include/system_metrics.h"
#include "../include/ai_engine.h"
#include "../include/rules_config.h"

int main() {
    std::cout << "🧠 AI System Doctor (Configurable Rules)\n";
    std::cout << "=======================================\n";

    SystemMetrics metrics = collect_metrics();
    RulesConfig rules = load_rules_config("rules.json");

    auto diagnoses = run_ai_engine(metrics, rules);

    for (const auto& d : diagnoses) {
        std::cout << "\n❗ Problem : " << d.problem;
        std::cout << "\n🔍 Cause   : " << d.cause;
        std::cout << "\n✅ Fix     : " << d.solution << "\n";
    }

    return 0;
}

