#pragma once
#include <vector>
#include <iostream>

class Cylinder
{
public:
	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	float baseRadius;
	float topRadius;
	float height;
	int sectorsNum;
	int stacksNum;

	const float PI = acos(-1);
	unsigned int paramNum = 3;

public:
	Cylinder( float bR = 1.0f, float tR = 1.0f, float h = 2.0f, int secNum = 4, int staNum = 3 ){
		setParams(bR, tR, h, secNum, staNum);
	}

	void setParams(float bR, float tR, float h, int secNum, int staNum) {
		if (bR <= 0 && tR <= 0) {
			std::cout << "Zle promienie" << '\n';
		}
		else if (h <= 0) {
			std::cout << "Zla wysokosc" << '\n';
		}
		else if (secNum < 3) {
			std::cout << "Zla liczba sectorow" << '\n';
		}
		else if (staNum < 1) {
			std::cout << "Zla liczba stackow" << '\n';
		}
		else {
			this->baseRadius = bR;
			this->topRadius = tR;
			this->height = h;
			this->sectorsNum = secNum;
			this->stacksNum = staNum;
		}

		clearVectors();

		generateCylinder();
		
	}

	std::vector<float> getVertices() {
		return this->vertices;
	}

	std::vector<unsigned int> getIndices() {
		return this->indices;
	}

	void clearVectors() {
		this->vertices.clear();
		this->indices.clear();
	}

	void generateCylinder() {
		generateVertices();
		generateIndices();
	}

	std::vector<float> generateBaseCircleVertices() {
		float angleStep = 2 * PI / sectorsNum;

		std::vector<float> circleVertices;
		circleVertices.push_back(0.0f);
		circleVertices.push_back(0.0f);
		circleVertices.push_back(-height / 2.0f);
		if (baseRadius > 0) {
			for (int i = 0; i < sectorsNum; ++i) {
				circleVertices.push_back(topRadius*cos(i*angleStep));
				circleVertices.push_back(topRadius*sin(i*angleStep));
				circleVertices.push_back(-height / 2.0f);
			}
		}
		return circleVertices;
	}
	std::vector<float> generateTopCircleVertices() {
		float angleStep = 2 * PI / sectorsNum;

		std::vector<float> circleVertices;
		circleVertices.push_back(0.0f);
		circleVertices.push_back(0.0f);
		circleVertices.push_back(height / 2.0f);
		if (topRadius > 0.0f) {
			for (int i = 0; i < sectorsNum; ++i) {
				circleVertices.push_back(topRadius*cos(i*angleStep));
				circleVertices.push_back(topRadius*sin(i*angleStep));
				circleVertices.push_back(height / 2.0f);
			}
		}
		return circleVertices;
	}
	void generateVertices() {
		std::vector<float> topCircleVertices = generateTopCircleVertices();
		std::vector<float> baseCircleVertices = generateBaseCircleVertices();
		
		// Add top circle vertices
		for (int i = 0; i < topCircleVertices.size(); ++i) {
			this->vertices.push_back(topCircleVertices[i]);
		}

		// Count steps for each coords.
		std::vector<std::vector<float>> verticesStep;
		if (topRadius <= 0.0f) {
			for (int i = 0; i < sectorsNum; ++i) {
				verticesStep.push_back(std::vector<float>());
				verticesStep[i].push_back((baseCircleVertices[(i + 1) * 3] - topCircleVertices[0]) / stacksNum);
				verticesStep[i].push_back((baseCircleVertices[(i + 1) * 3 + 1] - topCircleVertices[1]) / stacksNum);
				verticesStep[i].push_back((baseCircleVertices[(i + 1) * 3 + 2] - topCircleVertices[2]) / stacksNum);
			}
		}
		else if (baseRadius <= 0.0f) {
			for (int i = 0; i < sectorsNum; ++i) {
				verticesStep.push_back(std::vector<float>());
				verticesStep[i].push_back((baseCircleVertices[0] - topCircleVertices[(i + 1) * 3]) / stacksNum);
				verticesStep[i].push_back((baseCircleVertices[1] - topCircleVertices[(i + 1) * 3 + 1]) / stacksNum);
				verticesStep[i].push_back((baseCircleVertices[2] - topCircleVertices[(i + 1) * 3 + 2]) / stacksNum);
			}
		}
		else {
			for (int i = 0; i < sectorsNum; ++i) {
				verticesStep.push_back(std::vector<float>());
				verticesStep[i].push_back((baseCircleVertices[(i + 1) * 3] - topCircleVertices[(i + 1) * 3]) / stacksNum);
				verticesStep[i].push_back((baseCircleVertices[(i + 1) * 3 + 1] - topCircleVertices[(i + 1) * 3 + 1]) / stacksNum);
				verticesStep[i].push_back((baseCircleVertices[(i + 1) * 3 + 2] - topCircleVertices[(i + 1) * 3 + 2]) / stacksNum);
			}
		}

		// Add between vertices
		if (topRadius <= 0.0f) {
			for (int i = 0; i < stacksNum - 1; ++i) {
				for (int j = 0; j < sectorsNum; ++j) {
					this->vertices.push_back(topCircleVertices[0] + (i + 1)*verticesStep[j][0]);
					this->vertices.push_back(topCircleVertices[1] + (i + 1)*verticesStep[j][1]);
					this->vertices.push_back(topCircleVertices[2] + (i + 1)*verticesStep[j][2]);
				}
			}
		}
		else if (baseRadius <= 0.0f) {
			for (int i = 0; i < stacksNum - 2; ++i) {
				for (int j = 0; j < sectorsNum; ++j) {
					this->vertices.push_back(topCircleVertices[(j + 1) * 3] + (i + 1)*verticesStep[j][0]);
					this->vertices.push_back(topCircleVertices[(j + 1) * 3 + 1] + (i + 1)*verticesStep[j][1]);
					this->vertices.push_back(topCircleVertices[(j + 1) * 3 + 2] + (i + 1)*verticesStep[j][2]);
				}
			}
		}
		else {
			for (int i = 0; i < stacksNum - 1; ++i) {
				for (int j = 0; j < sectorsNum; ++j) {
					this->vertices.push_back(topCircleVertices[(j + 1) * 3] + (i + 1)*verticesStep[j][0]);
					this->vertices.push_back(topCircleVertices[(j + 1) * 3 + 1] + (i + 1)*verticesStep[j][1]);
					this->vertices.push_back(topCircleVertices[(j + 1) * 3 + 2] + (i + 1)*verticesStep[j][2]);
				}
			}
		}

		// Add base circle vertices
		//for (int i = 3; i < baseCircleVertices.size(); ++i) {
		//	vertices.push_back(baseCircleVertices[i]);
		//}
		this->vertices.push_back(baseCircleVertices[0]);
		this->vertices.push_back(baseCircleVertices[1]);
		this->vertices.push_back(baseCircleVertices[2]);
	}

	void generateIndices() {

		// Top
		if (this->topRadius > 0.0f) {
			for (int i = 0; i < this->sectorsNum - 1; ++i) {
				this->indices.push_back(0);
				this->indices.push_back((i + 2));
				this->indices.push_back((i + 1));
			}
			this->indices.push_back(0);
			this->indices.push_back(1);
			this->indices.push_back(this->sectorsNum);
		}

		// Side
		if (this->topRadius <= 0.0f) {
			for (int i = 0; i < this->sectorsNum - 1; ++i) {
				this->indices.push_back(0);
				this->indices.push_back((i + 2));
				this->indices.push_back((i + 1));
			}
			this->indices.push_back(0);
			this->indices.push_back(1);
			this->indices.push_back(this->sectorsNum);
			for (int i = 1; i < stacksNum - 1; ++i) {
				for (int j = 0; j < sectorsNum - 1; ++j) {
					this->indices.push_back(j + 1 + i * sectorsNum);
					this->indices.push_back(j + 2 + i * sectorsNum);
					this->indices.push_back(j + 1 + (i + 1) * sectorsNum);
					this->indices.push_back(j + 2 + i * sectorsNum);
					this->indices.push_back(j + 2 + (i + 1) * sectorsNum);
					this->indices.push_back(j + 1 + (i + 1) * sectorsNum);
				}
				this->indices.push_back((i + 1)*sectorsNum);
				this->indices.push_back(1 + i * sectorsNum);
				this->indices.push_back((i + 2)*sectorsNum);
				this->indices.push_back(1 + i * sectorsNum);
				this->indices.push_back(1 + sectorsNum + i * sectorsNum);
				this->indices.push_back((i + 2)*sectorsNum);
			}
		}
		else if (this->baseRadius <= 0.0f) {
			for (int i = 0; i < stacksNum - 2; ++i) {
				for (int j = 0; j < sectorsNum - 1; ++j) {
					this->indices.push_back(j + 1 + i * sectorsNum);
					this->indices.push_back(j + 2 + i * sectorsNum);
					this->indices.push_back(j + 1 + (i + 1) * sectorsNum);
					this->indices.push_back(j + 2 + i * sectorsNum);
					this->indices.push_back(j + 2 + (i + 1) * sectorsNum);
					this->indices.push_back(j + 1 + (i + 1) * sectorsNum);
				}
				this->indices.push_back((i + 1)*sectorsNum);
				this->indices.push_back(1 + i * sectorsNum);
				this->indices.push_back((i + 2)*sectorsNum);
				this->indices.push_back(1 + i * sectorsNum);
				this->indices.push_back(1 + sectorsNum + i * sectorsNum);
				this->indices.push_back((i + 2)*sectorsNum);
			}
			for (int i = 0; i < this->sectorsNum - 1; ++i) {
				this->indices.push_back(this->vertices.size() / 3 - 1);
				this->indices.push_back(this->vertices.size() / 3 - 3 - i);
				this->indices.push_back(this->vertices.size() / 3 - 2 - i);
			}
			this->indices.push_back(this->vertices.size() / 3 - 1);
			this->indices.push_back(this->vertices.size() / 3 - 2);
			this->indices.push_back(this->vertices.size() / 3 - 1 - this->sectorsNum);
		}
		else {
			for (int i = 0; i < stacksNum - 1; ++i) {
				for (int j = 0; j < sectorsNum - 1; ++j) {
					this->indices.push_back(j + 1 + i * sectorsNum);
					this->indices.push_back(j + 2 + i * sectorsNum);
					this->indices.push_back(j + 1 + (i+1) * sectorsNum);
					this->indices.push_back(j + 2 + i * sectorsNum);
					this->indices.push_back(j + 2 + (i+1) * sectorsNum);
					this->indices.push_back(j + 1 + (i+1) * sectorsNum);
				}
				this->indices.push_back((i + 1)*sectorsNum);
				this->indices.push_back(1 + i * sectorsNum);
				this->indices.push_back((i + 2)*sectorsNum);
				this->indices.push_back(1 + i * sectorsNum);
				this->indices.push_back(1 + sectorsNum + i * sectorsNum);
				this->indices.push_back((i + 2)*sectorsNum);
			}
		}

		// Base
		if (this->baseRadius > 0.0f) {
			for (int i = 0; i < this->sectorsNum - 1; ++i) {
				this->indices.push_back(this->vertices.size()/3 - 1);
				this->indices.push_back(this->vertices.size()/3 - 3 - i);
				this->indices.push_back(this->vertices.size()/3 - 2 - i);
			}
			this->indices.push_back(this->vertices.size()/3 - 1);
			this->indices.push_back(this->vertices.size()/3 - 2);
			this->indices.push_back(this->vertices.size()/3 - 1 - this->sectorsNum);
		}
	}

	
};

