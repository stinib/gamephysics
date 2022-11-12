using namespace std;
using namespace GamePhysics;

class Point {
public:
	Point(Vec3 pos, Vec3 vel, Vec3 acc);


	// data variables
	Vec3 position;
	Vec3 velocity;
	Vec3 acceleration;
};