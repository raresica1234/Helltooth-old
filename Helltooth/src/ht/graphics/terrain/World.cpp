#include "World.h"

#include <cstdio>
#include <cmath>
#include <cstdlib>

namespace ht { namespace graphics {
	using namespace maths;

#define maxPrimeIndex 10

	int numX = 512,
		numY = 512,
		numOctaves = 7;
	double persistence = 1;

	int primeIndex = 0;

	int primes[maxPrimeIndex][3] = {
		{ 995615039, 600173719, 701464987 },
		{ 831731269, 162318869, 136250887 },
		{ 174329291, 946737083, 245679977 },
		{ 362489573, 795918041, 350777237 },
		{ 457025711, 880830799, 909678923 },
		{ 787070341, 177340217, 593320781 },
		{ 405493717, 291031019, 391950901 },
		{ 458904767, 676625681, 424452397 },
		{ 531736441, 939683957, 810651871 },
		{ 997169939, 842027887, 423882827 }
	};

	double Noise(int i, int x, int y) {
		int n = x + y * 57;
		n = (n << 13) ^ n;
		int a = primes[i][0], b = primes[i][1], c = primes[i][2];
		int t = (n * (n * n * a + b) + c) & 0x7fffffff;
		return 1.0 - (double)(t) / 1073741824.0;
	}

	double SmoothedNoise(int i, int x, int y) {
		double corners = (Noise(i, x - 1, y - 1) + Noise(i, x + 1, y - 1) +
			Noise(i, x - 1, y + 1) + Noise(i, x + 1, y + 1)) / 16,
			sides = (Noise(i, x - 1, y) + Noise(i, x + 1, y) + Noise(i, x, y - 1) +
				Noise(i, x, y + 1)) / 8,
			center = Noise(i, x, y) / 4;
		return corners + sides + center;
	}

	double Interpolate(double a, double b, double x) {  // cosine interpolation
		double ft = x * 3.1415927,
			f = (1 - cos(ft)) * 0.5;
		return  a*(1 - f) + b*f;
	}

	double InterpolatedNoise(int i, double x, double y) {
		int integer_X = (int)x;
		double fractional_X = x - integer_X;
		int integer_Y = (int)y;
		double fractional_Y = y - integer_Y;

		double v1 = SmoothedNoise(i, integer_X, integer_Y),
			v2 = SmoothedNoise(i, integer_X + 1, integer_Y),
			v3 = SmoothedNoise(i, integer_X, integer_Y + 1),
			v4 = SmoothedNoise(i, integer_X + 1, integer_Y + 1),
			i1 = Interpolate(v1, v2, fractional_X),
			i2 = Interpolate(v3, v4, fractional_X);
		return Interpolate(i1, i2, fractional_Y);
	}

	double ValueNoise_2D(double x, double y) {
		double total = 0,
			frequency = pow(2, numOctaves),
			amplitude = 10;
		for (int i = 0; i < numOctaves; ++i) {
			frequency /= 2;
			amplitude *= persistence;
			total += InterpolatedNoise((primeIndex + i) % maxPrimeIndex,
				x / frequency, y / frequency) * amplitude;
		}
		return total / frequency;
	}


	World::World(int size, vec4 terrainCounts)
		: StaticEntity(nullptr) {
		hasShader = true;
		for (float x = terrainCounts.z; x <= terrainCounts.x; x+=1.0f) 
			for (float y = terrainCounts.w; y <= terrainCounts.y; y+= 1.0f) {
				Renderable* current = generateTerrain();
				chunks.push_back(Chunk(vec2(x, y), current));
			}
		utils::String vertex = shader.generateVertex(), fragment = shader.generateFragment();

		unsigned int id = API::createShader(vertex, fragment, false);
		program = ShaderManager::Get()->getProgram(id);
	}

	World::~World() {
		for (Chunk chunk : chunks) {
			del chunk.chunk;
		}
	}


	Renderable* World::generateTerrain() {
		RawModel* model = nullptr;

		GLfloat distance = (float)TERRAIN_SIZE / ((float)VERTEX_COUNT - 1);

		int terrainSize = VERTEX_COUNT * VERTEX_COUNT;

		GLfloat* positions = htnew GLfloat[terrainSize * 3];
		GLfloat* normals = htnew GLfloat[terrainSize * 3];
		GLuint* indices = htnew GLuint[6 * (VERTEX_COUNT - 1) * (VERTEX_COUNT - 1)];
		GLfloat* textureCoords = htnew GLfloat[terrainSize * 2];

		int vertexPointer = 0;

		for (float y = 0; y < VERTEX_COUNT; y++)
			for (float x = 0; x < VERTEX_COUNT; x++) {
				positions[vertexPointer * 3] = x * distance;
				positions[vertexPointer * 3 + 1] = getHeight(x, y, distance);
				positions[vertexPointer * 3 + 2] = y * distance;

				vec3 normal = generateNormal(x, y, distance);

				normals[vertexPointer * 3] = normal.x;
				normals[vertexPointer * 3 + 1] = normal.y;
				normals[vertexPointer * 3 + 2] = normal.z;

				textureCoords[vertexPointer * 2] = x / ((float)VERTEX_COUNT - 1);
				textureCoords[vertexPointer * 2 + 1] = y / ((float)VERTEX_COUNT - 1);
				vertexPointer++;
			}

		int pointer = 0;
		for (unsigned int gz = 0; gz < VERTEX_COUNT - 1; gz++) {
			for (unsigned int gx = 0; gx < VERTEX_COUNT - 1; gx++) {
				unsigned int topLeft = (gz*VERTEX_COUNT) + gx;
				unsigned int topRight = topLeft + 1;
				unsigned int bottomLeft = ((gz + 1)*VERTEX_COUNT) + gx;
				unsigned int bottomRight = bottomLeft + 1;
				indices[pointer++] = topLeft;
				indices[pointer++] = bottomLeft;
				indices[pointer++] = topRight;
				indices[pointer++] = topRight;
				indices[pointer++] = bottomLeft;
				indices[pointer++] = bottomRight;
			}
		}
		model = htnew RawModel(positions, terrainSize * 3 * sizeof(GLfloat));
		model->storeData(indices, 6 * (VERTEX_COUNT - 1) * (VERTEX_COUNT - 1) * sizeof(GLuint));
		model->storeData(RAWMODEL_NORMALS, normals, terrainSize * 3 * sizeof(GLfloat));
		model->storeData(RAWMODEL_TEXTURE_COORDS, textureCoords, terrainSize * 2 * sizeof(GLfloat));

		Renderable* renderable = htnew Renderable();
		renderable->loadRawModel(model);
		return renderable;
	}

	vec3 World::generateNormal(float x, float y, float distance) {
		float heightL = getHeight(x - 1, y, distance);
		float heightR = getHeight(x + 1, y, distance);
		float heightD = getHeight(x, y - 1, distance);
		float heightU = getHeight(x, y + 1, distance);
		vec3 normal(heightL - heightR, 2.0f, heightD - heightU);
		normal.normalize();
		return normal;
	}

	float World::getHeight(float x, float y, float distance) {
		if(x == 0 && y == 0)
			return (float)ValueNoise_2D((VERTEX_COUNT - 1) * distance, (VERTEX_COUNT - 1) * distance);
		else if (x == 0)
			return (float)ValueNoise_2D((VERTEX_COUNT - 1) * distance, y * distance);
		else if (y == 0)
			return (float)ValueNoise_2D(x * distance, (VERTEX_COUNT - 1) * distance);
		return (float)ValueNoise_2D(x * distance, y * distance);
	}


} } 