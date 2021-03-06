#include "threshold.h"

template <class C, class P>
void ThresholdTransform<C, P>::set_input(C input, uint8_t input_channel) {
  if (input >= min_value && input <= max_value) {
    this->output = in_range;
  } else {
    this->output = out_range;
  }

  this->notify();
}

void NumericThreshold::get_configuration(JsonObject& root) {
  root["min"] = min_value;
  root["max"] = max_value;
  root["in_range"] = in_range;
  root["value"] = output;
}

static const char NUMERIC_SCHEMA[] PROGMEM = R"({
    "type": "object",
    "properties": {
        "min": { "title": "Minimum value", "type": "number", "description" : "Minimum value to be 'in range'" },
        "max": { "title": "Maximum value", "type": "number", "description" : "Maximum value to be 'in range'" },
        "in_range": { "title": "In range value", "type": "boolean", "description" : "Output value when input value is 'in range'" },
        "value": { "title": "Last value", "type" : "boolean", "readOnly": true }
    }
  })";

bool NumericThreshold::set_configuration(const JsonObject& config) {
  String expected[] = {"min", "max", "in_range", "value"};
  for (auto str : expected) {
    if (!config.containsKey(str)) {
      return false;
    }
  }
  min_value = config["min"];
  max_value = config["max"];
  in_range = config["in_range"];
  output = config["value"];

  return true;
}

String NumericThreshold::get_config_schema() { return FPSTR(NUMERIC_SCHEMA); }

void IntegerThreshold::get_configuration(JsonObject& root) {
  root["min"] = min_value;
  root["max"] = max_value;
  root["in_range"] = in_range;
  root["value"] = output;
}

static const char INTEGER_SCHEMA[] PROGMEM = R"({
      "type": "object",
      "properties": {
          "min": { "title": "Minimum value", "type": "number", "description" : "Minimum value to be 'in range'" },
          "max": { "title": "Maximum value", "type": "number", "description" : "Maximum value to be 'in range'" },
          "in_range": { "title": "In range value", "type": "boolean", "description" : "Output value when input value is 'in range'" },
          "value": { "title": "Last value", "type" : "boolean", "readOnly": true }
      }
    })";

bool IntegerThreshold::set_configuration(const JsonObject& config) {
  String expected[] = {"min", "max", "in_range"};
  for (auto str : expected) {
    if (!config.containsKey(str)) {
      return false;
    }
  }
  min_value = config["min"];
  max_value = config["max"];
  in_range = config["in_range"];
  output = config["value"];

  return true;
}

String IntegerThreshold::get_config_schema() { return FPSTR(INTEGER_SCHEMA); }