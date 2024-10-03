#include <iostream>
#include <vector>
#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <algorithm>

using json = nlohmann::json;
using namespace std;

class Location {
public:
    string name;
    double latitude;
    double longitude;

    Location(string n, double lat, double lon) : name(n), latitude(lat), longitude(lon) {}
};

class WeatherVariable {
public:
    double temperature;
    double windSpeed;

    WeatherVariable(double temp = 0.0, double wind = 0.0) : temperature(temp), windSpeed(wind) {}

    void display() const {
        cout << "Temperature: " << temperature << "°C, Wind Speed: " << windSpeed << " m/s" << endl;
    }
};

size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* s) {
    size_t totalSize = size * nmemb;
    s->append((char*)contents, totalSize);
    return totalSize;
}

class LocationManager {
    vector<Location> locations;

public:
    void addLocation(const string& name, double lat, double lon) {
        locations.push_back(Location(name, lat, lon));
        cout << "Location added: " << name << endl;
    }

    void removeLocation(const string& name) {
        locations.erase(
            remove_if(locations.begin(), locations.end(), [&](const Location& loc) {
                return loc.name == name;
            }),
            locations.end());
        cout << "Location removed: " << name << endl;
    }

    const vector<Location>& getLocations() const {
        return locations;
    }

    void displayLocations() const {
        if (locations.empty()) {
            cout << "No locations available." << endl;
            return;
        }
        for (const auto& loc : locations) {
            cout << loc.name << " (Latitude: " << loc.latitude << ", Longitude: " << loc.longitude << ")" << endl;
        }
    }
};

class WeatherForecastingSystem {
public:
    WeatherVariable fetchWeatherForLocation(const Location& location) {
        CURL* curl;
        CURLcode res;
        string readBuffer;

        curl = curl_easy_init();
        if (curl) {
            string url = "https://api.open-meteo.com/v1/forecast?latitude=" + to_string(location.latitude) + "&longitude=" + to_string(location.longitude) + "&current_weather=true";

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
        }

        auto jsonResponse = json::parse(readBuffer);
        double temperature = jsonResponse["current_weather"]["temperature"];
        double windSpeed = jsonResponse["current_weather"]["windspeed"];

        return WeatherVariable(temperature, windSpeed);
    }
};

void fetchAndDisplayWeather(const LocationManager& locManager, WeatherForecastingSystem& weatherSystem) {
    const vector<Location>& locations = locManager.getLocations();
    for (const auto& loc : locations) {
        WeatherVariable weather = weatherSystem.fetchWeatherForLocation(loc);
        cout << "Weather for " << loc.name << ":\n";
        weather.display();
        cout << endl;
    }
}

void exportWeatherDataToCSV(const vector<WeatherVariable>& weatherData, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        file << "Temperature,Wind Speed\n";
        for (const auto& weather : weatherData) {
            file << weather.temperature << "," << weather.windSpeed << "\n";
        }
        file.close();
        cout << "Weather data exported to " << filename << endl;
    } else {
        cout << "Unable to open file " << filename << endl;
    }
}

void exportWeatherDataToJSON(const vector<WeatherVariable>& weatherData, const string& filename) {
    json j;
    for (const auto& weather : weatherData) {
        j.push_back({ {"temperature", weather.temperature}, {"windSpeed", weather.windSpeed} });
    }

    ofstream file(filename);
    if (file.is_open()) {
        file << j.dump(4);
        file.close();
        cout << "Weather data exported to " << filename << endl;
    } else {
        cout << "Unable to open file " << filename << endl;
    }
}

void displayMenu(LocationManager& locManager, WeatherForecastingSystem& weatherSystem) {
    int choice;
    do {
        cout << "\n--- Weather Forecast System ---\n";
        cout << "1. Add Location\n";
        cout << "2. Remove Location\n";
        cout << "3. View All Locations\n";
        cout << "4. Fetch and Display Weather\n";
        cout << "5. Export Weather Data to CSV\n";
        cout << "6. Export Weather Data to JSON\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string name;
            double lat, lon;
            cout << "Enter location name: ";
            cin >> name;
            cout << "Enter latitude: ";
            cin >> lat;
            cout << "Enter longitude: ";
            cin >> lon;
            locManager.addLocation(name, lat, lon);
            break;
        }
        case 2: {
            string name;
            cout << "Enter location name to remove: ";
            cin >> name;
            locManager.removeLocation(name);
            break;
        }
        case 3:
            locManager.displayLocations();
            break;
        case 4:
            fetchAndDisplayWeather(locManager, weatherSystem);
            break;
        case 5: {
            vector<WeatherVariable> weatherData;
            const vector<Location>& locations = locManager.getLocations();
            for (const auto& loc : locations) {
                weatherData.push_back(weatherSystem.fetchWeatherForLocation(loc));
            }
            exportWeatherDataToCSV(weatherData, "weather_data.csv");
            break;
        }
        case 6: {
            vector<WeatherVariable> weatherData;
            const vector<Location>& locations = locManager.getLocations();
            for (const auto& loc : locations) {
                weatherData.push_back(weatherSystem.fetchWeatherForLocation(loc));
            }
            exportWeatherDataToJSON(weatherData, "weather_data.json");
            break;
        }
        case 0:
            cout << "Exiting the system." << endl;
            break;
        default:
            cout << "Invalid choice, please try again." << endl;
        }

    } while (choice != 0);
}

int main() {
    LocationManager locManager;
    WeatherForecastingSystem weatherSystem;

    displayMenu(locManager, weatherSystem);

    return 0;
}
