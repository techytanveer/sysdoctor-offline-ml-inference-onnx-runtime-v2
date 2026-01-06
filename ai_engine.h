#ifndef AI_ENGINE_H
#define AI_ENGINE_H

#include <vector>
#include "system_metrics.h"
#include "diagnosis.h"
#include "rules_config.h"

std::vector<Diagnosis> run_ai_engine(
    const SystemMetrics& metrics,
    const RulesConfig& rules
);

#endif

