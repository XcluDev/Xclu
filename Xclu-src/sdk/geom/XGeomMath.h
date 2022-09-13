#pragma once

// Сделано на основе ofxKu/ofxKuGeom

/*
XGeomGeom - geometrical utils
Structure XGeomGeomLine2D for working with line in 2D:
 - compute line equation,
 - compute signed distance from a line,
 - project point on line,
 - mirror point of line.

Triangle in 3D:
 - cross line segment and triangle 

Plane in 3D:
 - signed distance from point to plane
 - projection of the point to plane
 - cross line segment and plane

Point clouds:
 - minimal distance between two point sets
Polygons:
 - signed triangle area
 - compute if point is inside polygon
Sphere:
 - convert points from unit square to unit sphere and back
 - create circle on a unit sphere
*/

#include "xmath.h"
#include <QVector>

// Line in 2D
struct XGeomGeomLine2D {
    vec2 p0, p1;
    vec2 normal;
	//(a,b) = normal, looks on the right in left-handed coord.system (oF screen)
	//normal is normalized
	// conormal directed as p1-p0 is (-b,a)
	float a = 0;
	float b = 0;
	float c = 0;
    XGeomGeomLine2D() {}
    XGeomGeomLine2D(const vec2 &p0, const vec2 &p1);
    XGeomGeomLine2D(float x1, float y1, float x2, float y2);
    void setup(const vec2 &p0, const vec2 &p1);

    float sgd(const vec2 &p);		//signed distance to point
    vec2 project(const vec2 &p);	//project point onto line
    vec2 mirror(const vec2 &p);	//mirror point

	//if pcross is not NULL, sets to crossing point
	//note: we don't consider boundary cases such as parallel lines
    bool intersect_segments(const XGeomGeomLine2D &line, vec2 *pcross = NULL);
    bool intersect_segments(const vec2& p0, const vec2& p1, vec2* pcross = NULL);

    // void draw_rect(float rad = 0.5);	//draw quad with "rad" distance for creating hi-res shots
};

// Line in 3D
struct XGeomGeomLine3D {
    vec3 p0, p1;
    vec3 dir_unnormalized;
	bool is_ray = false;	// notification that it's ray from p0

	// Line equation is p0 + t*dir_unnormalized, t in R; for segment t in [0,1]
    XGeomGeomLine3D() {}
    XGeomGeomLine3D(const vec3& p0, const vec3& p1);
    void setup(const vec3& p0, const vec3& p1);
    void setup_ray(const vec3& p0, const vec3& p1);

	bool is_t_valid(float t) const;	// t must be in [0,1] if it's line, and t>=0 for ray

	struct CrossResult {
		bool crossed = false;
        vec3 p = vec3(0,0,0);
		float t = 0;	// t in [0,1] means that point inside a segment [p0, p1]
	};
};


// Plane in 3D
struct XGeomGeomPlane {
    bool setup(const vec3& origin, const vec3& normal, bool normalize = true);
    bool setup(const vec3& origin, const vec3& vec1, const vec3& vec2);
    bool setup_by_points(const vec3& p0, const vec3& p1, const vec3& p2);
	void revert_normal();

	// Signed distance from point to plane
    float signed_distance(const vec3& point) const;

	// Projection of the point to plane
    vec3 projection(const vec3& point) const;

	// Crossing plane and line, if t in [0,1] it means crossed as segment
    XGeomGeomLine3D::CrossResult cross_line(const XGeomGeomLine3D& line) const;

    vec3 base;
    vec3 norm;
	float d = 0;	//dot(norm,p) + d = 0 - equation of the plane
};

// Triangle in 3D
struct XGeomGeomTriangle3D {
    XGeomGeomTriangle3D() {}
    XGeomGeomTriangle3D(const vec3& p0, const vec3& p1, const vec3& p2);
    void setup(const vec3& p0, const vec3& p1, const vec3& p2);

	// Crossing triangle and line, if t in [0,1] it means crossed as segment
	/* Usage:
        XGeomGeomLine3D line(vec3(0, 0, 0), vec3(0, 0, 10));
        XGeomGeomTriangle3D tri(vec3(-1, -1, 1), vec3(0, 1, 1), vec3(1, -1, 1));
		auto cross = tri.cross_line(line);
        qDebug() << "crossed " << cross.crossed << " t " << cross.t << "   point " << cross.p.x << ", " << cross.p.y << ", " << cross.p.z << endl;
	*/
    XGeomGeomLine3D::CrossResult cross_line(const XGeomGeomLine3D& line, float eps = 0.001) const;

    vec3 p0;
    vec3 p1;
    vec3 p2;
    XGeomGeomPlane plane, plane01, plane12, plane20;
};

//Minimal distance between two point sets
float XGeomPointCloudsDistance(const QVector<vec3> &A, const QVector<vec3> &B);

//Triangle area, signed, 2D
float XGeomGeomTriangleAreaSigned(const vec3 &a, const vec3 &b, const vec3 &c);

//Check if point is strictly inside polygon, given CCV
bool XGeomGeomPointInsidePolygonCcvStrictly(const vec3 &p, const QVector<vec3> &pnt);


//Convert unit square [0,1]x[0,1] to unit sphere
vec3 XGeomGeomSquareToSphere(const vec3 &p2);

//Convert unit sphere to unit square [0,1]x[0,1]
vec2 XGeomGeomSphereToSquare(const vec3 &p3);


//Generate a circle on a unit sphere
QVector<vec3> XGeomGeomCreateCircleOnSphere(vec3 c3, float rad, int resolution);







