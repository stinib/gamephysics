#ifndef MASSSPRINGSYSTEMSIMULATOR_h
#define MASSSPRINGSYSTEMSIMULATOR_h
#include "Simulator.h"

// Do Not Change
#define EULER 0
#define LEAPFROG 1
#define MIDPOINT 2
// Do Not Change

class Point {
public:	
	
	// data variables
	Vec3 position;
	Vec3 velocity;
	Vec3 acceleration;
	bool isFixed;

	Point::Point(Vec3 pos, Vec3 vel, Vec3 acc) {
		position = pos;
		velocity = vel;
		acceleration = acc;
		isFixed = false;
	}

	Point::Point(Vec3 pos, Vec3 vel, bool fix) {
		position = pos;
		velocity = vel;
		isFixed = fix;
		acceleration = Vec3();
	}

};

class Spring {
public:
	Spring(int id1, int id2, float initialLength) {
		mp1 = id1;
		mp2 = id2;
		L = initialLength;
	}


	// data variables
	int mp1;
	int mp2;
	float L;
};

class MassSpringSystemSimulator:public Simulator{
public:
	// Construtors
	MassSpringSystemSimulator();
	
	// UI Functions
	const char * getTestCasesStr();
	void initUI(DrawingUtilitiesClass * DUC);
	void reset();
	void drawFrame(ID3D11DeviceContext* pd3dImmediateContext);
	void notifyCaseChanged(int testCase);
	void externalForcesCalculations(float timeElapsed);
	void simulateTimestep(float timeStep);
	void onClick(int x, int y);
	void onMouse(int x, int y);

	// Specific Functions
	void setMass(float mass);
	void setStiffness(float stiffness);
	void setDampingFactor(float damping);
	int addMassPoint(Vec3 position, Vec3 Velocity, bool isFixed);
	void addSpring(int masspoint1, int masspoint2, float initialLength);
	int getNumberOfMassPoints();
	int getNumberOfSprings();
	Vec3 getPositionOfMassPoint(int index);
	Vec3 getVelocityOfMassPoint(int index);
	void applyExternalForce(Vec3 force);
	
	// Do Not Change
	void setIntegrator(int integrator) {
		m_iIntegrator = integrator;
	}

private:
	// Data Attributes
	float m_fMass;
	float m_fStiffness;
	float m_fDamping;
	int m_iIntegrator;
	vector<Point> points_;
	vector<Spring> springs_;

	// UI Attributes
	Vec3 m_externalForce;
	Point2D m_mouse;
	Point2D m_trackmouse;
	Point2D m_oldtrackmouse;
};
#endif