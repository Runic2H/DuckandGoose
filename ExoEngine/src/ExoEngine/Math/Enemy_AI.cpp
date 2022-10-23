void AITree(E_State enemystate) {
    switch(enemystate) {
        case E_State::patrol:
        //walk left a bit
        //walk right a bit
        //check for player within range
            //check self for type
                //switch to melee or ranged based on enemy type
        break;
        case E_state::chase:
        //close in on player position
        //when within attack range, perform melee attack
        break;
        case E_state::attack:
        //attack the player
        //if out of range, return to chase state
        break;
    }
}