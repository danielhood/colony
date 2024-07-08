#pragma once

#include <vector>
#include <array>
#include <memory>

using namespace std;

class Tile {
	public:
		Tile();

		// TODO: Remove ring/pos
		void setRingPos(int ring, int pos);
		int getRing() const { return ring_; }
		int getPos() const { return pos_; }

		void setCoords(int x, int y);
		int getX() const { return x_; }
		int getY() const { return y_; }
		
		Tile& getLink(int index);
		int numLinks() { return (int)dynLinks_.size(); }
		void addLink(Tile& tile);
		bool isAdjacentTo(int ring, int pos);

		// links_[0] is up, and increments clockwise
		array<Tile*, 6> links_ = {};

	protected:
		// TODO: Remove ring/pos
		int ring_ = 0;
		int pos_ = 0;
		vector<Tile*> dynLinks_;

		int x_ = 0;
		int y_ = 0;
		bool coordInitialized_ = false;
};
