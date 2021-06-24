#ifndef UNTITLED2_PASSENGERS_H
#define UNTITLED2_PASSENGERS_H

#include <list>
#include <random>
#include <algorithm>

const int startCount = 5;

class Passengers {
public:
    Passengers() {
        this->refill();
    }

    struct Passenger {
        const int start;
        const int stop;

        Passenger(const int start, const int stop) : start(start), stop(stop) {};
    };

    void print() {
        for (Passenger p : this->passengers) {
            printf("start: %d, stop: %d\n", p.start, p.stop);
        }
    }

    void refill() {
        std::random_device rd;
        std::uniform_int_distribution<int> dist(0, 2);

        for (int i = 0; i < startCount; i++) {
            int start = dist(rd), stop = dist(rd);
            while (start == stop) stop = dist(rd);

            Passenger tmp(start, stop);
            this->passengers.push_back(tmp);
        }
    }

    std::list<Passenger>& getPassengers() {
        return this->passengers;
    }


private:
    std::list<Passenger> passengers;
};

#endif //UNTITLED2_PASSENGERS_H
