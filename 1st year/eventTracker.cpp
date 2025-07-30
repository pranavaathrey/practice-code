#include <iostream>
#include <string>
using namespace std;

class Event{
    private:
    static long totalParticipants;
    int participantID;
    string participantName;
    
    public:
    void setParticipant(int id, string name){
        participantID = id;
        participantName = name;
        totalParticipants++;
    }
    
    int getParticipantID(){
        return participantID;
    }
    
    string getParticipantName(){
        return participantName;
    }
    
    static int getTotalParticipants(){
        return totalParticipants;
    }
};

long Event::totalParticipants = 0;

int main(){
    int n, id, searchID;
    string name;
    cin >> n;
    
    Event participants[n];
    
    for(int i = 0; i < n; i++){
        cin >> id;
        cin.ignore();
        getline(cin, name);
        
        participants[i].setParticipant(id, name);
    }
    cin >> searchID;
    
    bool found = false;
    for(int i = 0; i < n; i++){
        if(searchID == participants[i].getParticipantID()){
            cout << "Participant found: "
                 << "Participant ID: " << participants[i].getParticipantID()
                 << ", Name: " << participants[i].getParticipantName() << endl;
            found = true;
        }
    }
    if(!found) 
        cout << "Participant with ID " << searchID << " not found." << endl;
    
    return 0;
}
