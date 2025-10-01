/**
 * snippets
 *
 * Author: Stephen Jingle <sib.li>
 * Created: 30 Sep 2025
 */

#include "log.h"
#include "random.h"

int main() {

    sib::fmt("{}", sib::getRandomInt(-20, -10));
    try {
        sib::fmt("{}", sib::getRandomInt(20, 10));
    } catch (const std::invalid_argument& e) {
        sib::err(e.what());
    }
}