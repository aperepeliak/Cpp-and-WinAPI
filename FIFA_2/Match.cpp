#include "Match.h"

Match::Match(int h_scored, int g_scored) {
	host_score = h_scored;
	guest_score = g_scored;
}

Match::Match(int h, int g, int t, int r)
{
	h_name = "undefined";
	g_name = "undefined";
	host = h;
	guest = g;
	tour = t;
	round = r;
	host_score = 0;
	guest_score = 0;
	h_penalty = 0;
	g_penalty = 0;
}
