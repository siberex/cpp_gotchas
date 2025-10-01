/**
 * snippets
 *
 * Author: Stephen Jingle <sib.li>
 * Created: 30 Sep 2025
 */


#pragma once

#include <random>
#include <functional>


namespace sib {

    inline int getRandomInt(const int from, const int to) {
        std::random_device dev;
        std::mt19937 engine(dev());
        std::uniform_int_distribution<int> distribution(from,to);
        // return distribution(engine);
        auto getRand = std::bind(distribution, engine);
        return getRand();
    }

} // namespace sib