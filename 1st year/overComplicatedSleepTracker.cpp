#include <iostream>
using namespace std;

typedef struct{
    int hours;
    int minutes;
}Time;

class SleepTracker{
    protected:
    Time bedTime, wakeTime;
    int sleepDuration;
    
    public:
    SleepTracker(Time bedTime, Time wakeTime){
        this->bedTime = bedTime;
        this->wakeTime = wakeTime;
    }
    virtual Time showSleepDuration() = 0;
    virtual int getSleepDuration() = 0;
};

class WeekdaySleep: public SleepTracker{
    public:
    WeekdaySleep(Time bedTime, Time wakeTime): 
                 SleepTracker(bedTime, wakeTime) {}
    
    Time showSleepDuration() override{
        Time sleepDur;
        int wakeMinutes = ((wakeTime.hours * 60) + wakeTime.minutes);
        int bedMinutes = ((bedTime.hours * 60) + bedTime.minutes);
        
        if(wakeMinutes < bedMinutes){ //crossed 12 AM
            sleepDuration = wakeMinutes - bedMinutes;
            sleepDuration += 24 * 60;
        }else
            sleepDuration = wakeMinutes - bedMinutes;
        
        sleepDur.hours = sleepDuration / 60;
        sleepDur.minutes = sleepDuration % 60;
        
        return sleepDur;
    }
    int getSleepDuration() override{
        return sleepDuration;
    }
};

class WeekendSleep: public SleepTracker{
    public:
    WeekendSleep(Time bedTime, Time wakeTime): 
                 SleepTracker(bedTime, wakeTime) {}
    
    Time showSleepDuration() override{
        Time sleepDur;
        int wakeMinutes = ((wakeTime.hours * 60) + wakeTime.minutes);
        int bedMinutes = ((bedTime.hours * 60) + bedTime.minutes);
        
        if(wakeMinutes < bedMinutes){ //crossed 12 AM
            sleepDuration = wakeMinutes - bedMinutes;
            sleepDuration += 24 * 60;
        }else
            sleepDuration = wakeMinutes - bedMinutes;
        
        sleepDur.hours = sleepDuration / 60;
        sleepDur.minutes = sleepDuration % 60;
        
        return sleepDur;
    }
    int getSleepDuration() override{
        return sleepDuration;
    }
};

int main(){
    Time wkdyBedTime, wkdyWakeTime;
    Time wkedBedTime, wkedWakeTime;
    cin >> wkdyBedTime.hours >> wkdyBedTime.minutes 
        >> wkdyWakeTime.hours >> wkdyWakeTime.minutes;
    cin >> wkedBedTime.hours >> wkedBedTime.minutes 
        >> wkedWakeTime.hours >> wkedWakeTime.minutes;
    int weekdayMins, weekendMins;
    
    SleepTracker *p;
    WeekdaySleep wkdy(wkdyBedTime, wkdyWakeTime);
    WeekendSleep wked(wkedBedTime, wkedWakeTime);
    
    p = &wkdy;
    cout << "Weekday: " << p->showSleepDuration().hours << "h " 
                        << p->showSleepDuration().minutes << "m " << endl;
    weekdayMins = p->getSleepDuration();
    p = &wked;
    cout << "Weekend: " << p->showSleepDuration().hours << "h " 
                        << p->showSleepDuration().minutes << "m " << endl;
    weekendMins = p->getSleepDuration();
    
    if(weekdayMins > weekendMins)
        cout << "User slept more on weekdays." << endl;
    else if(weekdayMins < weekendMins)
        cout << "User slept more on the weekend." << endl;
    else if(weekdayMins == weekendMins)
        cout << "User slept the same amount on weekdays and weekend." << endl;
    
    return 0;
}

