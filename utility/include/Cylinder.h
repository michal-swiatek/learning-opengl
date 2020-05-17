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

	const float PI = (float)acos(-1);
	unsigned int paramNum = 8;

public:
	Cylinder(float bR = 1.0f, float tR = 1.0f, float h = 2.0f, int secNum = 4, int staNum = 3) {
		this->setParams(bR, tR, h, secNum, staNum);
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

			this->clearVectors();

			this->generateCylinder();
		}
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
		this->generateVertices();
		this->generateIndices();
	}

	float vectorLength(std::vector<float> vec) {
		float squaresSum = 0.0f;
		for (int i = 0; i < vec.size(); ++i) {
			squaresSum += vec[i] * vec[i];
		}
		return sqrt(squaresSum);
	}

	std::vector<float> generateBaseCircleVertices() {
		float angleStep = 2 * PI / this->sectorsNum;

		std::vector<float> circleVertices;
		// Coords
		circleVertices.push_back(0.0f);
		circleVertices.push_back(-this->height / 2.0f);
		circleVertices.push_back(0.0f);
		// N vec coords
		circleVertices.push_back(0.0f);
		circleVertices.push_back(-1.0f);
		circleVertices.push_back(0.0f);
		// UV
		circleVertices.push_back(0.0f);
		circleVertices.push_back(0.0f);
		if (this->baseRadius > 0) {
			for (int i = 0; i < this->sectorsNum; ++i) {
				// Coords
				circleVertices.push_back(this->baseRadius*cos(i*angleStep));
				circleVertices.push_back(-this->height / 2.0f);
				circleVertices.push_back(this->baseRadius*sin(i*angleStep));
				// N vec coords
				std::vector<float> nVec = { this->baseRadius*cos(i*angleStep), 0.0f, this->baseRadius*sin(i*angleStep) };
				float nVecLen = vectorLength(nVec);
				for (int i = 0; i < nVec.size(); ++i) {
					nVec[i] /= nVecLen;
				}

				circleVertices.push_back(nVec[0]);
				circleVertices.push_back(nVec[1]);
				circleVertices.push_back(nVec[2]);
				// UV
				circleVertices.push_back(0.0f);
				circleVertices.push_back(0.0f);
			}
		}
		return circleVertices;
	}

	std::vector<float> generateTopCircleVertices() {
		float angleStep = 2 * PI / this->sectorsNum;

		std::vector<float> circleVertices;
		// Coords
		circleVertices.push_back(0.0f);
		circleVertices.push_back(this->height / 2.0f);
		circleVertices.push_back(0.0f);
		// N vec coords
		circleVertices.push_back(0.0f);
		circleVertices.push_back(1.0f);
		circleVertices.push_back(0.0f);
		// UV
		circleVertices.push_back(0.0f);
		circleVertices.push_back(0.0f);
		if (this->topRadius > 0.0f) {
			for (int i = 0; i < this->sectorsNum; ++i) {
				// Coords
				circleVertices.push_back(this->topRadius*cos(i*angleStep));
				circleVertices.push_back(this->height / 2.0f);
				circleVertices.push_back(this->topRadius*sin(i*angleStep));
				// N vec coords
				std::vector<float> nVec = { this->topRadius*cos(i*angleStep), 0.0f, this->topRadius*sin(i*angleStep) };
				float nVecLen = vectorLength(nVec);
				for (int i = 0; i < nVec.size(); ++i) {
					nVec[i] /= nVecLen;
				}
				circleVertices.push_back(nVec[0]);
				circleVertices.push_back(nVec[1]);
				circleVertices.push_back(nVec[2]);
				// UV
				circleVertices.push_back(0.0f);
				circleVertices.push_back(0.0f);
			}
		}
		return circleVertices;
	}

	void generateVertices() {
		std::vector<float> topCircleVertices = generateTopCircleVertices();
		std::vector<float> baseCircleVertices = generateBaseCircleVertices();

		// Add top circle vertices
		for (unsigned int i = 0; i < topCircleVertices.size(); ++i) {
			this->vertices.push_back(topCircleVertices[i]);
		}

		// Count steps for each coords.
		std::vector<std::vector<float>> verticesStep;
		if (this->topRadius <= 0.0f) {
			for (int i = 0; i < this->sectorsNum; ++i) {
				verticesStep.push_back(std::vector<float>());
				verticesStep[i].push_back((baseCircleVertices[(i + 1) * paramNum] - topCircleVertices[0]) / this->stacksNum);
				verticesStep[i].push_back((baseCircleVertices[(i + 1) * paramNum + 1] - topCircleVertices[1]) / this->stacksNum);
				verticesStep[i].push_back((baseCircleVertices[(i + 1) * paramNum + 2] - topCircleVertices[2]) / this->stacksNum);
			}
		}
		else if (this->baseRadius <= 0.0f) {
			for (int i = 0; i < this->sectorsNum; ++i) {
				verticesStep.push_back(std::vector<float>());
				verticesStep[i].push_back((baseCircleVertices[0] - topCircleVertices[(i + 1) * paramNum]) / this->stacksNum);
				verticesStep[i].push_back((baseCircleVertices[1] - topCircleVertices[(i + 1) * paramNum + 1]) / this->stacksNum);
				verticesStep[i].push_back((baseCircleVertices[2] - topCircleVertices[(i + 1) * paramNum + 2]) / this->stacksNum);
			}
		}
		else {
			for (int i = 0; i < this->sectorsNum; ++i) {
				verticesStep.push_back(std::vector<float>());
				verticesStep[i].push_back((baseCircleVertices[(i + 1) * paramNum] - topCircleVertices[(i + 1) * paramNum]) / this->stacksNum);
				verticesStep[i].push_back((baseCircleVertices[(i + 1) * paramNum + 1] - topCircleVertices[(i + 1) * paramNum + 1]) / this->stacksNum);
				verticesStep[i].push_back((baseCircleVertices[(i + 1) * paramNum + 2] - topCircleVertices[(i + 1) * paramNum + 2]) / this->stacksNum);
			}
		}

		// Add between vertices
		if (this->topRadius <= 0.0f) {
			for (int i = 0; i < this->stacksNum; ++i) {
				for (int j = 0; j < this->sectorsNum; ++j) {
					// Coords
					this->vertices.push_back(topCircleVertices[0] + (i + 1)*verticesStep[j][0]);
					this->vertices.push_back(topCircleVertices[1] + (i + 1)*verticesStep[j][1]);
					this->vertices.push_back(topCircleVertices[2] + (i + 1)*verticesStep[j][2]);
					// N vec coords
					std::vector<float> nVec = { topCircleVertices[0] + (i + 1)*verticesStep[j][0], 0.0f, topCircleVertices[2] + (i + 1)*verticesStep[j][2] };
					float nVecLen = vectorLength(nVec);
					for (int i = 0; i < nVec.size(); ++i) {
						nVec[i] /= nVecLen;
					}
					this->vertices.push_back(nVec[0]);
					this->vertices.push_back(nVec[1]);
					this->vertices.push_back(nVec[2]);
					// UV
					this->vertices.push_back(0.0f);
					this->vertices.push_back(0.0f);
				}
			}
		}
		else if (this->baseRadius <= 0.0f) {
			for (int i = 0; i < this->stacksNum - 1; ++i) {
				for (int j = 0; j < this->sectorsNum; ++j) {
					// Coords
					this->vertices.push_back(topCircleVertices[(j + 1) * paramNum] + (i + 1)*verticesStep[j][0]);
					this->vertices.push_back(topCircleVertices[(j + 1) * paramNum + 1] + (i + 1)*verticesStep[j][1]);
					this->vertices.push_back(topCircleVertices[(j + 1) * paramNum + 2] + (i + 1)*verticesStep[j][2]);
					// N vec coords
					std::vector<float> nVec = { topCircleVertices[(j + 1) * paramNum] + (i + 1)*verticesStep[j][0], 0.0f, topCircleVertices[(j + 1) * paramNum + 2] + (i + 1)*verticesStep[j][2] };
					float nVecLen = vectorLength(nVec);
					for (int i = 0; i < nVec.size(); ++i) {
						nVec[i] /= nVecLen;
					}
					this->vertices.push_back(nVec[0]);
					this->vertices.push_back(nVec[1]);
					this->vertices.push_back(nVec[2]);
					// UV
					this->vertices.push_back(0.0f);
					this->vertices.push_back(0.0f);
				}
			}
		}
		else {
			for (int i = 0; i < this->stacksNum; ++i) {
				for (int j = 0; j < this->sectorsNum; ++j) {
					// Coords
					this->vertices.push_back(topCircleVertices[(j + 1) * paramNum] + (i + 1)*verticesStep[j][0]);
					this->vertices.push_back(topCircleVertices[(j + 1) * paramNum + 1] + (i + 1)*verticesStep[j][1]);
					this->vertices.push_back(topCircleVertices[(j + 1) * paramNum + 2] + (i + 1)*verticesStep[j][2]);
					// N vec coords
					std::vector<float> nVec = { topCircleVertices[(j + 1) * paramNum] + (i + 1)*verticesStep[j][0], 0.0f, topCircleVertices[(j + 1) * paramNum + 2] + (i + 1)*verticesStep[j][2] };
					float nVecLen = vectorLength(nVec);
					for (int i = 0; i < nVec.size(); ++i) {
						nVec[i] /= nVecLen;
					}
					this->vertices.push_back(nVec[0]);
					this->vertices.push_back(nVec[1]);
					this->vertices.push_back(nVec[2]);
					// UV
					this->vertices.push_back(0.0f);
					this->vertices.push_back(0.0f);
				}
			}
		}

		// Add base vertices
		for (int i = 0; i < paramNum; ++i) {
			this->vertices.push_back(baseCircleVertices[i]);
		}
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
			for (int i = 0; i < this->stacksNum - 1; ++i) {
				for (int j = 0; j < this->sectorsNum - 1; ++j) {
					this->indices.push_back(j + 1 + i * this->sectorsNum);
					this->indices.push_back(j + 2 + i * this->sectorsNum);
					this->indices.push_back(j + 1 + (i + 1) * this->sectorsNum);
					this->indices.push_back(j + 2 + i * this->sectorsNum);
					this->indices.push_back(j + 2 + (i + 1) * this->sectorsNum);
					this->indices.push_back(j + 1 + (i + 1) * this->sectorsNum);
				}
				this->indices.push_back((i + 1)*this->sectorsNum);
				this->indices.push_back(1 + i * this->sectorsNum);
				this->indices.push_back((i + 2)*this->sectorsNum);
				this->indices.push_back(1 + i * this->sectorsNum);
				this->indices.push_back(1 + (i + 1) * this->sectorsNum);
				this->indices.push_back((i + 2)*this->sectorsNum);
			}
		}
		else if (this->baseRadius <= 0.0f) {
			for (int i = 0; i < this->stacksNum - 1; ++i) {
				for (int j = 0; j < this->sectorsNum - 1; ++j) {
					this->indices.push_back(j + 1 + i * this->sectorsNum);
					this->indices.push_back(j + 2 + i * this->sectorsNum);
					this->indices.push_back(j + 1 + (i + 1) * this->sectorsNum);
					this->indices.push_back(j + 2 + i * this->sectorsNum);
					this->indices.push_back(j + 2 + (i + 1) * this->sectorsNum);
					this->indices.push_back(j + 1 + (i + 1) * this->sectorsNum);
				}
				this->indices.push_back((i + 1)*this->sectorsNum);
				this->indices.push_back(1 + i * this->sectorsNum);
				this->indices.push_back((i + 2)*this->sectorsNum);
				this->indices.push_back(1 + i * this->sectorsNum);
				this->indices.push_back(1 + (i + 1) * this->sectorsNum);
				this->indices.push_back((i + 2)*this->sectorsNum);
			}
			for (int i = 0; i < this->sectorsNum - 1; ++i) {
				this->indices.push_back(this->vertices.size() / paramNum - 1);
				this->indices.push_back(this->vertices.size() / paramNum - 3 - i);
				this->indices.push_back(this->vertices.size() / paramNum - 2 - i);
			}
			this->indices.push_back(this->vertices.size() / paramNum - 1);
			this->indices.push_back(this->vertices.size() / paramNum - 2);
			this->indices.push_back(this->vertices.size() / paramNum - 1 - this->sectorsNum);
		}
		else {
			for (int i = 0; i < this->stacksNum; ++i) {
				for (int j = 0; j < this->sectorsNum - 1; ++j) {
					this->indices.push_back(j + 1 + i * this->sectorsNum);
					this->indices.push_back(j + 2 + i * this->sectorsNum);
					this->indices.push_back(j + 1 + (i + 1) * this->sectorsNum);
					this->indices.push_back(j + 2 + i * this->sectorsNum);
					this->indices.push_back(j + 2 + (i + 1) * this->sectorsNum);
					this->indices.push_back(j + 1 + (i + 1) * this->sectorsNum);
				}
				this->indices.push_back((i + 1)*this->sectorsNum);
				this->indices.push_back(1 + i * this->sectorsNum);
				this->indices.push_back((i + 2)*this->sectorsNum);
				this->indices.push_back(1 + i * this->sectorsNum);
				this->indices.push_back(1 + (i + 1) * this->sectorsNum);
				this->indices.push_back((i + 2)*this->sectorsNum);
			}
		}

		// Base
		if (this->baseRadius > 0.0f) {
			for (int i = 0; i < this->sectorsNum - 1; ++i) {
				this->indices.push_back(this->vertices.size() / paramNum - 1);
				this->indices.push_back(this->vertices.size() / paramNum - 3 - i);
				this->indices.push_back(this->vertices.size() / paramNum - 2 - i);
			}
			this->indices.push_back(this->vertices.size() / paramNum - 1);
			this->indices.push_back(this->vertices.size() / paramNum - 2);
			this->indices.push_back(this->vertices.size() / paramNum - 1 - this->sectorsNum);
		}
	}


};

