// Copyright (C) 2017, kylinsage <kylinsage@gmail.com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "vm.h"
#include "state.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

static const int instructionCount = 32;

// Simulate executing opcodes, which are generated randomly.
void VM::run()
{
    srand(time(NULL));
    for (int i = 0; i < instructionCount; i++) {
        int opcode = rand() % 4;
        switch (opcode) {
        case 0: // push a new component into the stack
            populate();
            break;
        case 1:
            if (size() >= 1) { // pop object, which becomes garbage
                std::cout << ">> POP\n";
                pop();
            } else {
                populate();
            }
            break;
        default:
            if (size() >= 2) { // compose top two objects
                compose();
            } else {
                populate();
            }
            break;
        }
    }
    std::cout << ">> HALT\n";
}

// Push a new component into the stack
void VM::populate()
{
    std::cout << ">> PUSH\n";
    push(state->newComponent());
}

// Compose top two objects
void VM::compose()
{
    std::cout << ">> COMPOSE\n";
    auto composite = state->newComposite();
    composite->add(top());
    pop();
    composite->add(top());
    pop();
    push(composite);
}
