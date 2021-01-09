#include <app/Stats.hpp>


namespace app {
    
    Stats *Stats::getInstance() {
        static Stats stats;
        return &stats;
    }
}
