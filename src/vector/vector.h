#include <vector>
#include <iostream>

template<typename T> class Vector {
private:
    std::vector<T> values;

public:
    Vector(std::initializer_list<T> values_): values(values_) {}
    Vector(std::vector<T> vector_): values(vector_) {}
    Vector(size_t n, const T& val): values(std::vector<T>(n, val)) {}


    T operator[](const size_t i) const {
        return values[i];
    }

    bool operator==(const Vector<T> &other) const;
    bool operator< (const Vector<T> &other) const;
    bool operator<=(const Vector<T> &other) const;

    Vector operator-() const;
    Vector operator+=(const Vector<T> &other);
    Vector operator+ (const Vector<T> &other) const;
    Vector operator-=(const Vector<T> &other);
    Vector operator- (const Vector<T> &other) const;
    Vector operator+ (const T& addend) const;
    Vector operator*=(const Vector<T> &other);
    Vector operator* (const Vector<T> &other) const;
    Vector operator/=(const Vector<T> &other);
    Vector operator/ (const Vector<T> &other) const;

    template<typename U> Vector operator*(const U &coef) const;
    template<typename U> Vector operator/(const U &divisor) const;

    size_t size() const;

    template<typename U>
    friend std::ostream& operator<< (std::ostream &os, const Vector<U> &vector);
};


template <typename T>
bool Vector<T>::operator==(const Vector<T> &other) const {
    return this->values == other.values;
}

template <typename T>
bool Vector<T>::operator<(const Vector<T> &other) const {
    return this->values < other.values;
}

template <typename T>
bool Vector<T>::operator<=(const Vector<T> &other) const {
    return this->values <= other.values;
}



template <typename T>
Vector<T> Vector<T>::operator-() const {
    Vector neg(this->values);
    for (size_t i = 0; i < this->size(); i++){
        neg.values[i] = -neg.values[i];
    }
    return neg;
}


template <typename T>
Vector<T> Vector<T>::operator+=(const Vector<T> &other) {
    assert(this->values.size() == other.values.size());

    for (size_t i = 0; i < this->size(); i++){
        this->values[i] += other[i];
    }
    return *this;
}

template <typename T>
Vector<T> Vector<T>::operator+(const Vector<T> &other) const {
    Vector<T> sum(this->values);
    sum += other;
    return sum;
}

template <typename T>
Vector<T> Vector<T>::operator-=(const Vector<T> &other) {
    *this += -other;
    return *this;
}

template <typename T>
Vector<T> Vector<T>::operator-(const Vector<T> &other) const {
    return *this + (-other);
}

template <typename T>
Vector<T> Vector<T>::operator+(const T &addend) const {
    return *this + Vector<T>(this->size(), addend);
}

template <typename T>
Vector<T> Vector<T>::operator*=(const Vector<T> &other) {
    assert(this->values.size() == other.values.size());

    for (size_t i = 0; i < this->size(); i++){
        this->values[i] *= other[i];
    }
    return *this;
}

template <typename T>
Vector<T> Vector<T>::operator*(const Vector<T> &other) const {
    Vector<T> prod(this->values);
    prod *= other;
    return prod;
}

template <typename T>
template <typename U>
Vector<T> Vector<T>::operator*(const U &coef) const {
    return *this * Vector<T>(this->size(), coef);
}

template <typename T, typename U>
Vector<T> operator*(const U &coef, const Vector<T> &vector) {
    return vector * coef;
}

template <typename T>
Vector<T> Vector<T>::operator/=(const Vector<T> &other) {
    assert(this->values.size() == other.values.size());

    for (size_t i = 0; i < this->size(); i++){
        this->values[i] /= other[i];
    }
    return *this;
}

template <typename T>
Vector<T> Vector<T>::operator/(const Vector<T> &other) const {
    Vector<T> quotient(this->values);
    quotient /= other;
    return other;
}

template <typename T>
template <typename U>
Vector<T> Vector<T>::operator/(const U &divisor) const {
    return *this / Vector<T>(this->size(), divisor);
}

template <typename T>
size_t Vector<T>::size() const {
    return this->values.size();
}


template <typename T>
std::ostream& operator<<(std::ostream &os, const Vector<T> &vector){
    for(auto v: vector.values) os << v << ", ";
    os << std::endl;
    return os;
}
