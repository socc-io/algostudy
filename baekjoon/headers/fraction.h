//
//  fraction.h
//  DailyCodingTeamNote
//
//  Created by IRIS on 10/12/15.
//  Copyright (c) 2015 IRIS. All rights reserved.
//

#pragma once

/*NOTE
1. All operation ALWAYS returns value of which denominator is POSITIVE.
2. BE AWARE OF OVERFLOW!
 */

template <typename T>
class Fraction {
public:

    T x, y; // x over y, y SHOULD NOT BE 0
    Fraction(T x, T y) {
        this->x = x;
        this->y = y;
        init();
    }
    void init() { //make y (denominator) POSTIIVE
        if (this->y < 0) {
            this->x *= -1;
            this->y *= -1;
        }
    }

    Fraction operator+ (const Fraction f) const {
        T g = abs(gcd(this->y, f.y));
        
        T _y = (this->y / g) * f.y;
        T _x = this->x * (_y / this->y) + f.x * (_y / f.y);
        
        T _g = abs(gcd(_x, _y));
        
        return Fraction(_x / _g, _y / _g);
        
    }
    Fraction operator- (const Fraction f) const {
        return (*this) + Fraction(-f.x, f.y);
    }
    Fraction operator* (const Fraction f) const {
        
        return Fraction(
                          (this->x / abs(gcd(this->x, f.y)) ) * (f.x / abs(gcd(this->y, f.x))),
                          (this->y / abs(gcd(this->y, f.x)) ) * (f.y / abs(gcd(this->x, f.y)))
                        );
    }
    Fraction operator/ (const Fraction f) const {
        return (*this) * Fraction( f.y, f.x);
    }
};
