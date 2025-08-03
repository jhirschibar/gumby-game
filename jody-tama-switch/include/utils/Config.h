#pragma once

#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

// Configuration value types
using ConfigValue = std::variant<bool, int, float, std::string>;

class Config {
public:
    // Loading and saving
    static bool load(const std::string& filename);
    static bool save(const std::string& filename);
    
    // Value access
    static bool getBool(const std::string& key, bool defaultValue = false);
    static int getInt(const std::string& key, int defaultValue = 0);
    static float getFloat(const std::string& key, float defaultValue = 0.0f);
    static std::string getString(const std::string& key, const std::string& defaultValue = "");
    
    // Value setting
    static void setBool(const std::string& key, bool value);
    static void setInt(const std::string& key, int value);
    static void setFloat(const std::string& key, float value);
    static void setString(const std::string& key, const std::string& value);
    
    // Utility
    static bool hasKey(const std::string& key);
    static void removeKey(const std::string& key);
    static void clear();
    
    // Default configuration
    static void setDefaults();
    
private:
    static std::unordered_map<std::string, ConfigValue> values;
    
    // Helper methods
    static ConfigValue getValue(const std::string& key);
    static void setValue(const std::string& key, const ConfigValue& value);
    static std::string serializeValue(const ConfigValue& value);
    static ConfigValue deserializeValue(const std::string& type, const std::string& value);
};