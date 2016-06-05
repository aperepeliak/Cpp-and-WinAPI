#include <time.h>
#include "FIFA.h"

using namespace std;

void main() {
	system("color F0");
	srand((unsigned)time(NULL));

	FIFA season;
	season.Play();
}