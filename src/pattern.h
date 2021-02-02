#pragma once

class Pattern {
public:
    virtual void init() {};
    virtual void update() {};
    virtual ~Pattern() {};
};

class Factory {
public:
    virtual Pattern *getInstance() = 0;
};

template<class TPattern>
class PatternFactory : Factory {
public:
    Pattern *getInstance() {
        return new TPattern();
    }
};
