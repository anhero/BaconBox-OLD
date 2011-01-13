#ifndef __CHARACTER_H
#define __CHARACTER_H

#include <vector>
namespace RedBox {

struct Kerning {
	int charID;
	int amount;
	Kerning(int characterID, int amountOfKerning):charID(characterID), amount(amountOfKerning){}
};

class Character {
	friend class CharacterSet;

private:
	int charID;
	int u; //x texture maping coordinate
	int v; //y texture maping coordinate
	int texHandle; //opengl texture handle
	int width;
	int height;
	int xAdvance;
	int xOffset;
	int yOffset;
	std::vector<Kerning> kerning;
};
}
#endif