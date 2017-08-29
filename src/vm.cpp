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

static const int instructionCount = 50;

// Simulate executing opcodes, which are generated randomly.
void VM::run()
{
    srand(time(NULL));
    for (int i = 0; i < instructionCount; i++) {
        int opcode = rand() % 4;
        switch (opcode) {
        case 0: // push a new component into the m_stack
            push();
            break;
        case 1: // pop object, which becomes garbage
            pop();
            break;
        case 2:
            compose();
            break;
        case 3:
            circle();
            break;
        default:
            break;
        }
    }
    std::cout << ">> HALT\n";
}

// Push a new component into the m_stack
void VM::push()
{
    std::cout << ">> PUSH\n";
    auto object = m_state->newObject();
    m_state->m_stack.push_back(object);
}

void VM::pop()
{
    if (m_state->m_stack.size() > 0) {
        std::cout << ">> POP\n";
        m_state->m_stack.pop_back();
    }
}

// Compose top two objects
void VM::compose()
{
    int size = m_state->m_stack.size();
    if (size < 2)
        return;

    auto object1 = m_state->m_stack[size - 1];
    auto object2 = m_state->m_stack[size - 2];
    if (!object2->contains(object1)) {
        std::cout << ">> COMPOSE\n";
        object2->add(object1);
    }
}

// Circular references of top two objects
void VM::circle()
{
    int size = m_state->m_stack.size();
    if (size > 1) {
        auto object1 = m_state->m_stack[size - 1];
        auto object2 = m_state->m_stack[size - 2];
        if (!object2->contains(object1)) {
            object2->add(object1);
        }
        if (!object1->contains(object2)) {
            std::cout << ">> CIRCLE TOP TWO\n";
            object1->add(object2);
        }
    } else if (size > 0) {
        auto object = m_state->m_stack[size - 1];
        if (!object->contains(object)) {
            std::cout << ">> CIRCLE ITSELF\n";
            object->add(object);
        }
    }
}
