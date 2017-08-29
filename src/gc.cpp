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

int GCObject::m_totalCount = 0;

GCObject::GCObject()
    : m_marked(0)
{
    m_totalCount++;
    m_id = m_totalCount;
    std::cout << ".. Creating a new object, id: " << m_id << std::endl;
}

GCObject::~GCObject()
{
    std::cout << ".. Deleting object, id: " << m_id << std::endl;
}

GarbageCollector::~GarbageCollector()
{
    // delete all the remaining objects
    for (auto object : m_objectPool)
        delete object;
}

Object *GarbageCollector::newObject()
{
    if (m_objectPool.size() == m_thresholdCount)
        gc();
    Object *object = new Object;
    m_objectPool.push_back(object);
    return object;
}

void GarbageCollector::gc()
{
    mark();
    sweep();
    if (m_objectPool.size() >= m_thresholdCount)
        m_thresholdCount = 2 * m_thresholdCount;
}
