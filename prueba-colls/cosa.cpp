#include <cmath>
#include <tuple>

#include <FreeSOLID/3D/Point.h>
#include <FreeSOLID/3D/Quaternion.h>
#include <FreeSOLID/SOLID/solid.h>

#define PRINT_COLL_DATA(CD) \
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

int main(int argc, char **argv) {
        unsigned int c, i, n;
        int obj1 = 1, obj2 = 2;
        vector<tuple<DtCollData, DtObjectRef, DtObjectRef>> cs;

        dtDisableCaching();

        DtShapeRef shape = dtNewComplexShape();
                dtBegin(DT_SIMPLEX);
                        dtVertex(-1, 0, 0);
                        dtVertex( 1, 0, 0);
                dtEnd();
        dtEndComplexShape();

        dtCreateObject(&obj1, shape);
        dtCreateObject(&obj2, shape);
        dtSetPairResponse(&obj1, &obj2, &collide, DT_SMART_RESPONSE, &cs);

        dtSelectObject(&obj1);
        dtLoadIdentity();

        dtSelectObject(&obj2);
        dtLoadIdentity();
        {
                auto q = Quaternion(Vector(0, 0, 1), M_PI / 2.0);
                dtRotate(q[0], q[1], q[2], q[3]);
                dtTranslate(-5, 0, 0);
        }

        dtProceed();

        while (true) {
                while (true) {
                        cs.clear();
                        dtTestObjects(&obj1, &obj2);
                        c = cs.size();
                        if (c == 0) {
                                //cout << "Cero colisiones! :-O" << endl;
                                break;
                        }
                        if (c == 1) cout << "Una colisión! :-O" << endl;
                        else cout << c << " colisiones! :-O" << endl;

                        for (i = 0, n = cs.size(); i < n; i++) {
                                auto cd = cs[i];
                                auto d  = get<0>(cd);
                                auto n  = d.normal;
                                auto p1 = d.point1;
                                auto p2 = d.point2;
                                auto o1 = get<1>(cd);
                                auto o2 = get<2>(cd);

                                PRINT_COLL_DATA(d);

                                dtSelectObject(o1);
                                dtTranslate(-n[0], -n[1], -n[2]);
                                dtSelectObject(o2);
                                dtTranslate( n[0],  n[1],  n[2]);
                        }
                }
                dtProceed();

                dtSelectObject(&obj2);
                dtTranslate(0.1, 0, 0);
        }
}
