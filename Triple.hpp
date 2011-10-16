#ifndef TRIPLE_HPP
#define TRIPLE_HPP

#include <string>

class Triple {
        public:
                double x, y, z;

                Triple(                                                 ) : x(0), y(0), z(0) {}
                Triple(double const &k                                  ) : x(k), y(k), z(k) {}
                Triple(double const &x, double const &y, double const &z) : x(x), y(y), z(z) {}

                std::string const to_string() const;

                Triple const operator + (Triple const &) const;
                Triple const operator + (double const &) const;
                Triple const operator - (              ) const;
                Triple const operator - (Triple const &) const;
                Triple const operator - (double const &) const;
                Triple const operator * (Triple const &) const;
                Triple const operator * (double const &) const;
                Triple const operator / (double const &) const;
                Triple const normalized (              ) const;
                Triple const cross      (Triple const &) const;
                double       dot        (Triple const &) const;
                double       length     (              ) const;
                double       length_2   (              ) const;
                double       ang_xy     (              ) const;

                Triple & operator  = (double const &);
                Triple & operator += (Triple const &);
                Triple & operator += (double const &);
                Triple & operator -= (Triple const &);
                Triple & operator -= (double const &);
                Triple & operator *= (double const &);
                Triple & operator /= (double const &);
                Triple & normalize   (              );
};

#endif
