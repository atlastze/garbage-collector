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

#include "gc.h"
#include <iostream>

int GCObject::totalCount = 0;

GCObject::GCObject()
    : marked(0)
{
    totalCount++;
    id = totalCount;
    std::cout << ".. Creating a new object, id: " << id << std::endl;
}

GCObject::~GCObject()
{
    std::cout << ".. Deleting object, id: " << id << std::endl;
}

GarbageCollector::~GarbageCollector()
{
    // delete all the remaining objects
    for (auto object : objects)
        delete object;
}

Component *GarbageCollector::newComponent()
{
    if (objects.size() >= thresholdCount)
        gc();
    Component *component = new Component;
    objects.push_back(component);
    return component;
}

Composite *GarbageCollector::newComposite()
{
    if (objects.size() == thresholdCount)
        gc();
    Composite *composite = new Composite;
    objects.push_back(composite);
    return composite;
}

void GarbageCollector::gc()
{
    mark();
    sweep();
    if (objects.size() >= thresholdCount)
        thresholdCount = 2 * thresholdCount;
}
