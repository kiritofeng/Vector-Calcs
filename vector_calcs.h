#include<bits/stdc++.h>
using namespace std;
struct vec2 {
    double x, y;

    vec2 operator + (const vec2 &v) {
        return vec2{x+v.x, y+v.y};
    }
    vec2 operator - (const vec2 &v) {
        return vec2{x-v.x, y-v.y};
    }

    double operator * (const vec2 &v) {
        return x*v.x+y*v.y;
    }

    double operator ^ (const vec2 &v) {
        return x * v.y - y * v.x;
    }

    double lenSq() {
        return x*x+y*y;
    }

    double len() {
        return sqrt(lenSq());
    }

    vec2 scale(double fact) {
        return {x * fact, y * fact};
    }

    vec2 normalize() {
    	return scale(1.0 / len());
    }
};
struct vec3 {
    double x, y, z;

    vec3 operator + (const vec3 &v) {
        return vec3{x+v.x, y+v.y, z+v.z};
    }
    vec3 operator - (const vec3 &v) {
        return vec3{x-v.x, y-v.y, z-v.z};
    }

    double operator * (const vec3 &v) {
        return x*v.x+y*v.y+z*v.z;
    }

    vec3 operator ^ (const vec3 &v) {
        return vec3{y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x};
    }

    double lenSq() {
        return x*x+y*y+z*z;
    }

    double len() {
        return sqrt(lenSq());
    }

    vec3 scale(double fact) {
        return {x * fact, y * fact, z * fact};
    }

    vec3 normalize() {
    	return scale(1.0 / len());
    }

};

struct plane {
    double p[4];
    plane(double d1,double d2, double d3, double d4) {
        tie(p[0],p[1],p[2],p[3]) = make_tuple(d1,d2,d3,d4);
    }
    double operator [] (int i) {
        return p[i];
    }
};

vec3 projPlane(plane eq, vec3 p, vec3 orig) {
	vec3 v = p - orig;
	vec3 n = {eq[0], eq[1], eq[2]};
	double dist = v*n;
	vec3 res = p-n.scale(dist);
	return p-n.scale(dist);
}

vec2 proj2d(plane eq, vec3 p, vec3 orig, vec3 fixedPoint) {
	vec3 projectedP = projPlane(eq, p, orig);
	vec3 fp1 = (projPlane(eq, fixedPoint, orig) - orig).normalize();
	vec3 fp2 = fp1 ^ (vec3){eq[0], eq[1], eq[2]};
	return {fp1*projectedP, fp2*projectedP};
}

vec3 intersectLinePlane(plane eq, vec3 a, vec3 b) {
	double t = -(eq[0] * b.x + eq[1] * b.y + eq[2] * b.z + eq[3]) / (eq[0] * (a.x - b.x) + eq[1] * (a.y - b.y) + eq[2] * (a.z - b.z));
	if(t < 0 || t > 1) {
		return {NAN, NAN, NAN};
	}
	return a.scale(t) + b.scale(1 - t);
}

vec2 intersectLineSegment(vec2 la, vec2 lb, vec2 sa, vec2 sb) {
	double a = la.y - lb.y;
	double b = lb.x - la.x;
	double c = -(a * la.x + b * la.y);
	double t = -(a * sb.x + b * sb.y + c) / (a * (sa.x - sb.x) + b * (sa.y - sb.y));
	if(t < 0 || t > 1) {
		return {NAN, NAN};
	}
	return sa.scale(t)+sb.scale(1 - t);
}

plane getPlane(vec3 &norm, vec3 &pnt) {
    return plane(norm.x,norm.y,norm.z,-(norm*pnt));
}
