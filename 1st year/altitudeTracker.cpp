#include <iostream>
#include <iomanip>
#include <list>
using namespace std;

class DroneAltitudeTracker{
    private:
    list<float> altitudes;
    int size;

    public:
    DroneAltitudeTracker(int max = 5){
        size = max;
    }
    void addAltitude(float altitude){
        if(altitudes.size() >= 5){
            while(altitudes.size() > 4)
                altitudes.pop_front();
            altitudes.push_back(altitude);
        }else
            altitudes.push_back(altitude);
    }
    void displayAltitudes(){
        for(auto altitude: altitudes){
            cout << fixed << setprecision(1) 
                 << altitude << " m" << endl;
        }
    }
};

int main(){
    DroneAltitudeTracker droneAltitudeTracker;
    string input;

    while(true){
        cin >> input;
        if(input == "q")
            return 0;
        else if(input == "v")
            droneAltitudeTracker.displayAltitudes();
        else
            droneAltitudeTracker.addAltitude(stof(input));
    }
}