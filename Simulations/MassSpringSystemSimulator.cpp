#include "MassSpringSystemSimulator.h"

// Construtors
MassSpringSystemSimulator::MassSpringSystemSimulator() {
	float m_fMass = 10;
	float m_fStiffness = 40;
	float m_fDamping = 0;
	int m_iIntegrator = 0;

	Vec3 m_externalForce = Vec3();
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
	Vec3 pos{ 0,0,0 };
	Vec3 color{ 1,0.5,1 };
	float scale = 0.01;

	DUC->setUpLighting(Vec3(), 0.4 * Vec3(1, 1, 1), 100, 0.6 * Vec3(0.97, 0.86, 1));

	DUC->drawSphere(pos, scale);
}

void MassSpringSystemSimulator::notifyCaseChanged(int testCase)
{
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

	void MassSpringSystemSimulator::simulateTimestep(float timeStep) {}

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
	return -1;
}

void MassSpringSystemSimulator::addSpring(int masspoint1, int masspoint2, float initialLength) {}

int MassSpringSystemSimulator::getNumberOfMassPoints() {
	return -1;
}

int MassSpringSystemSimulator::getNumberOfSprings() {
	return -1;
}

Vec3 MassSpringSystemSimulator::getPositionOfMassPoint(int index) {
	return Vec3();
}

Vec3 MassSpringSystemSimulator::getVelocityOfMassPoint(int index) {
	return Vec3();
}

void MassSpringSystemSimulator::applyExternalForce(Vec3 force) {}
