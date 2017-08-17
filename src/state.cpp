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

#include "state.h"
#include <iostream>

class MarkVisitor : public GCObjectVisitor {
public:
    virtual void visit(Component *component)
    {
        if (component->marked)
            return;
        component->marked = 1;
    }

    virtual void visit(Composite *composite)
    {
        if (composite->marked)
            return;
        composite->marked = 1;
        for (auto component : composite->components)
            component->accept(this);
    }
};

class PrintVisitor : public GCObjectVisitor {
public:
    virtual void visit(Component *component)
    {
        std::cout << component->id;
    }

    virtual void visit(Composite *composite)
    {
        std::cout << composite->id << ": {";
        for (auto component : composite->components) {
            std::cout << " ";
            component->accept(this);
        }
        std::cout << " }";
    }
};

void State::mark()
{
    MarkVisitor marker;
    for (auto object : stack)
        object->accept(&marker);
}

void State::sweep()
{
    int garbageCount = 0;
    for (auto i = objects.begin(); i != objects.end();) {
        if (!(*i)->marked) {
            delete *i;
            objects.erase(i); // don't advance the iterator
            garbageCount++;
        } else {
            (*i)->marked = 0;
            ++i;
        }
    }

    if (garbageCount > 0) {
        std::cout << "\t" << garbageCount << " object(s) collected\n";
        if (objects.size() == 0)
            return;
        std::cout << "\tthe remaining object(s):\n";
        PrintVisitor printer;
        for (auto object : objects) {
            std::cout << "\t";
            object->accept(&printer);
            std::cout << "\n";
        }
    }
}
