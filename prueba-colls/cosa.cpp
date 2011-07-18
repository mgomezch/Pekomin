#include <cmath>
#include <tuple>

#include <3D/Point.h>
#include <3D/Quaternion.h>
#include <SOLID/solid.h>

#define PRINT_COLL_DATA(CD)                                                                                                \
                cout << "Punto 1: (" << (CD).point1[0] << ", " << (CD).point1[1] << ", " << (CD).point1[2] << ")" << endl; \
                cout << "Punto 2: (" << (CD).point2[0] << ", " << (CD).point2[1] << ", " << (CD).point2[2] << ")" << endl; \
                cout << "Normal : (" << (CD).normal[0] << ", " << (CD).normal[1] << ", " << (CD).normal[2] << ")" << endl;

void collide(void *client_data, DtObjectRef obj1, DtObjectRef obj2, const DtCollData *coll_data) {
        cout << "Colisión entre " << *static_cast<int *>(obj1) << " (" << obj1 << ") y " << *static_cast<int *>(obj2) << " (" << obj2 << ")" << endl;
        if (coll_data) {
                PRINT_COLL_DATA(*coll_data);
                reinterpret_cast<vector<tuple<DtCollData, DtObjectRef, DtObjectRef>> *>(client_data)->push_back(make_tuple(*coll_data, obj1, obj2));
        }
}

#define MAKE_OBJ(PX, PY, PZ, ROT)              \
        objp = new tuple<double[3], double>(); \
        get<0>(*objp)[0] = (PX);               \
        get<0>(*objp)[1] = (PY);               \
        get<0>(*objp)[2] = (PZ);               \
        get<1>(*objp) = 0;                     \
        objs.push_back(objp);                  \
        dtCreateObject(objp, shape);

int main(int argc, char **argv) {
        unsigned int c, i, n;
        tuple<double[3], double> *objp;
        vector<decltype(objp)> objs;
        vector<tuple<DtCollData, DtObjectRef, DtObjectRef>> cs;

        dtDisableCaching();

        DtShapeRef shape = dtNewComplexShape();
                dtBegin(DT_SIMPLEX);
                        dtVertex(-1, 0, 0);
                        dtVertex( 1, 0, 0);
                dtEnd();
        dtEndComplexShape();

        auto obj1 = MAKE_OBJ( 0, 0, 0, 0       );
        auto obj2 = MAKE_OBJ(-5, 0, 0, M_PI/2.0);

        dtSetDefaultResponse(&collide, DT_SMART_RESPONSE, &cs);

        for (i = 0, n = objs.size(); i < n; i++) {
                dtSelectObject(objs[i]);
                dtLoadIdentity();
                {
                        auto q = Quaternion(Vector(0, 0, 1), get<1>(*(objs[i])));
                        dtRotate(q[0], q[1], q[2], q[3]);
                        dtTranslate(get<0>(*(objs[i]))[0], get<0>(*(objs[i]))[1], get<0>(*(objs[i]))[2]);
                }
        }
        dtProceed();

        while (true) {
                get<0>(*obj2)[0] += 0.2;

                for (i = 0, n = objs.size(); i < n; i++) {
                        dtSelectObject(objs[i]);
                        dtLoadIdentity();
                        {
                                auto q = Quaternion(Vector(0, 0, 1), get<1>(*(objs[i])));
                                dtRotate(q[0], q[1], q[2], q[3]);
                                dtTranslate(get<0>(*(objs[i]))[0], get<0>(*(objs[i]))[1], get<0>(*(objs[i]))[2]);
                        }
                }

                while (true) {
                        cs.clear();
                        c = dtTest();
                        if (c == 0) {
//                              cout << "Cero colisiones! :-O" << endl;
                                break;
                        }
                        if (c == 1) cout << "Una colisión! :-O" << endl;
                        else cout << c << " colisiones! :-O" << endl;

                        for (i = 0, n = cs.size(); i < n; ++i) {
                                auto cd = cs[i];
                                auto d  = get<0>(cd);
                                auto n  = d.normal;
//                              auto p1 = d.point1;
//                              auto p2 = d.point2;
                                auto o1 = reinterpret_cast<decltype(objp)>(get<1>(cd));
                                auto o2 = reinterpret_cast<decltype(objp)>(get<2>(cd));

                                PRINT_COLL_DATA(d);

                                get<0>(*o1)[0] += n[0];
                                get<0>(*o1)[1] += n[1];
                                get<0>(*o1)[2] += n[2];
                                get<0>(*o2)[0] -= n[0];
                                get<0>(*o2)[1] -= n[1];
                                get<0>(*o2)[2] -= n[2];

                                dtSelectObject(o1);
                                dtLoadIdentity();
                                {
                                        auto q = Quaternion(Vector(0, 0, 1), get<1>(*o1));
                                        dtRotate(q[0], q[1], q[2], q[3]);
                                        dtTranslate(get<0>(*o1)[0], get<0>(*o1)[1], get<0>(*o1)[2]);
                                }
                                dtSelectObject(o2);
                                dtLoadIdentity();
                                {
                                        auto q = Quaternion(Vector(0, 0, 1), get<1>(*o1));
                                        dtRotate(q[0], q[1], q[2], q[3]);
                                        dtTranslate(get<0>(*o2)[0], get<0>(*o2)[1], get<0>(*o2)[2]);
                                }
                        }
                }
                dtProceed();
        }
}
