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

#ifndef GC_H
#define GC_H

#include <vector>

static const int initialThresholdCount = 4;

// GC objects derived from GCObject
class Component; // the simple object
class Object; // the complex object, consist of simple objects

// visitor of visitor pattern
class GCObjectVisitor {
public:
    virtual void visit(Object *) = 0;
};

// base class of GC objects
class GCObject {
    friend class MarkVisitor;
    friend class PrintVisitor;
    friend class State;
    friend class GarbageCollector;

public:
    GCObject();
    virtual ~GCObject();

    virtual void accept(GCObjectVisitor *) = 0;

    // the number of allocated objects, including those collected garbage
    static int m_totalCount;

protected:
    // GC flag
    unsigned char m_marked;
    // object id
    int m_id;
};

class GarbageCollector {
public:
    GarbageCollector()
        : m_thresholdCount(initialThresholdCount)
    {
    }
    ~GarbageCollector();

    GarbageCollector(const GarbageCollector &) = delete;
    const GarbageCollector &operator=(const GarbageCollector &) = delete;

    // allocate GC objects
    Object *newObject();

    void unmarkAll()
    {
        for (auto object : m_objectPool)
            object->m_marked = 0;
    }

protected:
    // mark-and-sweep steps
    virtual void mark() = 0;
    virtual void sweep() = 0;
    virtual void gc();

    // all the remaining objects
    std::vector<GCObject *> m_objectPool;

    // the number of objects required to trigger a GC.
    int m_thresholdCount;
};

// complex GC object, consist of objects
class Object : public GCObject {
    friend class MarkVisitor;
    friend class PrintVisitor;

public:
    Object()
        : GCObject()
    {
    }
    virtual void accept(GCObjectVisitor *visitor)
    {
        visitor->visit(this);
    }

    void add(Object *object)
    {
        m_objects.push_back(object);
    }

    bool contains(Object *object)
    {
        for (auto child : m_objects)
            if (object == child)
                return true;
        return false;
    }

private:
    std::vector<Object *> m_objects;
};

#endif /* GC_H */
