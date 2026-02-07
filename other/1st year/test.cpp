#include <iostream>
#include <set>
using namespace std;

template<typename T>
void uniqueWithThreshold(T arr[], int n, T k){
    set<T> uniques;
    for(int i = 0; i < n; i++){
        if(*(arr + i) > k)
            uniques.emplace(*(arr + i));
    }
    for(auto unique: uniques){
        cout << unique << endl;
    }
}

int main() {
    const int n = 5;

    int intData[n] = {3, 7, 1, 7, 9};
    float floatData[n] = {2.5, 7.1, 3.0, 2.5, 9.6};

    cout << "Unique integers greater than threshold 4:" << endl;
    uniqueWithThreshold(intData, n, 4);

    cout << "\nUnique floats greater than threshold 3.0:" << endl;
    uniqueWithThreshold(floatData, n, 3.0f);

    return 0;
}

/*
class ProjectLead{
    private:
    int teamSize;
    string* teamMembers;

    public:
    ProjectLead(): teamSize(0), teamMembers(nullptr) {}
    ~ProjectLead(){ delete[] teamMembers;}

    void setDetails(int size){
        teamSize = size;
        teamMembers = new string[teamSize];
    }
};
*/