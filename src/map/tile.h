#pragma once

#include <vector>
#include <array>
#include <memory>

using namespace std;

class Tile {
	public:
		void setCoords(int x, int y);
		int getX() const { return x_; }
		int getY() const { return y_; }
		
		Tile& getLink(int index);
		bool isAdjacentTo(int ring, int pos);

		// links_[0] is up, and increments clockwise
		array<shared_ptr<Tile>, 6> links_ = {};

	protected:
		int x_ = 0;
		int y_ = 0;
		bool coordInitialized_ = false;
};
