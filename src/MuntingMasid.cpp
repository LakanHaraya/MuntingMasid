/**
 * @file MuntingMasid.cpp
 * @brief Implementasyon ng `MuntingMasid` class para sa pag-log gamit ang syslog-style severity levels.
 */

#include "MuntingMasid.h"

MuntingMasid::MuntingMasid(
    Stream &stream,
    const char* appName,
    Severity minLevel,
    TimestampFunc tsFunc
) : 
    _stream(&stream),
    _appName(appName),
    _minLevel(minLevel),
    _timestampFunc(tsFunc)
{}

void MuntingMasid::setMinimumSeverity(Severity level) {
    _minLevel = level;
}

const char* MuntingMasid::_severityLabel(Severity severity) {
    static const char* labels[] = {
        "KAGI", // Emergency
        "ALRT", // Alert
        "KRIT", // Critical
        "MALI", // Error
        "BALA", // Warning
        "PNSN", // Notice
        "IMPO", // Info
        "DALI"  // Debug
    };
    return labels[severity];
}

void MuntingMasid::log(Severity severity, const char* message) {
    if (severity > _minLevel) return; 

    // Kung may timestamp function, tawagin ito at iprint ito sa stream
    if (_timestampFunc) {
        _stream->print(_timestampFunc());
        _stream->print(" ");
    }
    
    _stream->print("[");
    _stream->print(_severityLabel(severity));
    _stream->print("] [");
    _stream->print(_appName);
    _stream->print("] ");
    _stream->println(message);
}

// Pinaikling metodo
void MuntingMasid::emergency(const char* message) { log(EMERGENCY, message); }
void MuntingMasid::alert(const char* message) { log(ALERT, message); }
void MuntingMasid::critical(const char* message) { log(CRITICAL, message); }
void MuntingMasid::error(const char* message) { log(ERROR, message); }
void MuntingMasid::warning(const char* message) { log(WARNING, message); }
void MuntingMasid::notice(const char* message) { log(NOTICE, message); }
void MuntingMasid::info(const char* message) { log(INFO, message); }
void MuntingMasid::debug(const char* message) { log(DEBUG, message); }
