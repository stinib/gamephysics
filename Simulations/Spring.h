using namespace std;
using namespace GamePhysics;

class Spring {
public:
	Spring(int id1, int id2, float initialLength);


	// data variables
	int mp1;
	int mp2;
	float L;
};