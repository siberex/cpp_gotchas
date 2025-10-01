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
        sib::fmt("{}", sib::getRandomInt(10, 20));

}