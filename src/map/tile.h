#pragma once

#include <vector>
#include <memory>

using namespace std;

class Tile {
	public:
		void setCoord (int ring, int pos);
		int getRing () const { return ring_; }
		int getPos () const { return pos_; }
		
		Tile& getLink(int index);
		int numLinks() { return links_.size(); }
		void addLink(Tile& tile);

	protected:
		int ring_ = 0;
		int pos_ = 0;
		bool coordInitialized_ = false;

		vector<Tile*> links_;
};
