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

	// render constants
	const Vec3 color{ 1, 0.5, 1 };
	const float scale{ 0.05 };
	const float timestep{ 0.1 };


	// helper methods
	void addPointsAndSprings();
	Vec3 calculateVectorBetween(Vec3 src, Vec3 dst);
	float calculateLengthOfVector(Vec3 d);
	Vec3 normalize(Vec3 d, float len);
	Vec3 calculateForceWithHooke(float k, float l, float L, Vec3 d_norm);
	Vec3 calculateAcceleration(Vec3 f, float m);
	Vec3 calculateEulerUpdate(Vec3 x_old, Vec3 dx_old, float h);

	// timestep simulator methods
	void simulateEuler(float h);
	void simulateEuler1StepAndPrintResults(float h);

	void simulateMidpoint(float h);
	void simulateMidpoint1StepAndPrintResults(float h);
};
#endif