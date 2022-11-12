#include "MassSpringSystemSimulator.h"

// Construtors
MassSpringSystemSimulator::MassSpringSystemSimulator() {
	m_fMass = 10;
	m_fStiffness = 40;
	m_fDamping = 0;
	m_iIntegrator = 0;

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
	for (auto p : points_) {
		DUC->setUpLighting(Vec3(), 0.4 * Vec3(1, 1, 1), 100, 0.6 * Vec3(0.97, 0.86, 1));
		DUC->drawSphere(p.position, scale);
	}

	for (auto sp : springs_)
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
	addMassPoint(Vec3(0, 0, 0), Vec3(-1, 0, 0), false);
	addMassPoint(Vec3(0, 2, 0), Vec3(1, 0, 0), false);
	addSpring(0,1, 1);


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
	points_.emplace_back(position, Velocity, isFixed);
	return points_.size() - 1;
	return -1;
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
