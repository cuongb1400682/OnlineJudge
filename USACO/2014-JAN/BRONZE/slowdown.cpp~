#include <fstream>
#include <iostream>
#include <list>
#include <cmath>

using namespace std;

const int MAX_N = 10000;

list<int> event;      // list of events
char cevent[MAX_N];   // character ('T' or 'D') represent for events
double ievent[MAX_N]; // value of events (time or distance)
int n;                // the number of events

inline list<int>::iterator find_event(double now, double dist, double speed, double & d, double & t) {
    d = t = 0;
    list<int>::iterator retval;

    // the nearest distance
    double min = 10000.;

    // for each element in list of events
    // find the nearest event
    for (list<int>::iterator p = event.begin(); p != event.end(); ++p) {
        if (cevent[*p] == 'D' && min > ievent[*p]) {
            min = ievent[*p];
            retval = p;

            t = (min - dist) * speed;
            d = min - dist;
        }

        if (cevent[*p] == 'T' && min > ((ievent[*p] - now) / speed) + dist) {
            retval = p;
            min = (ievent[*p] - now) / speed + dist;

            d = (ievent[*p] - now) / speed;
            t = ievent[*p] - now;
        }
    }

    return retval;
}

double solve(void) {
    double dist = 0;  // distance from the beginning to the end (in meters)
    double now = 0;   // total time to now (in secs)
    double speed = 1; // complement of speed (1 / speed)

    list<int>::iterator e;
    double d, t;

    // initialize the event list
    for (int i = 0; i < n; ++i)
        event.push_back(i);

    while (!event.empty()) {
        // find the nearest event, the interval (t),
        // and the distance from the previous event to the last
        e = find_event(now, dist, speed, d, t);

        now += t;
        dist += d;
        ++speed;

        event.erase(e);
    }

    return (1000. - dist) * speed + now;
}

int main(void) {
    ifstream in("slowdown.in");
    in >> n;
    for (int i = 0; i < n; ++i)
        in >> cevent[i] >> ievent[i];
    in.close();

    ofstream out("slowdown.out");
    double result = solve();
    out << static_cast<int>(round(result));
    out.close();
    return 0;
}
