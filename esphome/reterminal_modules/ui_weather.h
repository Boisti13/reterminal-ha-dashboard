#pragma once
#include <string>

static const char* weather_to_text(const std::string &s) {
  if (s == "clear-night")        return "Clear Night";
  if (s == "cloudy")             return "Cloudy";
  if (s == "exceptional")        return "Exceptional";
  if (s == "fog")                return "Fog";
  if (s == "hail")               return "Hail";
  if (s == "lightning")          return "Lightning";
  if (s == "lightning-rainy")    return "Thunderstorm";
  if (s == "partlycloudy")       return "Partly Cloudy";
  if (s == "pouring")            return "Heavy Rain";
  if (s == "rainy")              return "Rain";
  if (s == "snowy")              return "Snow";
  if (s == "snowy-rainy")        return "Sleet";
  if (s == "sunny")              return "Sunny";
  if (s == "windy")              return "Windy";
  if (s == "windy-variant")      return "Windy, Cloudy";
  return "Unknown";
}
