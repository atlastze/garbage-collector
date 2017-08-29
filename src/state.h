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

#ifndef STATE_H
#define STATE_H

#include "gc.h"
#include <vector>

class State : public GarbageCollector {
    friend class VM;

public:
    State() {}
    ~State() {}

    State(const State &) = delete;
    const State &operator=(const State &) = delete;

    void runVM();

protected:
    // implement virtual methods
    void mark();
    void sweep();

    std::vector<Object *> m_stack;
};

#endif /* STATE_H */
