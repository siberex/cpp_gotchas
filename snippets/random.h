/**
 * snippets
 *
 * Author: Stephen Jingle <sib.li>
 * Created: 30 Sep 2025
 */


#pragma once

#include <random>
#include <stdexcept>


namespace sib {

    inline int getRandomInt(const int from, const int to) {
        if (from > to) {
            throw std::invalid_argument("getRandomInt: expected from <= to, provided: " + std::to_string(from) + " > " + std::to_string(to));
        }
        std::random_device dev;
        std::mt19937 engine(dev());
        std::uniform_int_distribution<int> distribution(from, to);
        auto getRand = [&] { return distribution(engine); };
        return getRand();
    }

} // namespace sib