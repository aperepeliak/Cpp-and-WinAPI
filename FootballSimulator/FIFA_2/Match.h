#pragma once
#include <string>

using namespace std;

class Match
{
protected:
	string h_name;		// ����� ������
	string g_name;

	int host;			// ����� ������ ����������� �������
	int guest;			// ����� ������ �������� �������

	int host_score;		// ������� ���� ���������
	int guest_score;	// ������� ���� �������

	int round;			// ���� ����������
	int tour;			// ��� ���������� ��� ���� �����

	int h_penalty;		// �� ������ ����� ��������
	int g_penalty;		// �� ������ ����� ��������

public:
	Match(int h_scored, int g_scored);

	Match(int h, int g, int t, int r = 0);

	void setHostName(string h_n) { h_name = h_n; }
	void setGuestName(string g_n) { g_name = g_n; }
	void setHost(int h) { host = h; }
	void setGuest(int g) { guest = g; }
	void setRound(int r) { round = r; }
	void setTour(int t) { tour = t; }
	void setHostScore(int hs) { host_score = hs; }
	void setGuestScore(int gs) { guest_score = gs; }
	void setHostPenalty(int h_p) { h_penalty = h_p; }
	void setGuestPenalty(int g_p) { g_penalty = g_p; }

	string getHostName() { return h_name; }
	string getGuestName() { return g_name; }
	int getHost() { return host; }
	int getGuest() { return guest; }
	int getRound() { return round; }
	int getTour() { return tour; }
	int getHostScore() { return host_score; }
	int getGuestScore() { return guest_score; }
	int getHostPenalty() { return h_penalty; }
	int getGuestPenalty() { return g_penalty; }
};