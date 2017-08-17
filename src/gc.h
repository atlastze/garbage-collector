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
class Composite; // the complex object, consist of simple objects

// visitor of visitor pattern
class GCObjectVisitor {
public:
    virtual void visit(Component *) = 0;
    virtual void visit(Composite *) = 0;
};

// base class of GC objects
class GCObject {
    friend class MarkVisitor;
    friend class PrintVisitor;
    friend class State;

public:
    GCObject();
    virtual ~GCObject();

    virtual void accept(GCObjectVisitor *) = 0;

    // the number of allocated objects, including those collected garbage
    static int totalCount;

protected:
    // GC flag
    unsigned char marked;
    // object id
    int id;
};

class GarbageCollector {
public:
    GarbageCollector()
        : thresholdCount(initialThresholdCount)
    {
    }
    ~GarbageCollector();

    GarbageCollector(const GarbageCollector &) = delete;
    const GarbageCollector &operator=(const GarbageCollector &) = delete;

    // allocate GC objects
    Component *newComponent();
    Composite *newComposite();

protected:
    // mark-and-sweep steps
    virtual void mark() = 0;
    virtual void sweep() = 0;
    virtual void gc();

    // all the remaining objects
    std::vector<GCObject *> objects;

    // the number of objects required to trigger a GC.
    int thresholdCount;
};

// simple GC object
class Component : public GCObject {
public:
    Component()
        : GCObject()
    {
    }
    virtual void accept(GCObjectVisitor *visitor)
    {
        visitor->visit(this);
    }
};

// complex GC object, consist of objects
class Composite : public GCObject {
    friend class MarkVisitor;
    friend class PrintVisitor;

public:
    Composite()
        : GCObject()
    {
    }
    virtual void accept(GCObjectVisitor *visitor)
    {
        visitor->visit(this);
    }

    void add(GCObject *object)
    {
        components.push_back(object);
    }

private:
    std::vector<GCObject *> components;
};

#endif /* GC_H */
