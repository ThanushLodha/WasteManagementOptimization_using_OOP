#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
using namespace std;

class Location {
public:
    int id;
    double x_coordinate;
    double y_coordinate;

    Location(int a, double x, double y) : id(a), x_coordinate(x), y_coordinate(y) {}

    virtual double CalculateDistance(const Location& other) const {
        double x1 = x_coordinate;
        double y1 = y_coordinate;
        double x2 = other.x_coordinate;
        double y2 = other.y_coordinate;
        double dx = x1 - x2;
        double dy = y1 - y2;
        dx = dx * dx;
        dy = dy * dy;
        double ans = sqrt(dx + dy);
        return ans;
    }
};

class WasteCollectionPoint : public Location {
public:
    double waste_quantity;

    WasteCollectionPoint(int a, double x, double y, double qty) : Location(a, x, y), waste_quantity(qty) {}

    double CalculateDistance(const Location& other) const override {
        const WasteCollectionPoint* otherPoint = dynamic_cast<const WasteCollectionPoint*>(&other);
        if (otherPoint) {
            return Location::CalculateDistance(other);
        } else {
            return std::numeric_limits<double>::max();
        }
    }
};

class Vehicle {
public:
    double waste_capacity;
    int id;

    Vehicle(int a, double capacity) : id(a), waste_capacity(capacity) {}
};

vector<WasteCollectionPoint> optimizedRoutes(vector<WasteCollectionPoint>& points)
{
    vector<WasteCollectionPoint> optimizedPoints;
    vector<bool> visited(points.size(), false);
    int currentPointIndex = 0;
    visited[currentPointIndex] = true;
    optimizedPoints.push_back(points[currentPointIndex]);
    while (optimizedPoints.size() < points.size())
    {
        double minDistance = numeric_limits<double>::max();
        int index;
        for (int i = 1; i < points.size(); i++)
        {
            if (!visited[i])
            {
                double a = points[currentPointIndex].CalculateDistance(points[i]);
                if (a < minDistance)
                {
                    minDistance = a;
                    index = i;
                }
            }
        }
        visited[index] = true;
        optimizedPoints.push_back(points[index]);
        currentPointIndex = index;
    }
    return optimizedPoints;
}

vector<vector<WasteCollectionPoint>> assignPointsToVehicles(const vector<WasteCollectionPoint>& points, vector<Vehicle>& vehicles) {
    vector<vector<WasteCollectionPoint>> assignedPoints(vehicles.size());
    vector<WasteCollectionPoint> sortedPoints = points;
    // sort(sortedPoints.begin(), sortedPoints.end(), [](const WasteCollectionPoint& p1, const WasteCollectionPoint& p2) {
    //     return p1.waste_quantity > p2.waste_quantity;
    // });

    for (const auto& point : sortedPoints) {
        int bestFitIndex = -1;
        double minCapacityDifference = numeric_limits<double>::max();

        for (int i = 0; i < vehicles.size(); i++) {
            double capacityDifference = vehicles[i].waste_capacity - point.waste_quantity;

            if (capacityDifference >= 0 && capacityDifference < minCapacityDifference) {
                minCapacityDifference = capacityDifference;
                bestFitIndex = i;
            }
        }

        if (bestFitIndex != -1) {
            vehicles[bestFitIndex].waste_capacity -= point.waste_quantity;
            assignedPoints[bestFitIndex].push_back(point);
        }
    }

    return assignedPoints;
}

int main()
{
    cout << "File Format:" << endl;
    cout << "<Number of places to pick up garbage from>" << endl;
    cout << "<place_id> <x_coordinate> <y_coordinate> <capacity>" << endl;
    cout << "<place_id> <x_coordinate> <y_coordinate> <capacity>" << endl;
    cout << "<place_id> <x_coordinate> <y_coordinate> <capacity>" << endl;
    cout << "....." << endl;
    cout << "<Number of vehicles>" << endl;
    cout << "<vehicle_id> <vehicle_capacity>" << endl;
    cout << "<vehicle_id> <vehicle_capacity>" << endl;
    cout << "....." << endl;
    char* envPath = getenv("MYFILE");
    string path;
    cout << "Enter the file name along with txt extension:" << endl;
    cin >> path;
    path = string(envPath)+'/'+path;
    ifstream inputFile(path);
    if (!inputFile)
    {
        cout << "Error opening file" << endl;
        return 1;
    }
    int numPoints;
    inputFile >> numPoints;
    vector<WasteCollectionPoint> points;
    for (int i = 0; i < numPoints; i++)
    {
        int id;
        double x;
        double y;
        double capacity;
        inputFile >> id >> x >> y >> capacity;
        points.emplace_back(id, x, y, capacity);
    }
    int numVehicles;
    inputFile >> numVehicles;
    vector<Vehicle> vehicles;
    for (int i = 0; i < numVehicles; i++)
    {
        int id;
        double capacity;
        inputFile >> id >> capacity;
        vehicles.emplace_back(id, capacity);
    }
    inputFile.close();
    vector<WasteCollectionPoint> optimizedPoints;
    optimizedPoints = optimizedRoutes(points);
    vector<vector<WasteCollectionPoint>> ans;
    ans = assignPointsToVehicles(optimizedPoints, vehicles);
    for (int i = 0; i < ans.size(); i++)
    {
        cout << "Vehicle: " << vehicles[i].id << "  Points: ";
        for (const auto& j : ans[i])
        {
            cout << j.id << "->";
        }
        cout << "Back to dumpyard!!" << endl;
    }

    return 0;
}
