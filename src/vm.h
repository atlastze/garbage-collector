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

#ifndef VM_H
#define VM_H

#include "state.h"
#include <vector>

class VM {
public:
    explicit VM(State *state)
        : state(state)
    {
    }

    void run();

private:
    void push(GCObject *value)
    {
        state->stack.push_back(value);
    }

    void pop()
    {
        if (state->stack.size() > 0)
            state->stack.pop_back();
    }

    GCObject *top()
    {
        return state->stack.back();
    }

    int size()
    {
        return state->stack.size();
    }

    void populate();
    void compose();

    State *state;
};

#endif /* VM_H */
