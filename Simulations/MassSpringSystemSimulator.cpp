#include "MassSpringSystemSimulator.h"

/// C:\Users\kerst\source\repos\gamephysics

// Construtors
MassSpringSystemSimulator::MassSpringSystemSimulator() {
	m_fMass = 10;
	m_fStiffness = 40;
	m_fDamping = 0;
	m_iIntegrator = 0;

	currentTime = 0;

	points_ = vector<Point>();
	springs_ = vector<Spring>();

	m_externalForce = Vec3();
}

// UI Functions
const char* MassSpringSystemSimulator::getTestCasesStr() {
	return "Euler, Midpoint";
}

void MassSpringSystemSimulator::initUI(DrawingUtilitiesClass* DUC) {
	this->DUC = DUC;
}

void MassSpringSystemSimulator::reset() {
	m_mouse.x = m_mouse.y = 0;
	m_trackmouse.x = m_trackmouse.y = 0;
	m_oldtrackmouse.x = m_oldtrackmouse.y = 0;
}

void MassSpringSystemSimulator::drawFrame(ID3D11DeviceContext* pd3dImmediateContext) {
	for (auto &p : points_) {
		DUC->setUpLighting(Vec3(), 0.4 * Vec3(1, 1, 1), 100, 0.6 * Vec3(0.97, 0.86, 1));
		DUC->drawSphere(p.position, scale);
	}

	for (auto &sp : springs_)
	{
		Point p1 = points_.at(sp.mp1);
		Point p2 = points_.at(sp.mp2);

		DUC->beginLine();
		DUC->drawLine(p1.position, color, p2.position, color);
		DUC->endLine();
	}
}



void MassSpringSystemSimulator::notifyCaseChanged(int testCase)
{
	addPointsAndSprings();

	m_iTestCase = testCase;

	switch (m_iTestCase)
	{
	case 0:
		cout << "Euler !\n";
		break;
	case 1:
		cout << "Midpoint !\n";
		break;
	default:
		cout << "Empty Test !\n";
		break;
	}
}

void MassSpringSystemSimulator::externalForcesCalculations(float timeElapsed) {} 

void MassSpringSystemSimulator::simulateTimestep(float timeStep) {
	currentTime += timeStep;
	//if (currentTime > 0.15) return;

	//cout << "current time: " << currentTime << endl << endl;

	switch (m_iTestCase)
	{
	case 0: 
		simulateEuler(timeStep); 
		break;
	case 1: 
		simulateMidpoint1StepAndPrintResults(timeStep);
		break;
	default: 
		print("SIMULATE TIMESTEP: Empty Test !");
		break;
	}
}

// helper methods
Vec3 MassSpringSystemSimulator::calculateVectorBetween(Vec3 src, Vec3 dst) {
	return dst - src;
}

float MassSpringSystemSimulator::calculateLengthOfVector(Vec3 d) {
	// ||d|| = sqrt( d1^2 + d2^2 + d3^2 )
	return sqrt( pow(d.x, 2) + pow(d.y, 2) + pow(d.z, 2));
}

Vec3 MassSpringSystemSimulator::normalize(Vec3 d, float l) {
	return d / l;
}
Vec3 MassSpringSystemSimulator::calculateForceWithHooke(float k, float l, float L, Vec3 d_norm) {
	return -m_fStiffness * (l - L) * d_norm;
}

Vec3 MassSpringSystemSimulator::calculateAcceleration(Vec3 f, float m) {
	// TODO: add gravity later
	return f / m;
}

Vec3 MassSpringSystemSimulator::calculateEulerUpdate(Vec3 x_old, Vec3 dx_old, float h) {
	return x_old + (dx_old * h);
}


// timestep simulator methods
void MassSpringSystemSimulator::simulateEuler(float h) {
	for (auto& sp : springs_)
	{
		// 0. get points
		Point& point2 = points_.at(sp.mp2);
		Point& point1 = points_.at(sp.mp1);

		// 1. calc normalized vectors
		Vec3 d1 = calculateVectorBetween(point2.position, point1.position);
		float l = calculateLengthOfVector(d1);
		Vec3 d1_norm = normalize(d1, l);
		Vec3 d2_norm = -d1_norm;

		// 2. calc Hooke Forces
		Vec3 f1 = calculateForceWithHooke(m_fStiffness, l, sp.L, d1_norm);
		Vec3 f2 = -f1;

		// 3. update point attributes
		point1.acceleration = calculateAcceleration(f1, m_fMass);
		point2.acceleration = calculateAcceleration(f2, m_fMass);

		point1.position = calculateEulerUpdate(point1.position, point1.velocity, h);
		point2.position = calculateEulerUpdate(point2.position, point2.velocity, h);

		point1.velocity = calculateEulerUpdate(point1.velocity, point1.acceleration, h);
		point2.velocity = calculateEulerUpdate(point2.velocity, point2.acceleration, h);
	}
}

void MassSpringSystemSimulator::simulateEuler1StepAndPrintResults(float h) {

	print("Euler Results:");
	simulateNextEulerStep(h, true);
}

void MassSpringSystemSimulator::simulateNextEulerStep(float h, bool printResults)
{
	cout << h << endl;
	for (auto& sp : springs_)
	{	
		// 0. get points
		Point& point2 = points_.at(sp.mp2);														cout << "index 2: " << sp.mp2 << " should be: 1" << endl;
		Point& point1 = points_.at(sp.mp1);														cout << "index 1: " << sp.mp1 << " should be: 0" << endl;

		// 1. calc normalized vectors
		Vec3 d1 = calculateVectorBetween(point2.position, point1.position);						cout << "d1: " << toString(d1)  << " should be: (0, -2, 0)" << endl;
		float l = calculateLengthOfVector(d1);													cout << "l: " << l << " should be: 2" << endl;
		Vec3 d1_norm = normalize(d1, l);														cout << "d1_norm: " << toString(d1_norm) << " should be: (0, -1, 0)" << endl;
		Vec3 d2_norm = -d1_norm;																cout << "d2_norm: " << toString(d2_norm) << " should be: (0, 1, 0)" << endl;

		// 2. calc Hooke Forces
		Vec3 f1 = calculateForceWithHooke(m_fStiffness, l, sp.L, d1_norm);						cout << "f1: " << toString(f1) << " should be: (0, 40, 0)" << endl;
		Vec3 f2 = -f1;																			cout << "f2: " << toString(f2) << " should be: (0, -40, 0)" << endl;
			
		// 3. update point attributes
		point1.acceleration = calculateAcceleration(f1, m_fMass);								cout << "a1: " << toString(point1.acceleration) << " should be: (0, 4, 0)" << endl;
		point2.acceleration = calculateAcceleration(f2, m_fMass);								cout << "a2: " << toString(point2.acceleration) << " should be: (0, -4, 0)" << endl;

		point1.position = calculateEulerUpdate(point1.position, point1.velocity, h);			cout << "p1: " << toString(point1.position) << " should be: (-0.1, 0, 0)" << endl;
		point2.position = calculateEulerUpdate(point2.position, point2.velocity, h);			cout << "p2: " << toString(point2.position) << " should be: (0.1, 2, 0)" << endl;
			
		point1.velocity = calculateEulerUpdate(point1.velocity, point1.acceleration, h);		cout << "v1: " << toString(point1.velocity) << " should be: (-1, 0.4, 0)" << endl;
		point2.velocity = calculateEulerUpdate(point2.velocity, point2.acceleration, h);		cout << "v2: " << toString(point2.velocity) << " should be: (1, -0.4, 0)" << endl;

		//if (printResults)
		/* {
			print("p1.p = ", point1.position);
			print("p1.v = ", point1.velocity);
			print("p1.a = ", point1.acceleration);
			print("");
			print("p2.p = ", point2.position);
			print("p2.v = ", point2.velocity);
			print("p2.a = ", point2.acceleration);
		}*/
	}
	
}

void MassSpringSystemSimulator::simulateMidpoint(float h) {}

void MassSpringSystemSimulator::simulateMidpoint1StepAndPrintResults(float h) {}

void MassSpringSystemSimulator::print(string message)
{
	cout << message << endl;
}


void MassSpringSystemSimulator::print(string message, Vec3 value)
{
	cout << message << " = (" << value.x << ", " << value.y << ", " << value.z << ") " << endl;
}

string MassSpringSystemSimulator::toString(Vec3 vector)
{
	stringstream ss;
	ss << "( " << vector.x << ", " << vector.y << ", " << vector.z << " )";
	return ss.rdbuf()->str();
}



void MassSpringSystemSimulator::onClick(int x, int y) {
	m_trackmouse.x = x;
	m_trackmouse.y = y;
}

void MassSpringSystemSimulator::onMouse(int x, int y) {
	m_oldtrackmouse.x = x;
	m_oldtrackmouse.y = y;
	m_trackmouse.x = x;
	m_trackmouse.y = y;
}


// Specific Functions
void MassSpringSystemSimulator::setMass(float mass) {
	m_fMass = mass;
}

void MassSpringSystemSimulator::setStiffness(float stiffness) {
	m_fStiffness = stiffness;
}

void MassSpringSystemSimulator::setDampingFactor(float damping) {
	m_fDamping = damping;
}

int MassSpringSystemSimulator::addMassPoint(Vec3 position, Vec3 Velocity, bool isFixed) {
	points_.emplace_back(position, Velocity, isFixed);
	return points_.size() - 1;
}

void MassSpringSystemSimulator::addSpring(int masspoint1, int masspoint2, float initialLength) {
	springs_.emplace_back(masspoint1, masspoint2, initialLength);
}

int MassSpringSystemSimulator::getNumberOfMassPoints() {
	return points_.size();;
}

int MassSpringSystemSimulator::getNumberOfSprings() {
	return springs_.size();;
}

Vec3 MassSpringSystemSimulator::getPositionOfMassPoint(int index) {
	return points_.at(index).position;
}

Vec3 MassSpringSystemSimulator::getVelocityOfMassPoint(int index) {
	return points_.at(index).velocity;

}

void MassSpringSystemSimulator::applyExternalForce(Vec3 force) {}

void MassSpringSystemSimulator::addPointsAndSprings()
{
	setMass(10);
	setStiffness(40);
	setDampingFactor(0);

	int p1_id = addMassPoint(Vec3(0, 0, 0), Vec3(-1, 0, 0), false);
	int p2_id = addMassPoint(Vec3(0, 2, 0), Vec3(1, 0, 0), false);
	//addMassPoint(Vec3(1, 2, 0), Vec3(1, 0, 0), false);

	addSpring(p1_id, p2_id, 1);
	//addSpring(2, 1, 1);
}
