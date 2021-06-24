#include "Passengers.h"
#include <queue>
#include <set>
using namespace std;

float arena_half_size_x = 85, arena_half_size_y = 45;
float player_half_size_x = 2.5, player_half_size_y = 12;
float elevator_p_y=0, elevator_dp_y = 1, elevator_half_size_x = 4.5, elevator_half_size_y = 6.5, time = 0;
int n = 0, napis1 = 0, napis2 = 0, cel = 0, time2 = 0;
int position = 0, people = 0, nast = 0;

class Elevator {
private:
    int position;
    std::queue<int> queue;
    std::set<int> helper;
    std::list<Passengers::Passenger> inElevator;
    Passengers passengers;

    void newPassengers() {
        for (Passengers::Passenger p : this->passengers.getPassengers()) {
            if (this->helper.find(p.start) == helper.end()) {
                this->queue.push(p.start);
                this->helper.insert(p.start);
            }
        }
    }

public:
    Elevator() : position(0) {
        this->newPassengers();
    }

    [[noreturn]] void makeAction() {
            // load passengers
            for (auto it = this->passengers.getPassengers().begin(); it != this->passengers.getPassengers().end();) {
                if (it->start == this->position) {
                    if (this->helper.find(it->stop) == helper.end()) {
                        this->queue.push(it->stop);
                        this->helper.insert(it->stop);
                    }
                    this->inElevator.push_back(*it);
                    n = this->position;
                    people = this->inElevator.size();
                    nast = this->queue.front();
                    cel = it->stop;
                    napis1 = 1;
                    it = this->passengers.getPassengers().erase(it);
                }
                else {
                    ++it;
                }
            }

            if (this->passengers.getPassengers().empty()) {
                this->passengers.refill();
                this->newPassengers();
            }

            // unload passengers
            for (auto it = this->inElevator.begin(); it != this->inElevator.end();) {
                if (it->stop == this->position) {
                    it = this->inElevator.erase(it);
                    n = this->position;
                    people = this->inElevator.size();
                    nast = this->queue.front();
                }
                else {
                    ++it;
                }
            }

            // get next destination
            this->position = this->queue.front();
            this->queue.pop();
            this->helper.erase(this->position);
            n = this->position;
            people = this->inElevator.size();
            nast = this->queue.front();
            napis2 = 1;
    }

    [[nodiscard]] int getPosition() const {
        return this->position;
    }

    [[nodiscard]] int getPeople() const {
        return this->inElevator.size();
    }

    [[nodiscard]] int getNext() const {
        return this->queue.front();
    }
};

internal void simulate_game(Input* input, float dt) {
    position = n;
    Elevator elevator;
    if (time2%300==0)
        elevator.makeAction();
    time2++;
    time += 1 * dt;
    if (elevator_p_y < position)   elevator_p_y += elevator_dp_y * dt;
    else                                elevator_p_y -= elevator_dp_y * dt;
    if (elevator_p_y < position && elevator_p_y > (position-0.03)) elevator_p_y = position;
    if (elevator_p_y > position && elevator_p_y < (position+0.03)) elevator_p_y = position;

    //Render
        draw_arena_borders(arena_half_size_x, arena_half_size_y, 0x666666);
        draw_rect(0, 0, arena_half_size_x, arena_half_size_y, 0x000000);
        draw_rect(0, -23, arena_half_size_x, 2, 0x666666);
        draw_rect(10, (arena_half_size_y / 2), 2, arena_half_size_y, 0x666666);

        draw_rect(-64, 13, 0.7, 25, 0x666666);
        draw_rect(-57, 13, 0.1, 25, 0x666666);
        draw_rect(-50, 13, 0.7, 25, 0x666666);

        draw_text("LVL", -80, 30, 0.4, 0xffffff);								draw_number(2, -70, 29, 0.6, 0xffffff);
        draw_text("LVL", -80, 15, 0.4, 0xffffff);								draw_number(1, -70, 14, 0.6, 0xffffff);
        draw_text("LVL", -80, 0, 0.4, 0xffffff);								draw_number(0, -70, -1, 0.6, 0xffffff);

        draw_text("TIME", 20, 40, 0.4, 0xffffff);						        draw_number(time, 78, 39, 0.6, 0xffffff);
        draw_text("CURRENT LEVEL", 20, 30, 0.4, 0xffffff);						draw_number(n, 78, 29, 0.6, 0xffffff);
        draw_text("NEXT DESTINATION LEVEL", 20, 20, 0.4, 0xffffff);				draw_number(nast, 78, 19, 0.6, 0xffffff);
        draw_text("NUMBER OF PASSENGERS", 20, 10, 0.4, 0xffffff);				draw_number(people, 78, 9, 0.6, 0xffffff);
        draw_text("PASSENGERS WEIGHT", 20, 0, 0.4, 0xffffff);					draw_number((people * 70), 78, -1, 0.6, 0xffffff);

        if (napis1)
        {
            draw_text("PASSENGER FROM LEVEL", -80, -30, 0.4, 0xffffff);				draw_number(n, -30, -31, 0.6, 0xffffff);
            draw_text("ENTERED AND WANTS TO GO TO LEVEL", -24, -30, 0.4, 0xffffff);	draw_number(cel, 55, -31, 0.6, 0xffffff);
        }

        if (napis2)
        {
            draw_text("ELEVATOR MOVES TO LEVEL", -80, -35, 0.4, 0xffffff);			draw_number(n, -22, -36, 0.6, 0xffffff);
        }

        draw_rect(-57, elevator_p_y*15, elevator_half_size_x, elevator_half_size_y, 0xffffff);
}